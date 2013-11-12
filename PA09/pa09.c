#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa09.h"

int main (int argc, char ** argv) {
  if (argc != 3) { //check arguments
    printf("usage: ./pa04 <input file> <output file>\n");
    return EXIT_FAILURE;
  }

  FILE* inputFile = NULL; //initializing input file
  inputFile = fopen(argv[1], "r");
  if (inputFile == NULL) {
    printf("File error!\n");
    return EXIT_FAILURE;
  }
  
  FILE* outputFile = fopen(argv[2], "w");
  if (outputFile == NULL) {
    printf("File error!\n");
    return EXIT_FAILURE;
  }
   
  //printf("Yo_1!\n");  
  if (strstr(argv[2], "bit")) { //argv[2][strlen(argv[2]) - 1] == 't') { 
    //printf("Yo_4!\n");
    HuffNode* p = HuffTree_binBuild(inputFile);
    Huff_postOrderPrint(p, outputFile);
    HuffTree_destroy(p);
  }
  else { 
    HuffNode* p = HuffTree_build(inputFile);
    Huff_postOrderPrint(p, outputFile);
    HuffTree_destroy(p);
  }
  return 0;

}

