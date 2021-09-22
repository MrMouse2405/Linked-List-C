# Linked Lists
A C Linked List Library Created For Personal Use. 

## Optimized for Accessing Elements
Usually, Linked Lists cost Time Complexity of O(n) for accessing any element, but this library uses special algorithm that can drastically reduce Time Complexity for accessing elements.

Time Complexity Per Algorithm (For accessing elements)

Linear Search
- O(1)

Binary Search:
- O(n)     : Acccesing First Time
- O(log(n) : Accessing Second Time.

## Garbage Collection
Comes with built in garbage collection. `void clearList(LinkedList *list)` and `void deleteList(LinkedList *list)` allow users to delete elements stored in linked list and even the linked list itself.


## API
Read Header File.

## Notes
- The LinkedList stores Void Pointers. It only stores void pointers to allow users to store references to any type of data.
- It's recommend to store the values in heap memory and then store their references in the list. Mostly to avoid stack smahing and undefined behavoir.
- You can store values in stack memory, but remember, these values stored on stack are <b> Local to their scope</b>. 

## Code Example

```c
#include "LinkedList.h" // Include the header file.

LinkedList *list = newLinkedList();

int a = 2;

// Library Stores Void Pointers, it stores void pointers to allow users to store any type of value.
void *b = &a;

// To store a value in the list
addToList(list,b);

// To get a value from the index.
void *c = getFromList(list,0);

// To clear all elements in a list
clearList(list);

// To completely delete the list, including elements in it.
deleteList(list);

```


