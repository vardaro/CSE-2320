/*
    based on example at
      http://cboard.cprogramming.com/c-programming/123907-passing-pathname-argument-glob-function.html

    more information can be found at
      https://www.kernel.org/doc/man-pages/online/pages/man3/glob.3.html
*/

#include <stdio.h>
#include <glob.h>

int main(void)
{
    glob_t  paths;  
    int     csource;
    char    **p;
     
    /*  Find all ".mp3" files in given directory  */
    csource = glob("*.mp3", 0, NULL, &paths);
     
    if (csource == 0)
    {
        for (p=paths.gl_pathv; *p != NULL; ++p)
            printf("%s\n", *p);  /*  *p is the address of a string  */

        globfree(&paths);  /* function that frees the memory of the matching strings */
    }
}
