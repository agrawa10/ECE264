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

HuffNode* HuffTree_binBuild(FILE* fptr) {
  int i = 1;
  //int j = 0;
  unsigned char byteOne, byteTwo, data;

  Stack* stack = NULL;
  
  byteOne = fgetc(fptr);
  //printf("Original Byte: %d\n", byteOne);
  //printf("%d\n", (1 << (8 - i)));
  do {
    //printf("Mask: %d\n", (1 << (8 - i)));
    //printf("Byte: %d\n", byteOne);
    //printf("%d\n", byteOne & (1 << (8 - i)));
    //printf("i:  %d\n", i);
     
    if (byteOne & (1 << (8 - i))) {
      //printf("ByteOne: %d\n", byteOne);
      //printf("Mask: %d\n", (1 << (8 - i)));
      //printf("Masked Result: %d\n", byteOne & (1 << (8 - i)));
      byteTwo = fgetc(fptr);
      //printf("ByteTwo: %d\n", byteTwo);
      data = (byteOne << i) | (byteTwo >> (8 - i));
      stack = Stack_push(stack, HuffNode_build(data));
      byteOne = byteTwo;
      //printf("Overwritten ByteOne: %d\n", byteOne);
    }
    
    else { //command is zero
      //printf("Yo!\n");
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
    
    if (i == 8) {
      byteOne = fgetc(fptr);
      i = 1;
      //j++;
    }
    else
      i++; 
    //if (j == 5) break;
  } while(stack != NULL);
  return NULL;
}

void Huff_postOrderPrint(HuffNode *tree, FILE* fptr) {
  // Base case: empty subtree
  if (tree == NULL) {
    return;
  }

  // Recursive case: post-order traversal

  // Visit left
  fprintf(fptr, "Left\n");
  Huff_postOrderPrint(tree->left, fptr);
  fprintf(fptr, "Back\n");

  // Visit right
  fprintf(fptr, "Right\n");
  Huff_postOrderPrint(tree->right, fptr);
  fprintf(fptr, "Back\n");

  // Visit node itself (only if leaf)
  if (tree->left == NULL && tree->right == NULL) {
    fprintf(fptr, "Leaf: %c\n", tree->value);
  }
}

void HuffTree_destroy(HuffNode *tree) {
  if (tree -> left != NULL)
    HuffTree_destroy(tree -> left);
  if (tree -> right != NULL)
    HuffTree_destroy(tree -> right);
  free(tree);
  return;
}
