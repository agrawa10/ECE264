#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create() {
  Stack* p = malloc(sizeof(Stack));
  p -> list = NULL;
  return p;
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */
void List_destroy(ListNode* p) {
  if (p == NULL)
    return; //nothing to free
  List_destroy(p -> next);
  free(p);
}

void Stack_destroy(Stack * stack) {
  if (stack == NULL)
    return;
  ListNode* p = stack -> list;
  List_destroy(p);
  free(stack);
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack) {
  if (stack -> list == NULL)
    return TRUE;
  return FALSE;
}

/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack) {
  ListNode* p = stack -> list;
  stack -> list = p -> next;
  int val = p -> value;
  free(p);
  return val;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value) {
  ListNode* p = malloc(sizeof(ListNode));
  p -> value = value;
  p -> next = stack -> list;
  stack -> list = p;
}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
 * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len) {
  int write_index = 0;
  int ind;
  Stack* stack = Stack_create();
    
  for (ind = 0; ind < len; ind++) {
    while (stack -> list != NULL && array[ind] > (stack -> list) -> value) {
      array[write_index] = Stack_pop(stack);
      write_index++;
    }
    Stack_push(stack, array[ind]);
  }
  
  while (stack -> list != NULL) {
    array[write_index] = Stack_pop(stack);
    write_index++;
  }
}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */
int maxInd(int* array, int len) {
  int ind;
  int max = 0;
  for (ind = 1; ind < len; ind++) {
    if (array[ind] > array[max])
      max = ind;
  }
  return max;
}

int minInd(int* array, int len) {
  int ind;
  int min = 0;
  for (ind = 1; ind < len; ind++) {
    if (array[ind] < array[min])
      min = ind;
  }
  return min;
}

int isStackSortable(int * array, int len) {
  if (len < 3)
    return TRUE;

  int max = maxInd(array, len);
  if (max == 0)
    return isStackSortable(array + 1, len - 1);

  else if (max == len - 1)
    return isStackSortable(array, len - 1);

  else if ((isStackSortable(array, max) && isStackSortable((array + max + 1), (len - max - 1)))) {
    int leftMax = maxInd(array, max);
    int rightMin = minInd((array + max + 1), (len - max - 1));
    rightMin += max + 1;
    if (array[leftMax] < array[rightMin])
      return TRUE;
  }
  return FALSE;
}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [0..k-1] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */
void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void permute(int* arr, int ind, int len) {
  if (ind == len) {
    if (isStackSortable(arr, len)) { 
      TreeNode* p = Tree_build(arr, len);
      Tree_printShape(p);
      Tree_destroy(p);
    }
    return;
  }
  
  int i;
  for (i = ind; i < len; i++) {
    swap((arr + i), (arr + ind));
    permute(arr, ind + 1, len);
    swap((arr + i), (arr + ind));
  }
}
  
void genShapes(int k) {
  int ind;
  int* arr = malloc(sizeof(int) * k);
  
  for (ind = 0; ind < k; ind++) {
    arr[ind] = ind;
  }
  permute(arr, 0, k);
  free(arr);
}
