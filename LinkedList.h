#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define TRUE  1
#define FALSE 0

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

    unsigned int getListSize(LinkedList *list)

    - Returns Size of List

 */
unsigned int getListSize(LinkedList *list);

/*

    unsigned int getListCursorPosition(LinkedList *list)
    - Returns the Position of the Cursor

 */

unsigned int getListCursorPosition(LinkedList *list);


/*

    void addToList(LinkedList *list, void *Value)

    - To add a new value to the list.
    - O(1) Time, O(n) Space

 */

void addToList(LinkedList *list, void *Value);

/*

    void * getFromList(LinkedList *list, int Index)

    - To get a value from the list.
     - O(1) to O(n) Time, O(n) Space
 */

void* getFromList(LinkedList *list, unsigned int Index);


/*

    void forEachElementInList(LinkedList *list, void(*f)(void*))

    - Apply the function f to the elements of the list passed. On each iteration
      the function f is passed the value of that element in the list.
    - O(n) Time, O(1) Space

    Yeah, I stole it from Java, GOT A PROBLEM BRO?

 */

void forEachElementInList(LinkedList *list, void(*f)(void*));


/*

    void BinarySearch(LinkedList *list, void(*Evaluate)(void*),void *Destination, unsigned int *Index)

    - Performs a Binary Search on the list, applies the function Evaluate on the indexed element to evaluate it.
    - Once evaluated, it will assign *Destination the value of the node, and *Index the index of the node.
    - Target is the value that you want to search for.
    - Target, Value, and MoveRight are passed onto the function Evaluate each time.
    - Evaluate Function MUST RETURN NON - ZERO VALUE IF TRUE, IT SHOULD RETURN ZERO IF FALSE
    - Evaluate FUNCTION MUST SET MOVERIGHT TO NON-ZERO VALUE IF THE ALGORITHM SHOULD SEARCH ON RIGHT,
    - OR EVALUATE FUNCTION SET MOVERIGHT TO ZERO IF THE ALGORITHM SHOULD SEARCH ON LEFT
    - O(2log(n)) Time, O(1) Space

 */

void BinarySearch(LinkedList *list,void *Target ,int(*Evaluate)(void* Value, void* Target, unsigned short int* MoveRight),void *Destination, unsigned int *Index);


#endif
