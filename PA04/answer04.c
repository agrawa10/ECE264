/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>



/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */
int checkPrime(int number) {
  if (number == 1)
    return 0;
  
  else if (number == 2)
    return 1;

  int divisor = 2;
  int check;
  do {
  check = number % divisor;
  divisor++;
  } while (check != 0 && divisor < number - 1);

  return check;
}

void partition(int n, int value, int index, int arr[], int mode) {
  int i, j, remValue;
  arr[index] = value;
  remValue = (n - value);

  for (i = 1; i <= remValue; i++) {
    switch (mode) { 
      case 1:
        partition(remValue, i, index + 1, arr, mode);
        break;
      case 2:
        if (i > value)
          partition(remValue, i, index + 1, arr, mode);
        break;
      case 3:
        if (i < value)
          partition(remValue, i, index + 1, arr, mode);
        break;
      case 4:
        if (i % 2)
          partition(remValue, i, index + 1, arr, mode);
        break;
      case 5:
        if (!(i % 2))
          partition(remValue, i, index + 1, arr, mode);
        break;
      case 6:
        if ((i - value) % 2)
          partition(remValue, i, index + 1, arr, mode);
        break;
      case 7:
        if (checkPrime(i))
          partition(remValue, i, index + 1, arr, mode);
    }
  }

  if (remValue == 0) {
    printf("= ");
    for (j = 0; j <= index; j++) {
      if (j == index)
        printf("%d\n", arr[j]);
      else
        printf("%d + ", arr[j]);
    }
  }
  return;
} 

void partitionAll(int value) {
  printf("partitionAll %d\n", value);
  int i;
  int *arr = malloc(sizeof(int) * value);
  
  for (i = 1; i <= value; i++) {
    partition(value, i, 0, arr, 1);
  }
  free(arr);
  return;
}
/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionIncreasing(int value)
{
  printf("partitionIncreasing %d\n", value);
  int i;
  int *arr = malloc(sizeof(int) * value);
  
  for (i = 1; i <= value; i++) {
    partition(value, i, 0, arr, 2);
  }
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */


void partitionDecreasing(int value)
{
  printf("partitionDecreasing %d\n", value);
  int i;
  int *arr = malloc(sizeof(int) * value);
  for (i = 1; i <= value; i++) {
    partition(value, i, 0, arr, 3);
  }
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionOdd(int value) {
  printf("partitionOdd %d\n", value);
  int i;
  int *arr = malloc(sizeof(int) * value);
  for (i = 1; i <= value; i++) {
    if (i % 2)
      partition(value, i, 0, arr, 4);
  }
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionEven(int value) {
  printf("partitionEven %d\n", value);
  int i;
  int *arr = malloc(sizeof(int) * value);
  for (i = 1; i <= value; i++) {
    if (!(i % 2))
      partition(value, i, 0, arr, 5);
  }
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from and odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionOddAndEven(int value) {
  printf("partitionOddAndEven %d\n", value);
  int i;
  int *arr = malloc(sizeof(int) * value);
  for (i = 1; i <= value; i++) {
    if (i % 2)
      partition(value, i, 0, arr, 6);
  }
  free(arr);
  return;
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionPrime(int value) {
  printf("partitionPrime %d\n", value);
  int i;
  int *arr = malloc(sizeof(int) * value);
  for (i = 2; i <= value; i++) {
    if (checkPrime(i))
      partition(value, i, 0, arr, 7);
      //printf("%d", i);
  }
  free(arr);
  return;
}
