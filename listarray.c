/***********************************************************************
 * List Array
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "listarray.h"

listarray_t *
new (unsigned int capacity)
{
  // assertions verifying preconditions
  assert (capacity > 0);

  // allocating space for a new list
  listarray_t * list = (listarray_t *) malloc (sizeof (listarray_t));
  // checking if space was allocated
  if (! list)
  {
    perror("Could not allocate space for new list");
    return NULL;
  }

  // allocating space for first node
  list->first = (node_t *) malloc (sizeof (node_t));
  // checking if space was allocated
  if (! list->first)
  {
    perror("Could not allocate space for new node");
    return NULL;
  }

  // allocating space for an array in first node
  list->first->array = (data_t *) malloc (capacity * sizeof(data_t));
  // checking if space was allocated
  if (! list->first->array)
  {
    perror("Could not allocate space for new array");
    return NULL;
  }

  list->first->length = capacity; // setting length to input capacity
  list->first->next = NULL; // setting next node to NULL
  list->size = 0; // initializing list size to 0

  return list;
} // new

unsigned int
size (listarray_t * list)
{
  return list->size; // returns size of list
} // size

/* Get pointer to data at specified index
 * Precondition:
 *  index <= size(list) [Note: equality allowed for add() function]
 * Postcondition:
 *  returns address of data item or NULL
 *  if returns NULL and last is not NULL, changes last to point to last node
 */
data_t *
get_ptr (listarray_t * list, unsigned int index, node_t ** last)
{
  // assertions verifying preconditions
  assert(index <= list->size);
  assert(index >= 0);

  node_t * current = list->first; // node pointing to first node in list
  node_t * prev = NULL; // initializing a node

  // traversing through list to find node with item at index

  while (current != NULL && index >= current->length)
  {
    prev = current;
    // finding difference between index and length of the current node array
    // index gets subtracted from till index in current array is reached
    index -= current->length;
    // setting current to next node
    current = current->next;
  } // while

  // if function has reached end of last node (index == size(list))
  if (index == 0 && current == NULL)
  {
    if (last != NULL)
      *last = prev; // node before current points to last instead of NULL
    return NULL;
  } // if
  return &(current->array[index]);
} // get_ptr


bool
add (listarray_t * list, data_t item)
{
  // assertions verifying preconditions
  assert (list != NULL);

  unsigned int initial_size = list->size; // initializing variable to store size
  node_t * last;
  // storing the address of the item at index initial_size

  data_t * address = get_ptr(list, initial_size, &last);


  if (address == NULL)
  {
    // allocating space for a new node
    node_t * new_node = (node_t *) malloc (sizeof(node_t));
    // checking if space was allocated
    if (! new_node)
    {
      perror("Could not allocate space for new node");
      return false;
    }
    // assign last node in the list to point to new node
    last->next = new_node;
    // length of new node is twice the length of node before it
    new_node->length = 2 * last->length;
    // allocating space for array in new_node
    new_node->array = (data_t *) malloc (new_node->length * sizeof(data_t));
    // checking if space was allocated
    if (! new_node->array)
    {
      perror("Could not allocate space for new array");
      return false;
    }
    new_node->next = NULL;
    new_node->array[0] = item; // setting first position of array as item
  }
  else // if address != NULL (returns a valid address)
  {
    *address = item;
  }

  list->size++; //incrementing size of list
  return true;
} // add

data_t
get (listarray_t * list, unsigned int index)
{
  // assertions verifyng preconditions
  assert (list != NULL);
  assert (index < list->size);

  // find address of item at index and return it
  data_t * address = get_ptr(list, index, NULL);
  return *address;
} // get

data_t
set (listarray_t * list, unsigned int index, data_t item)
{
  // assertions verifyng preconditions
  assert (list != NULL);
  assert (index < list->size);

  // find address of item at index
  data_t * address = get_ptr(list, index, NULL);
  // initialize a variable to store value at address
  data_t previous = *address;
  // set value at address to item
  *address = item;
  return previous; // return previous value at address
} // set

bool
contains (listarray_t * list, data_t item)
{
  // assertions verifyng preconditions
  assert (list != NULL);

  // traversing through list to find item
  for (int index = 0; index < list->size; index++)
  {
    if (get(list, index) == item)
      return true; // if item found return true
  } // for
  return false; // if item not found return false
}

void
clear (listarray_t * list)
{
  // assertions verifying preconditions
  assert (list != NULL);

  // initialize a current node to keep track of list traversal
  node_t * current = list->first;

  while (current != NULL)
  {
    node_t * temp = current->next;
    free(current->array); // free array at current
    free(current); // free current
    current = temp; // move on to next node
  } // while

  free(list); // free whole list
} // clear
