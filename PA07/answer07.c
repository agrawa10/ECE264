#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

Node *List_search(Node *head, int index) {
  Node *p = head;
  while (p != NULL) {
    if (p -> index == index) {
      return p;
    }
    p = p -> next;
  }
  return p;
}

/**
 * Prints a linked-list "head" into the output fie "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head) {
  while(head != NULL) {
    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
    head = head -> next;
  }
  printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head) {
  while(head != NULL) {
    Node* p = head -> next;
    free(head);
    head = p;
  }
}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index) {
  Node *p = malloc(sizeof(Node));
  p -> value = value;
  p -> index = index;
  p -> next = NULL;
  return p;
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
 * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
 * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length) {
  Node* head = NULL;
  int i;
  for (i = 0; i < length; i++) {
    head = List_insert_ascend(head, value[i], index[i]);
  }
  return head;
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index) {
  if (value == 0)
    return head;
  
  if(head == NULL) {	
    head = List_create(value,index);
    return head;
  }
  
  Node *current = head;
  if ((current -> index) > index) { //Insert before the first element
    current = List_create(value, index);
    current -> next = head;
    return current;
  }
  
  Node *previous = current;
  current = current -> next;
  while (current != NULL) { //Keep iterating until either greater index found or last element reached
    if ((current -> index) > index) { //Greater index found
      previous -> next = List_create(value, index);
      previous = previous -> next;
      previous -> next = current;
      return head;
    }
    else {
      previous = current;
      current = current -> next;
    }
  }
  
  previous -> next = List_create(value, index); //If no greater index available, append to end of list
  return head;
}


/**
 * This function deletes the node with the passed "index"
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 */
Node * List_delete(Node * head, int index) {
  if (head == NULL)
    return NULL;
  
  if (head -> index == index) {
    Node *p = head -> next;
    free(head);
    head = p;
    return p;
  }
  
  head -> next = List_delete(head -> next, index);
  return head;
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */
Node * List_copy(Node * head) {
  Node *p;
  if (head != NULL) {
    p = List_create(head -> value, head -> index);
    p -> next = List_copy(head -> next);
  }

  else
    p = NULL;
  return p;
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * List_merge(Node * head1, Node * head2) {
  Node *p = List_copy(head1);
  Node *q = NULL;

  if (head2 != NULL) {
    if ((q = List_search(p, head2 -> index))) { //Search of current head2 index in p successful
      int sum = q -> value + head2 -> value;
      if (sum == 0)
        p = List_delete(p, q -> index);
      else
        q -> value = sum;
    }
    else //If search unsuccessful, insert node pointed by head2 into p
      p = List_insert_ascend(p, head2 -> value, head2 -> index);
    
    q = p; //save address of p for freeing later
    p = List_merge(p, head2 -> next);
    List_destroy(q);

    return p;
  }
  
  else
    return p;
}

