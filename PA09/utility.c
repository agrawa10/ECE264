#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

HuffNode* HuffNode_build(int data) {
  HuffNode* p = malloc(sizeof(HuffNode));
  p -> value = data;
  p -> left = NULL;
  p -> right = NULL;
  return p;
}

HuffNode* HuffNode_specificBuild(HuffNode* a, HuffNode* b) {
  HuffNode* p = malloc(sizeof(HuffNode));
  p -> value = 0;
  p -> left = a;
  p -> right = b;
  return p;
}

Stack* Stack_push(Stack* stack, HuffNode* p) {
  Stack* q = malloc(sizeof(Stack));
  q -> next = stack;
  q -> node = p;
  return q;
} 

Stack* Stack_pop(Stack* stack) {
  Stack* q = stack -> next;
  free(stack);
  stack = q;
  return stack;
}
  
/* The function creates a Huffman Tree
*
* Arguments:
* FILE*        input file
* 
* returns:
* HuffNode*    the head of the Huffman Tree
*/
HuffNode* HuffTree_build(FILE* fptr) {
  int c, data;
  Stack* stack = NULL; 
  do {
    c = fgetc(fptr);

    if (c == '1') {
      data = fgetc(fptr);
      stack = Stack_push(stack, HuffNode_build(data));
    }
    
    else { //command is zero
      HuffNode* a = stack -> node;
      stack = Stack_pop(stack);
      if (stack == NULL)
        return a;
      else {
        HuffNode* b = stack -> node;
        stack = Stack_pop(stack);
        stack = Stack_push(stack, HuffNode_specificBuild(b, a));
      }
    }
  } while(stack != NULL);
  return NULL;
}
