#ifndef TREE_H
#define TREE_H

typedef struct leaf {
    int value;
    struct leaf *left;
    struct leaf *right;
} TreeNode;

void Huff_postOrderPrint(TreeNode *tree, FILE* fptr);

#endif /* tree.h */

