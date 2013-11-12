#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
    int value; 
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;

HuffNode* HuffNode_build(int data);
HuffNode* HuffNode_specificBuild(HuffNode* a, HuffNode* b);
HuffNode* HuffTree_build(FILE* fptr);
Stack* stack_push(Stack* stack, HuffNode* p);
Stack* stack_pop(Stack* stack);
HuffNode* HuffTree_binBuild(FILE* fptr);
void Huff_postOrderPrint(HuffNode *tree, FILE* fptr);
void HuffTree_destroy(HuffNode* tree);

#endif

