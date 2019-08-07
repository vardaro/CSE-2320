/* Anthony Vardaro 1001522383 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COURSE_BUFFER_LEN 100
#define START_OF_DAY      "08:00"


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

/**
 * Dynamically inserts a string into a string array of size size
 * @param array array to modify
 * @param str string to insert
 * @param size size of array
 */
void insertString(char ***array, char *str, int size) {
    /* Grow the array with a temp array, push the new string,
     * and set array = temp before exiting. */
    char **temp = realloc(*array, size * sizeof(char *));
    if (temp == NULL)
        err("Unable to realloc array");
    temp[size - 1] = (char *) malloc(strlen(str) * sizeof(char));
    strcpy(temp[size - 1], str);

    *array = temp;
}

/**
 * Dynamically inserts a struct class into a struct class array of size size.
 * @param array array to modify
 * @param c struct class to insert
 * @param size size of class array
 */
void insertClass(struct class **array, struct class *c, int size) {
    /* Reallocate the array using a temp array.
     * modify the temp array and set the original array = temp. */
    struct class *temp = realloc(*array, size * sizeof(struct class));
    if (temp == NULL)
        err("Unable to realloc array");

    /* set the order of placement for this instance */
    c->order = size;

    temp[size - 1] = *c;
    *array = temp;
}

/**
 * Returns a bool denoting if the kiddo can take the class
 * @param eligible string array of classes the student can take.
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
/**
 * Prints a struct class
 * @param c struct class
 */
void printClass(struct class *c) {
    char * temp;
    if (c == NULL) {
        err("Class object is null");
    }

    strcpy(temp, c->building);
    strcat(temp, " ");
    strcat(temp, c->room);
    printf("%s ", c->start);
    printf("%5s ", c->subject);
    printf("%s.%s  ", c->catalog, c->section);
    printf("%s--%s  ", c->start, c->end);
    printf("%-7s", temp);

    printf("  %s\n", c->name);

/*    printf("%s %5s %s.%s  %s--%s  %s %3s  %s\n", c->start, c->subject, c->catalog, c->section, c->start, c->end,
          c->building, c->room, c->name); */
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
/**
 * Returns a bool denoting whether c can be taken given context.
 *
 * @param classes struct class array, containing all the classes the
 *        student has signed up for.
 * @param c class the student wishes to apply for.
 * @param sizeClasses number of classes in array.
 * @return integer 1 if class has already been taken, 0 if not.
 */
int classHasBeenTaken(struct class *classes, struct class *c, int sizeClasses) {
    int i;
    int subject;
    int catalog;
    struct class *cur;

    /*
     * Loop over all the classes already scheduled
     * If the current iteration is equal to the potential class to sign up for -
     * return 1 (to indicate this class is already signed up for)/
     */
    for (i = 0; i < sizeClasses; i++) {
        cur = &classes[i];
        subject = strcmp(cur->subject, c->subject);
        catalog = strcmp(cur->catalog, c->catalog);

        /* if class has been taken return 1 */
        if (subject == 0 && catalog == 0) return 1;
    }
    return 0;
}

/**
 * Returns a bool denoting whether the class c can be schedule given the calender of the student.
 * The idea is that if end time of the latest class in the student schedule is less than the
 * start time of the class we want to add, the class can be easily scheduled.
 * @param classes array of struct classes
 * @param c class we want to add
 * @param sizeClasses number of classes already signed up for.
 * @return 1 if the student can fit class in schedule, 0 if not.
 */
int timeSlotAvailable(struct class *classes, struct class *c, int sizeClasses) {
    struct class * cur;

    /* if the class is before the predefined start of the day return 0*/
    if (strcmp(START_OF_DAY, c->start) > 0) return 0;

    /* if there are no classes, return 1 */
    if (sizeClasses == 0) return 1;

    cur = &classes[sizeClasses - 1];

    /* if cur is on a different day than c, return 1 */
    if (strcmp(cur->mon,c->mon) != 0) return 1;

    /* check if the end time of the last class, is less than the start time of new class */
    if (strcmp(cur->end, c->start) < 0) return 1;

    return 0;
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
    struct class *schedule = NULL;
    struct class *cur;
    int sizeSchedule = 0;
    int i;
    /* loop over the classes, select the nearest one relative to the time */
    for (i = 0; i < sizeClasses; i++) {
        cur = &classes[i];

        /* if the current class start time is == to our current time,
         * and has not been picked,
         * and the student can fit the time in their schedule, select the class. */
        if (
            classHasBeenTaken(schedule, cur, sizeSchedule) == 0 &&
            timeSlotAvailable(schedule, cur, sizeSchedule) == 1) {

            sizeSchedule++;
            insertClass(&schedule, cur, sizeSchedule);

        }
    }



    /* print the array and exit */
    printf("***  Monday schedule  ***\n");
    for (i = 0, cur = &schedule[i]; strcmp(schedule[i].mon, "Y") == 0 && i < sizeSchedule; i++) {

        printClass(&schedule[i]);
    }

    printf("\n***  Tuesday schedule  ***\n");
    for (;i < sizeSchedule; i++) {
        printClass(&schedule[i]);
    }

    free(schedule);
}


int main() {
    FILE *fp;
    char buffer[COURSE_BUFFER_LEN];
    char **eligible;
    struct class *classes;
    int sizeEligible = 0, sizeClasses = 0;

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

    scheduler(classes, sizeClasses);

    freeArray((void *) eligible, sizeEligible);
    free(classes);
    return 0;
}
