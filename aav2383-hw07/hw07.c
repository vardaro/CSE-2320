/* Anthony Vardaro 1001522383 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COURSE_BUFFER_LEN 100

struct class {
    char section[4];
    char subject[5];
    char catalog[5];
    char name[31];
    char building[5];
    char room[5];
    char start[6];
    char end[6];
    char mon[2];
    char tue[2];

    /* this field denotes what order the instance takes place in an array,
     * and is expecially important in maintaining this order when sorting ,
     * see comments below on qsortCallback() */
    size_t order;
};

void err(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

/**
 * Generates a dynamically allocated class from class buffer
 * @param buffer raw buffer from csv
 */
struct class *newClassFromBuffer(char *buffer) {
    struct class *c = (struct class *) malloc(sizeof(struct class) * 1);
    char delim[2] = ",";
    char copy[COURSE_BUFFER_LEN];
    strcpy(copy, buffer);
    strcpy(c->section, strtok(copy, delim));
    strcpy(c->subject, strtok(NULL, delim));
    strcpy(c->catalog, strtok(NULL, delim));
    strcpy(c->name, strtok(NULL, delim));
    strcpy(c->building, strtok(NULL, delim));
    strcpy(c->room, strtok(NULL, delim));
    strcpy(c->start, strtok(NULL, delim));
    strcpy(c->end, strtok(NULL, delim));
    strcpy(c->mon, strtok(NULL, delim));
    strcpy(c->tue, strtok(NULL, delim));

    return c;

}

void insertString(char ***array, char *str, int size) {
    char **temp = realloc(*array, size * sizeof(char *));
    if (temp == NULL)
        err("Unable to realloc array");
    temp[size - 1] = (char *) malloc(strlen(str) * sizeof(char));
    strcpy(temp[size - 1], str);

    *array = temp;
}

void insertClass(struct class **array, struct class *c, int size) {
    struct class *temp = realloc(*array, size * sizeof(struct class));
    if (temp == NULL)
        err("Unable to realloc array");
//    new = newClassFromBuffer(buffer);
    /* set the order of placement for this instance */
    c->order = size;

    temp[size - 1] = *c;
    *array = temp;
}

/**
 * Returns a bool denoting if the kiddo can take the class
 * @param eligible string array of class the student can take.
 * @param classBuffer raw buffer from courses csv file. it will parse the buffer in a
 *                    copied string, so the original will not get modified.
 * @param sizeEligible length of the eligible string array (number of strings)
 * @return integer 1 if student can take class, 0 if not
 */
int classCanBeTaken(char **eligible, char *classBuffer, int sizeEligible) {
    char delim[2] = ",";
    char *classSubject;
    char *classCatalog;
    char copy[COURSE_BUFFER_LEN];
    int i;

    /* copy the className into a new string, parse the name */
    strcpy(copy, classBuffer);
    strtok(copy, delim);
    classSubject = strtok(NULL, delim);
    classCatalog = strtok(NULL, delim);

    /* string them together */
    sprintf(copy, "%s %s", classSubject, classCatalog);

    /* look at each string determine if the student can take it
     * if the current iteration is a match, we can exit the function early */
    for (i = 0; i < sizeEligible; i++) {
        if (strcmp(copy, eligible[i]) == 0) return 1;
    }

    return 0;

}

void printClass(struct class *c) {
    if (c == NULL) {
        err("Class object is null");
    }
    printf("%s %s %s.%s %s--%s %s %s %s Monday:%s\n", c->start, c->subject, c->catalog, c->section, c->start, c->end,
           c->building, c->room, c->name, c->mon);
}

/**
 * The arrays of classes must be sorted by many rules in priority of the following order:
 * Day of week, Mon, Tue,
 * start time in asc
 * course name
 * course number asc
 *
 * this function is the callback fn for the built in qsort() function.
 *
 * IMPORTANT:
 * Different implementations of qsort() use different types of sorting algorithms -
 * they are not all using quicksort internally.
 *
 * GLIBC's implementation of qsort() is actually a merge sort which falls back to quicksort if there is insufficient memory.
 * http://calmerthanyouare.org/2013/05/31/qsort-shootout.html
 *
 * Although it is safe to assume that the mergesort (which is stable) implementation will mostly be used given the scope of this
 * homework assignment, there are ways to guarantee stability in qsort().
 * Paragraph 5 in https://www.gnu.org/software/libc/manual/html_node/Array-Sort-Function.html
 * suggests having a counter to fall back on in case there is an equality, which gets used to guarantee
 * preservation of order.
 *
 * I do this by having a "order" column in the struct class definition. In the final return statement,
 * it resorts to using this to determine placement.
 *
 * Therefore I think this is stable.
 *
 * @param a left
 * @param b right
 * @return < 0 if left should go first
 *         > 0 if right should go first
 *         = 0 if there are the same (this wont happen as no two classes are the same)
 */
int qsortCallback(const void *a, const void *b) {
    int left = strcmp(((struct class *) a)->mon, "Y");
    int right = strcmp(((struct class *) b)->mon, "Y");

    /* whichever class is on monday, takes higher priority in the arr */
    if ((left - right) != 0) return left < right;

    /* if code gets here, either they are both on monday or both on tuesday */
    /* lets compare by start time */
    left = atoi(((struct class *) a)->start);
    right = atoi(((struct class *) b)->start);

    if ((left - right) != 0) return left - right;

    /* compare by course name */
    /* if code is here, they are at the same time */
    left = strcmp(((struct class *) a)->subject, ((struct class *) b)->subject);
    if (left != 0) return left;

    /* if code reaches here, the course names are the same */
    /* compare by course number now */
    left = atoi(((struct class *) a)->catalog);
    right = atoi(((struct class *) b)->catalog);
    if ((left - right) != 0) return left - right;

    /* if code reaches here, their value is equal, so compare by their original order
     * this ensures stability in the algorithm */
    return ((struct class *) a)->order - ((struct class *) b)->order;
}


void freeArray(void **array, int size) {
    int i;
    for (i = 0; i < size; i++)
        free(array[i]);
    free(array);
}

int classHasBeenTaken(struct class *classes, struct class *c, int sizeClasses) {
    int i;
    int subject;
    int catalog;
    struct class *cur;
    for (i = 0; i < sizeClasses; i++) {
        cur = &classes[i];
        subject = strcmp(cur->subject, c->subject);
        catalog = strcmp(cur->catalog, c->catalog);

        /* if class has been taken return 1 */
        if (subject == 0 && catalog == 0) return 1;
    }
    return 0;
}

int timeSlotAvailable(struct class *classes, struct class *c, int sizeClasses) {
    int i;
    struct class * cur;

    /* if there are no classes, return 1 */
    if (sizeClasses == 0) return 1;

    cur = &classes[sizeClasses - 1];

    /* if cur is on a different day than c, return 1 */
    if (strcmp(cur->mon,c->mon) != 0) return 1;

    /* check if the end time of the last class, is less than the start time of new class */
    if (strcmp(cur->end, c->start) < 0) return 1;

//    for (i = 0; i < sizeClasses; i++) {
//        cur = &classes[i];
//        /* check that the start time of c is after the end time of cur. */
//        if (strcmp(cur->end, c->start) < 0) return 1;
//    }
    return 0;
}

char * lookahead(char * time, int minutes) {
    char copy[5];
    int newHour;
    int newMin;
    strcpy(copy, time);
    newHour = atoi(strtok(copy, ":"));
    newMin = atoi(strtok(NULL, ":"));
    printf("%d %d\n", newHour, newMin);

}

/**
 * Produces an array of classes, for a potential schedule for the student.
 *
 * @param eligible
 * @param classes
 * @param sizeEligible
 * @param sizeClass
 * @return array classes sorted by time.
 */
struct class *scheduler(struct class *classes, int sizeClasses) {
    char time[6] = "08:00";
    struct class *schedule = NULL;
    struct class *cur;
    int sizeSchedule = 0;
    int equality;
    int i;
    /* loop over the classes, select the nearest one relative to the time */
    for (i = 0; i < sizeClasses; i++) {
        cur = &classes[i];
        equality = strcmp(time, cur->start);

        /* if the current class start time is == to our current time,
         * and has not been picked,
         * and the student can fit the time in their schedule, select the class. */
        if (
            classHasBeenTaken(schedule, cur, sizeSchedule) == 0 &&
            timeSlotAvailable(schedule, cur, sizeSchedule) == 1) {

            sizeSchedule++;
            insertClass(&schedule, cur, sizeSchedule);
            strcpy(time, cur->end);

        } else {
//            minute = time[3];
//            minute++;
//            time[3] = minute;
            //lookahead(time, 10);
        }
    }

    for (i = 0; i < sizeSchedule; i++) {
        printClass(&schedule[i]);
    }
    return schedule;
}


int main() {
    FILE *fp;
    char buffer[COURSE_BUFFER_LEN];
    char **eligible;
    struct class *classes;
    int sizeEligible = 0, sizeClasses = 0;
    int i;

    fp = fopen("./eligible.txt", "r");

    if (fp == NULL)
        err("Error while opening file");

    while (fgets(buffer, COURSE_BUFFER_LEN, fp) != NULL) {
        sizeEligible++;

        /* terminate the trailing \n on the buffer */
        buffer[strlen(buffer) - 1] = '\0';

        /* grow the array on each iteration */
        insertString(&eligible, buffer, sizeEligible);

    }

    for (i = 0; i < sizeEligible; i++)
        printf("%s\n", eligible[i]);

    /* now read in classes, only include them if eligible. */
    fp = fopen("./fall2019courses.csv", "r");

    if (fp == NULL)
        err("Error while opening file");

    /* skips the first loop before entering the loop */
    fgets(buffer, COURSE_BUFFER_LEN, fp);
    while (fgets(buffer, COURSE_BUFFER_LEN, fp) != NULL) {
        if (classCanBeTaken(eligible, buffer, sizeEligible) == 0) continue;

        sizeClasses++;

        /* terminate the trailing \n on the buffer */
        buffer[strlen(buffer) - 1] = '\0';

        insertClass(&classes, newClassFromBuffer(buffer), sizeClasses);
    }

    /* sort the classes array, day of week, then, start time asc, then course name asc */
    qsort(classes, sizeClasses, sizeof(struct class), qsortCallback);

    for (i = 0; i < sizeClasses; i++) {
        printClass(&classes[i]);
    }

    printf("\n");
    scheduler(classes, sizeClasses);

    freeArray((void *) eligible, sizeEligible);
    free(classes);
    return 0;
}
