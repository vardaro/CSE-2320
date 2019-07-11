/* Anthony Vardaro 1001522383 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    struct Node *next;
    char * value;
};

struct Queue {
    struct Node * head;
};

/*
 * Returns a dynamic struct Queue ptr
 */
struct Queue * initQueue() {
    struct Queue * q;
    q = malloc(sizeof(struct Queue));
    q->head = NULL;
    return q;
}

void printQueue(struct Queue * q) {
    struct Node *cur;

    for (cur = q->head; cur != NULL; cur = cur->next) {
        /* dont print a comma on the last entry */
        if (cur->next == NULL)
           printf("%s", cur->value);
        else
            printf("%s, ", cur->value);
    }
}

/**
 * Add a new record to a record of the linked list
 * @param q struct Queue to modify
 * @param record string to append
 */
void enqueue(struct Queue * q, char * record) {
    struct Node * cur;
    struct Node * nextNode;
    if (!q) {
      printf("no queue has been allocated");
      return;
    }

    if (*record==0) {
        printf("empty record");
        return;
    }

    /* traverse the LL to see if the record is already there.
     *
     * by the end of the loop, cur = tail, which we can use later in the function.
    */
    cur = q->head;
    while (cur && cur->next != NULL) {
        if (strcmp(cur->value, record)==0) {
            printf("%s already exists in queue", record);
            return;
        }
        cur = cur->next;
    }

    /* if the parameters pass data validation, we can start allocating new memory */
    nextNode = malloc(sizeof(struct Node));
    nextNode->value = malloc(strlen(record) + 1);
    strcpy(nextNode->value, record);
    nextNode->next = NULL;

    /* if empty queue,
     * set the head to nextNode
     * else, set the node AFTER the current tail to nextNode
    */
    if (cur  == NULL)
        q->head = nextNode;
    else
        cur->next = nextNode;

}

/**
 * Removes the head of a LL, makes
 * head->next the new head
 * free memory accordingly
 * @param q struct Queue
 */
void dequeue(struct Queue * q) {
    struct Node * temp = q->head;
    if (temp == NULL) {
        printf("queue is empty");
        return;
    }

    q->head = q->head->next;
    free(temp->value);
    free(temp);

}

/**
 * Remove the entire the queue,
 * does not free struct Queue ptr
 * but does free all the nodes in the LL
 * @param q struct Queue
 */
void flush(struct Queue * q) {
    if (q->head == NULL) {
        printf(" queue is empty");
        return;
    }

    while (q->head != NULL)
        dequeue(q);
}

/**
 * Parses the name in the format
 * add,Anthony -> Anthony
 * @param s string to parse
 * @return string after comma
 */
char * nameSubstring(char * s) {
    char * nameToAdd;
    strtok(s, ",");
    nameToAdd = strtok(NULL, ",");
    nameToAdd[strlen(nameToAdd) - 1] = '\0';
    return nameToAdd;
}


int main() {
    struct Queue * q = initQueue();
    char * nameToAdd;
    char * cur = NULL;
    int buffersize = 50;
    cur = (char *)malloc(buffersize * sizeof(char));
    while (getline(&cur, &buffersize, stdin) != EOF) {

        switch (cur[0]) {
            case 'a':
                printf("   add: ");
                strcpy(nameToAdd, nameSubstring(cur));
                enqueue(q, nameToAdd);
                printQueue(q);
                break;
            case 'r':
                printf("remove: ");
                dequeue(q);
                printQueue(q);
                break;
            case 'f':
                printf(" flush:");
                flush(q);
                break;
        }
        printf("\n");
    }

    free(cur);
    if (q->head) {
        printf("flushing remaining names\n");
        flush(q);
    }
    free(q);

    return 0;
}
