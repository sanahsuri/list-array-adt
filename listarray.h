/***********************************************************************
 * List Array
 ***********************************************************************/

/* Conceptual list collection backed by a list of arrays with increasing size.
 * Supports the following operations:
 *  new      - Create a new listarray
 *  size     - Return the number of elements in a listarray
 *  add      - Insert an item at the end of the listarray
 *  get      - Get the item at a given index of the list array
 *  set      - Set the item at a given index of the list array
 *  contains - Determine whether the list array contains a specified item
 *  clear    - free all the memory associated with a listarray
 *
 *  Header author: Jerod Weinman
 */
#ifndef __LISTARRAY_H__
#define __LISTARRAY_H__

#include <stdbool.h>

typedef int data_t;
typedef struct node node_t;

struct node {
  data_t * array;
  unsigned int length;
  node_t * next;
};

typedef struct {
  node_t * first;
  unsigned int size;
} listarray_t;

/* Allocate a new listarray with the specified initial array capacity
 * Precondition:
 *  capacity > 0
 * Postcondition:
 *  Return value is NULL if memory cannot be allocated
 */
listarray_t *
new (unsigned int capacity);

/* Return the current size of the specified list */
unsigned int
size (listarray_t * list);

/* Add the specified item to the end of the collection
 * Preconditions:
 *  list points to a valid listarray_t
 * Produces:
 *  true if the item was added
 * Postconditions:
 *  get (list,size(list)-1) == item
 */
bool
add (listarray_t * list, data_t item);

/* Get the item at the specified index in list
 * Preconditions:
 *  list points to a valid listarray_t
 *  index < size(list)
 * Produces:
 *   item
 * Postcondition:
 *  list is unmodified
 *  item is the element at the specified position in list
 */
data_t
get (listarray_t * list, unsigned int index);

/* Replace the item at the specified index in list
 * Precondition:
 *  list points to a valid listarray_t
 *  index < size(list)
 * Produces:
 *  previous
 * Postcondition:
 *  get(list,index) = item
 *  previous = get(listbefore,index)
 */
data_t
set (listarray_t * list, unsigned int index, data_t item);

/* Determine whether the list contains the specified item
 * Precondition:
 *  list points to a valid listarray_t
 * Postcondition:
 *  list is unmodified
 *  Returns true if there exists an index such that get(list,index)==item
 */
bool
contains (listarray_t * list, data_t item);

/* Clear the contents of the list, releasing all memory
 * Precondition:
 *  list points to a valid listarray_t
 * Postcondition:
 *   all memory associated with list is freed
 *   pointer list can no longer be used */
void
clear (listarray_t * list);


#endif
