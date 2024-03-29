#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa05.h"
#define MAXIMUM_LENGTH 180

/*
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numInteger: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fscanf
 *
 * You do NOT know how many integers are in the file until you have
 * read it. Once you know how many integers there are, you can modify
 * the "numberOfIntegers" variable. (Note that this is a pointer, not
 * an integer) You must allocate memory to store the integers.
 * 
 * Once memory is allocated to store the integers, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 *
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read integeres is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readInteger(char * filename, int * numInteger) {
  FILE *fp;
  fp = fopen(filename, "r");
  
  if (fp == NULL) {
    return NULL;
  }
  
  int temp;
  *numInteger = 0;
  while (fscanf(fp, "%d", &temp) == 1) {
    (*numInteger)++;
  }
  
  int *arr;
  arr = malloc(sizeof(int) * *numInteger);
  
  fseek(fp, 0, SEEK_SET);
  
  int i = 0;
  while (fscanf(fp, "%d", &arr[i++]) == 1) {
  }

  fclose(fp);
  return arr;
}

/* ----------------------------------------------- */

/* 
 * Read a file of strings. This is similar to readInteger. However,
 * each string is an array of characters. The function needs to
 * allocate memory for an array of strings, i.e., array of arrays of
 * characters. In other words, this is a two-dimensional array (thus,
 * char **).
 * 
 * Arguments:
 * 
 * filename: the name of a file that contains a list of strings (one
 * per line)
 * 
 * numString: pointer to store the number of strings in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 * 
 * Returns:
 *
 * a array of strings from the file, or NULL if *any* error is
 * encountered.
 * 
 * Hint: use fgets. 
 * 
 * Remember that an array of strings is a two-dimensional array of
 * characters
 * 
 * You do NOT know how many strings are in the file until you have
 * read it. Once you know how many strings there are, you can modify
 * the "numberOfStrings" variable. (Note that this is a pointer, not
 * an string) You must allocate memory to store the strings.
 * 
 * Once memory is allocated to store the strings, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 * 
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 * 
 * One way to read stringes is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 * 
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 * 
 * int * ptr = (int *) malloc(sizeof(int) * size);
 * 
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 * 
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of strings in the file.  For example, if
 * you write this
 * 
 * char array[10000];
 * 
 * 
 */

char * * readString(char * filename, int * numString) {
  FILE *fp;
  fp = fopen(filename, "r");
  
  if (fp == NULL) {
    return NULL;
  }
  
  char temp[MAXIMUM_LENGTH];
  *numString = 0;

  while (fgets(temp, MAXIMUM_LENGTH, fp) != NULL) {
    (*numString)++;
  }
  
  char **arr;
  int i = 0;
  arr = malloc(sizeof(char *) * *numString);
  //for (i = 0; i < *numString; i++) {
    //arr[i] = malloc(sizeof(char) * MAXIMUM_LENGTH);
  //}
  
  fseek(fp, 0, SEEK_SET);
  
  //int j = 0;
  while (fgets(temp, MAXIMUM_LENGTH, fp) != NULL) {
    arr[i] = malloc(sizeof(char) * (strlen(temp) + 1));
    strcpy(arr[i], temp);
    i++;
  }
  
  fclose(fp);
  //free(temp);
  return arr;
}

/* ----------------------------------------------- */

/*
 * print an array of integers, one integer per line
 */

void printInteger(int * arrInteger, int numInteger) {
  int i = 0;
  for (i = 0; i < numInteger; i++) {
    printf("%d\n", arrInteger[i]);
  }
}

/* ----------------------------------------------- */

/*
 * print an array of strings, one string per line
 *
 * Hint: printf("%s" ... can print a string
 */
void printString(char * * arrString, int numString) {
  int row;
  for (row = 0; row < numString; row++) {
    printf("%s", arrString[row]);
    int len = strlen(arrString[row]);
    if (len == 0 || arrString[row][len - 1] != '\n') {
      printf("\n");
    }
  }
}

/* ----------------------------------------------- */

/*
 * release the memory occupied by the array of integers
 */
void freeInteger(int * arrInteger, int numInteger) {
  free(arrInteger);
  arrInteger = NULL; //to make sure freed pointer isn't used anymore
}

/* ----------------------------------------------- */

/*
 * release the memory occupied by the array of strings
 *
 * Hint: an array of strings is a two-dimensional array of characters
 */
void freeString(char * * arrString, int numString) {
  int i;
  for (i = 0; i < numString; i++) {
    free(arrString[i]);
  }
  free(arrString);
  arrString = NULL;
}

/* ----------------------------------------------- */

/*
 * Write integers to a file, one integer per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrInteger: an array of integers
 * numInteger: the number of integers 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %d
 *
 */

int saveInteger(char * filename, int * arrInteger, int numInteger) {
  FILE *fp = fopen(filename, "w");
  int i; 
  if (fp == NULL) {
    return 0;
  }
  
  for (i = 0; i < numInteger; i++) {
    fprintf(fp, "%d\n", arrInteger[i]);
  }
  return 1;
}

/* ----------------------------------------------- */

/*
 * Write strings to a file, one string per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrString: an array of strings
 * numString: the number of strings 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %s
 *
 */

int saveString(char * filename, char * * arrString, int numString) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    return 0;
  }
  
  int i;
  for (i = 0; i < numString; i++) {
    fprintf(fp, "%s", arrString[i]);
    
    int len = strlen(arrString[i]);
    if (len == 0 || arrString[i][len - 1] != '\n') {
      fprintf(fp, "\n");
    }
  }
  fclose(fp);
  return 1;
}

/* ----------------------------------------------- */
/*
 * sort an arry of integers by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort 
 *   
 * NOTES  
 *  - size_t refers to the size of an int. It is different for 
 *    different machines.
 *  - void * => Is a pointer but the type can be anything (int *, 
 *    char *, double * ,student *)
 *
 */
int compareInt(const void *p1, const void *p2) {
  //const: the function can read, cannot write
  int *intP1 = (int *) p1; //treat p1 as a pointer to an integer
  int *intP2 = (int *) p2;
  int intV1 = *intP1;
  int intV2 = *intP2;

  if (intV1 < intV2)
    return -1;
  
  if (intV1 == intV2)
    return 0;

  return 1;
}

void sortInteger(int * arrInteger, int numInteger) {
  qsort(&arrInteger[0], numInteger, sizeof(int), compareInt);
}


/* ----------------------------------------------- */
/*
 * sort an arry of strings by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 * Hint: use strcmp in the comparison function
 * 
 * NOTES:
 * C does not have the type for string
 * C uses array of characters for string, one element must be '\0'
 * 
 * string = char *
 * If C had a datatype for string, then
 *   - string *strarr = malloc(sizeof(string) * numElements)
 * But since there is no string datatype in C
 *   - char **strarr = malloc(sizeof(char *) * numElements)
 *   
 */
int compareStr(const void *p1, const void *p2) {
  //p1 stores the address of an element in the array
  //an element is a string, a string is char *
  char **strP1 = (char **) p1;
  char **strP2 = (char **) p2;
  char *strV1 = *strP1;
  char *strV2 = *strP2;
  
  if (strcmp(strV1, strV2) < 0)
    return -1;
  if (strcmp(strV1, strV2) == 0) 
    return 0;
  return 1;
}

void sortString(char * * arrString, int numString) {
  qsort(&arrString[0], numString, sizeof(char *), compareStr);
}
