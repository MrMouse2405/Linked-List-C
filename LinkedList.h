#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Linked List Data Type
typedef struct LinkedList LinkedList;

/*
    LinkedList *newList()

    - To construct the linked list.
    - Returns reference to the newly
      created list.
 */

LinkedList *newList();

/*

    int getListSize(LinkedList *list)

    - Returns Size of List

 */
int getListSize(LinkedList *list);

/*

    int getListCursorPosition(LinkedList *list)
    - Returns the Position of the Cursor

 */

int getListCursorPosition(LinkedList *list);


/*

    void addToList(LinkedList *list, void *Value)

    - To add a new value to the list.
    - O(1) Time, O(1) Space

 */

void addToList(LinkedList *list, void *Value);

/*

    void * getFromList(LinkedList *list, int Index)

    - Returns a value from the list found at provided index.
     - O(1) to O(n) Time, O(1) Space
 */

void* getFromList(LinkedList *list, int Index);

/*

    void addToListAtIndex(LinkedList *list, int Index)

    - Adds a new element to the list at a given index.
    - O(1) to O(n) Time, O(1) Space

 */

void addToListAtIndex(LinkedList *list, void *Value, int Index);

/*

    void removeFromListAtIndex(LinkedList *list, int Index);

    - Removes a value from the list.
    - O(1) to O(n) Time, O(1) Space

*/

void removeFromListAtIndex(LinkedList *list, int Index);

/*

    void clearList(LinkedList *list)

    - Clears all elements in the list, and collects garbage.
    - O(n) Time, O(1) Space

*/

void clearList(LinkedList *list);


/*

    void deleteList(LinkedList *list)

    - Completely clears all the elements in the list,
      and deletes the list.
    - O(n) Time, O(1) Space

*/

void deleteList(LinkedList *list);


/*

    void forEachElementInList(LinkedList *list, void(*f)(void*))

    - Apply the function f to the elements of the list passed. On each iteration
      the function f is passed the value of that element in the list.
    - O(n) Time, O(1) Space

    Yeah, I stole it from Java, GOT A PROBLEM BRO?

 */

void forEachElementInList(LinkedList *list, void(*f)(void*));


/*

    void BinarySearch(LinkedList *list, void(*Evaluate)(void*),void *Destination, int *Index)

    - Performs a Binary Search on the list, applies the function Evaluate on the indexed element to evaluate it.
    - Once evaluated, it will assign *Destination the value of the node, and *Index the index of the node.
    - Target is the value that you want to search for.
    - Target, Value, and MoveRight are passed onto the function Evaluate each time.
    - Evaluate Function MUST RETURN NON - ZERO VALUE IF TRUE, IT SHOULD RETURN ZERO IF FALSE
    - Evaluate FUNCTION MUST SET MOVERIGHT TO NON-ZERO VALUE IF THE ALGORITHM SHOULD SEARCH ON RIGHT,
    - OR EVALUATE FUNCTION SET MOVERIGHT TO ZERO IF THE ALGORITHM SHOULD SEARCH ON LEFT
    - O(2log(n)) Time, O(1) Space

 */

void BinarySearch(LinkedList *list,void *Target ,int(*Evaluate)(void* Value, void* Target, unsigned short int* MoveRight),void *Destination, int *Index);


#endif
