#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

/**
 * Computes a min of three variables
 * @param x
 * @param y
 * @param z
 * @return smallest int
 */
int min(int x, int y, int z) {
    int minxy = (x < y) ? x : y;
    return (minxy < z) ? minxy : z;
}

/*
 * DP Edit Distance approach from https://www.geeksforgeeks.org/edit-distance-dp-5/
 * in C89
 */
int editDist(char * str1, char * str2, int m, int n) {
    int ** dp;
    int i;
    int j;
    int ans;

    /* c89 does not allow variable len arrays, so we have to use dynamic mem
     * this is really no different than writing
     * int ** dp[m+1][n+1] in c99, or any modern programming language
     * */
    dp = (int **)malloc((m+1) * sizeof(int *));
    for (i = 0; i < m+1; i++)
        dp[i] = (int *)malloc((n+1) * sizeof(int));

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i==0)
                dp[i][j] = j;
            else if (j==0)
                dp[i][j] = i;
            else if(str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1]);
        }
    }

    /* store the answer so we dont lose it when we free space */
    ans = dp[m][n];
    for (i = 0; i < m+1; i++)
        free(dp[i]);
    free(dp);

    return ans;
}

int main(int argc, char * argv[]) {

    glob_t  paths;
    int csource;
    char **p;
    char **j;
    char reg[102] = "*.";
    int maxDistanceInteger;
    int currentEditDistance;
    int iterationHasBeenPrinted;

    if (argc != 3) {
        printf("usage:    executableName  maxDistanceInteger  fileNameExtension\n");
        printf("example:  %s  5  mp3\n", (char*)argv[0]);
        return 1;
    }

    /* append the supplied extension to "*.fileNameExtension */
    strcat(reg, argv[2]);

    /* capture filenames using regex */
    csource = glob(reg, 0, NULL, &paths);
    if (csource != 0) {
        printf("error capturing filenames\n");
        return csource;
    }

    /*
     * Iterate file glob  (i = 0) ... n
     * in the second loop (j = i) ... n
     *
     * compute the edit distance between j and i;
     * if the edit distance meets criteria, print it
     */
    maxDistanceInteger = atoi(argv[1]);
    iterationHasBeenPrinted = 0;

    for (p = paths.gl_pathv; *p != NULL; ++p) {
        for (j = p; *j != NULL; ++j) {
            currentEditDistance = editDist(*p, *j, strlen(*p), strlen(*j));
            if (currentEditDistance > 0 && currentEditDistance <= maxDistanceInteger) {

                if (iterationHasBeenPrinted == 0) {
                    printf("%s\n", *p);
                    iterationHasBeenPrinted = 1;
                }

                printf("%5d, %s\n", currentEditDistance, *j);
            }
        }

        iterationHasBeenPrinted = 0;
    }
    globfree(&paths);

    return 0;
}
