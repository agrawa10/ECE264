#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"
#include "tree.h"

int main (int argc, char ** argv) {
  if (argc != 3) { //check arguments
    printf("usage: ./pa04 <input file> <output file>\n");
    return EXIT_FAILURE;
  }

  FILE* fptr = NULL; //initializing input file
  fptr = fopen(argv[1], "r");
  if (fptr == NULL) {
    printf("File error!\n");
    return EXIT_FAILURE;
  }

  HuffNode* p = HuffTree_build(fptr);
  Huff_postOrderPrint((TreeNode*) p);
  return 0;

}

