#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/* DO NOT MODIFY THIS FUNCTION!!! */
void Huff_postOrderPrint(TreeNode *tree, FILE* fptr) {
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
