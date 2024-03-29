#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *value;
    struct Node *left;
    struct Node *right;
};

struct Node *balance(char **array, int firstIndex, int lastIndex) {
    int midpoint;
    struct Node *cur;
    if (firstIndex <= lastIndex) {
        midpoint = firstIndex + (lastIndex - firstIndex) / 2;
        cur =(struct Node *) malloc(sizeof(struct Node));
        cur->value = array[midpoint];

        cur->left = balance(array, firstIndex, midpoint - 1);
        cur->right = balance(array, midpoint + 1, lastIndex);

        return cur;
    } else {
        return NULL;
    }
}

/**
 * Sorts an array via insertion sort
 * @param arr array to sort
 * @param n length of array
 */
void sort(char **strings, int len) {
    int i, j;
    char *key;

    for (i = 1; i < len; i++) {
        key = strings[i];
        j = i - 1;

        while (j >= 0 && strcmp(strings[j], key) >= 0) {
            strings[j + 1] = strings[j];
            j = j - 1;
        }

        strings[j + 1] = key;
    }
}

/**
 * Prints a binary tree in preorder, root, left, right
 * @param root
 */
void preorder(struct Node * root) {
    if (root == NULL)
        return;

    printf("%s ", root->value);
    preorder(root->left);
    preorder(root->right);
}

/**
 * Prints binary tree in inorder
 * left,root,right
 * @param root
 */
void inorder(struct Node * root) {
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%s ", root->value);
    inorder(root->right);
}

/**
 * Prints binary tree in postorder
 * left,right,root
 * @param root
 */
void postorder(struct Node * root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%s ", root->value);
}

/**
 * Frees memory allocated for a binary tree via postorder traversal
 * @param root root node in current iteration
 */
void freeBinaryTree(struct Node * root) {
    if (root == NULL)
        return;

    freeBinaryTree(root->left);
    freeBinaryTree(root->right);
    free(root);
}

/**
 * Grows a previously allocated string array, by a factor of 2
 * This function modifies the pointers directly.
 * @param size int * of current size of the array
 * @param strings char *** ptr to 2d char array, array to resize
 */
void grow(int * size, char *** strings) {
    char ** temp;
    *size *= 2;
    printf("reallocating to %d addresses\n", *size);
    temp = realloc(*strings, *size * sizeof(char *));

    if (temp == NULL) {
        printf("unable to reallocate\n");
        return;
    }
    *strings = temp;

}
void freeStringArray(char ** strings, int len) {
    int i;
    for (i = 0; i < len; i++)
        free(strings[i]);
    free(strings);
}


int main() {
    int size = 2;
    int inputLen;
    int index = 0;
    FILE *fp;
    struct Node *root = NULL;
    char **strings = malloc(sizeof(char *) * size);
    char buffer[20];

    fp = fopen("./data-tree.txt", "r");

    if (!fp) {
        printf("error opening\n");
        return 1;
    }

    /*
     * Loop through every string in the file,
     *
     * check if theres enough room in char ** strings, if not,
     * resize the array and continue.
     *
     *
     * get the length of the current string, and malloc the
     * amt of memory accordingly in the char ** strings,
     * then copy it to the corresponding index
     */
    while (fgets(buffer, 20, fp) != NULL) {
        inputLen = strlen(buffer);

        /* terminate the trailing \n on buffer */
        buffer[inputLen - 1] = '\0';

        /* if the array is at max capracity, double its size */
        if (index == size)
            grow(&size, &strings);

        strings[index] = (char *) malloc(inputLen * sizeof(char));

        strcpy(strings[index], buffer);
        index++;

    }

    /* sort the array, and generate a binary tree with it to print */
    sort(strings, index);

    root = (struct Node *) malloc(sizeof(struct Node *));
    root = balance(strings, 0, index-1);

    printf("\n");
    printf(" preorder: ");
    preorder(root);
    printf("\n\n  inorder: ");
    inorder(root);
    printf("\n\npostorder: ");
    postorder(root);
    printf("\n");

    freeBinaryTree(root);
    freeStringArray(strings, index);

    return 0;
}
