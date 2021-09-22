/*
    Fast Access Linked List

    Linked Lists are an alternative to Arrays to store and arrange values.
    Linked lists are preferred over Arrays when you need to re-arrange values.

    Arrays cost time complexity of O(n) for re-arranging values as we will have
    to shift all the values in an array. While in a linked list, it costs time
    complexity of O(1), as we will only have to update the memory addresses of the two nodes (before and after).

    To access a value in an Array is wonderfully inexpensive, as we can quickly access it by
    indexing the value (O(1) time complexity). While in a linked list, it's expensive, as we
    will have to transverse from the head node (the first node) and keep on transversing through nodes
    until we find the value (O(n) time complexity).

    Since accessing values in a linked list is performance expensive,
    we have made a custom implementation, which I would call a Fast Access Linked List.

    In a Fast Access Linked List, to improve performance, we are caching two values;
    "Cursor" and "NodeAtCursor."

    To understand how this works, let's use an example.

    Let's say we are trying to print out all the values stored in the list.

     -  If we try to access the first value, at index 0, the program will
        return the value stored at the head node.

     -  If we try to access the second value, at index 1, the program transverses
        through the list and returns the value stored in the node at index 1.
        The "Cursor" variable will store the value 1, and "NodeAtCursor" will
        point to this node at index 1.

     -   And If we try to access the third value stored at index 2. This time the program
        will start from the node referenced by "NodeAtCursor" and transverses through the list
        until it finds the node at index 2 and returns it. Then it will increment the "Cursor" value,
        and "NodeAtCursor" will now point to the node at index 2. Hence, saving performance because
        it doesn't have to start from index 0 again.

    The program will continue this pattern for accessing values for all indices,
    if the "Cursor" value is greater than the index of the value we want, let's say the "Cursor" is 3,
    and we want value at index 1, the program will transverse through the list backwards,
    and if the index is greater, vice versa.

    If the index is the same as the cursor, the program will return the value stored in a node that's
     referenced by the "NodeAtCursor"

     The program also checks which route to access the node will take less hops
     For example:
         - Will it take less hops if we start from NodeAtCursor?
         - Will it take less hops if we start from Head Node?
         - Will it take less hops if we start from Tail Node?

    This custom implementation drastically reduces the time complexity for linear search [O(n)].
    Dropping time complexity from O(n + n) to O(n+1). This even reduces time complexity for Binary Search [O(log(n))],
    from O(log(n) + n) to  O(log(n) + log(n))

    So in brief, this custom implementation was made for using Linear Search And Binary Search.

 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

/*

    Node

    Each node stores a void pointer. This pointer points to
    the value stored in the node.

    Since this is a Doubly Linked List, Meaning, the Nodes
    have reference to two pointers. One of them points to
    the node that comes before the node, the next points to the
    node that comes after it.

    If the Node is a head node (meaning first node) the "Last" value will
    be NULL, if the node is a tail node(meaning last node) the "Next" value
    will be null.

 */

typedef struct Node {

    // Pointer to the value
    void *Value;

    // Next Node
    struct Node *Next;

    // Last Node
    struct Node *Last;

} Node;

/*

    Linked List

    This structure stores references to Head and Tail of the list.

    Also stores other important information, such as Size of the list,
    Cursor value, and NodeAtCursor.

    Every instance of Linked List has this structure even if the size of
    the list is ZERO, because this structure holds important information
    for the LinkedList
 */

typedef struct LinkedList {

    // The Top Node
    Node *Head;

    // The End Node
    Node *Tail;

    // Size
    unsigned int Size;

    // Recently accessed Node's Index
    unsigned int Cursor;

    // Recently accessed Node
    Node  *NodeAtCursor;

} LinkedList;


/*

  LinkedList * newList()

  This function initializes a new LinkedList in heap memory,
  and returns the reference to it.

*/

LinkedList * newList() {

    // Initialising in Heap and casting it to our data type
    LinkedList *newList = (LinkedList *) malloc (sizeof(struct LinkedList));

    // Setting default values
    newList->Head = NULL;
    newList->Tail = NULL;
    newList->Size = 0;
    newList->Cursor = 0;
    newList->NodeAtCursor = NULL;

    // Returning the reference to the list
    return newList;
}

/*

    unsigned int getListCursorPosition(LinkedList *list)
    - Returns the Position of the Cursor

 */

unsigned int getListCursorPosition(LinkedList *list) {
    return list->Cursor;
}

/*

    unsigned int getListSize(LinkedList *list)
    - Returns the size of the list

 */

unsigned int getListSize(LinkedList *list) {
    return list->Size;
}

/*

    void *add(LinkedList *list, void *Value)

    This function initializes a new node in heap memory
    and assigns the value of node to the provided value.

*/

void addToList(LinkedList *list, void *Value) {

    // Initialising new node in heap and casting it to our data type.
    Node *newNode = (Node *) malloc (sizeof(struct Node));

    // Assigning values
    newNode->Value = Value;
    newNode->Next  = NULL;
    newNode->Last = NULL;

    // Increment The Size
    list->Size++;

    // If it's the first element (Size==1 means first)
    if (list->Size == 1) {

        // Make head point to this node, because it's the first
        list->Head = newNode;

        // Make the tail point to this node,because it's also the last element
        list->Tail = newNode;

        // Make the NodeAtCursor point this node, because currently the cursor is at index 0.
        list->NodeAtCursor = newNode;

    }

    // If elements already exist in list (Size > 1)
    else {

        // Get Tail Node (last node)
        Node *lastNode = list->Tail;

        // Set Tail Node's Next value to this node.
        lastNode->Next = newNode;

        // Set newNode's Last value to Tail Node (interconnect each other)
        newNode->Last = lastNode;

        // Now set Tail Node's address to this Node (because now this is the last node)
        list->Tail = newNode;

    }

}

/*

    static Node* get(LinkedList *list, int Index)

    This function returns the node located at a
    given index.

    This function is abstracted. Hence, its static.
    Use getFromList to access a value externally.

 */


static Node* get(LinkedList *list, unsigned int Index) {

    // If Index is 0, the First Node, then return head node
    if (Index <= 0) // // <= for binary search, sometimes values loose precision because of integer division
        return list->Head;

    // If Index is the last index, the Last Node (Size - 1), then return tail node
    if (Index >= list->Size - 1) // >= for binary search, sometimes values loose precision because of integer division
        return list->Tail;

    // If Index is same as the cursor value, then return the NodeAtCursor
    if (Index == list->Cursor)
        return list->NodeAtCursor;



    /*

        Travelling through the list to find out value.
        Because the index was not 0, or Size - 1, or Cursor.

     */



    // To cache the node to start transversing from
    Node **curNode = NULL;

    // To know which path we have chosen [ 1: Head, 2: Tail, 0: Cursor]
    #define HEAD 1
    #define TAIL 2
    #define CURSOR 0

    int  ChosenPath = CURSOR;

    /*

        Calculating which is the best way to access the values.
        In simple words, we are calculating which way will require
        the least amount of hops to access our node:
         - Will it take less hops if we start from NodeAtCursor?
         - Will it take less hops if we start from Head Node?
         - Will it take less hops if we start from Tail Node?

     */

    // Calculating The Distance
    unsigned int DistanceFromHead = Index;
    unsigned int DistanceFromTail = (list->Size-1) - Index;
    unsigned int DistanceFromCursor = abs(list->Cursor - Index);

    // If Closest Path Is From Head
    // <= to handle stalemate situationsWhat if DistanceFromHead == DistanceFromTail?.
    if (DistanceFromHead <= DistanceFromCursor && DistanceFromHead <= DistanceFromTail) {
        curNode = &list->Head;
        ChosenPath = HEAD;
    }
        // If Closest Path Is From Tail (We have checked If DistanceFromHead is Greater than DistanceFrom Tail,
        // it's not right? It means it bigger from DistanceFromTail so we didn't check DistanceFromTail < DistanceFromCursor)
    else if (DistanceFromTail < DistanceFromCursor) {
        curNode = &list->Tail;
        ChosenPath = TAIL;
    }
        //Well then, looks like the closest distance is from Cursor
    else
        curNode = &list->NodeAtCursor;

    /*

      Travelling through list, by our chosen path

     */

    switch (ChosenPath) {

        /*

         Path: HEAD

         If the chosen path is HEAD,
         then move from start towards right, AKA Forward

        */

        case HEAD: {

            // Start Moving Forwards From Head, until we find the Node we want
            for (unsigned int i = 0; i < DistanceFromHead; ++i) {
                curNode = &(((Node *) (*curNode))->Next);
            }

            // Update the Cursor Value ( Cursor Value == DistanceFromHead because, that's the node we are at now)
            list->Cursor = DistanceFromHead;

            // Make the NodeAtCursor point towards this.
            list->NodeAtCursor = *curNode;

            break;
        }

            /*

            Path: TAIL

            If the chosen path is TAIL,
            then move from end towards left, AKA Backward

            */


        case TAIL: {

            // Start Moving Backwards From TAIL, until we find the Node we want
            for (unsigned int i = 0; i < DistanceFromHead; ++i) {
                curNode = &(((Node *) (*curNode))->Last);
            }

            // Update the Cursor Value (We are subtracting list size from DistanceFromTail,
            // because that's how many node's we are away from the list's end)
            list->Cursor = (getListSize(list) - 1) - DistanceFromTail;
            printf("%i\n", list->Cursor);

            // Make the NodeAtCursor point towards this.
            list->NodeAtCursor = *curNode;


            break;
        }

            /*

            Path: CURSOR

            If the chosen path is Cursor,
            and if the Index is greater than the CURSOR,
            then move from cursor towards right, AKA Forward
            else if the Index is lesser than the CURSOR,
            then move from cursor towards left, AKA Backward

            */


        default: {

            // If the index is greater than the cursor, then move right
            if (Index > list->Cursor) {

                // Start Moving Forward
                for (unsigned int i = 0; i < DistanceFromCursor; ++i) {
                    curNode = &(((Node *) (*curNode))->Next);
                }

                // Update Cursor Value (adding because we moved forward)
                list->Cursor += DistanceFromCursor;

            }

                // Else if the index is lesser than the cursor, then move left
            else {

                // Start Moving Backward
                for (unsigned int i = 0; i < DistanceFromCursor; ++i) {
                    curNode = &(((Node *) (*curNode))->Last);
                }


                // Update Cursor Value (subtracting because we moved forward)
                list->Cursor -= DistanceFromCursor;
            }

            // Update NodeAtCursor Value
            list->NodeAtCursor = *curNode;

            break;
        }
    }


    curNode = &list->NodeAtCursor;

    return (Node*)(*curNode);
}


/*

    void* getFromList(LinkedList *list, int Index)

    This function returns a value from stored
    in the node found at the index

 */

void* getFromList(LinkedList *list, unsigned int Index) {
    return get(list,Index)->Value;
}

/*

    void addToListAtIndex(LinkedList *list, unsigned int Index)

    Adds a new element to the list at a given index.

 */

void addToListAtIndex(LinkedList *list, void *Value, unsigned int Index) {

    if (Index < 0 || Index >= list->Size) {
        printf("INDEX OUT OF BOUNDS EXCEPTION. ATTEMPT TO INDEX INVALID INDEX %i\n",Index);
        exit(-1);
    }

    Node *newNode  = (Node *) malloc(sizeof(struct Node));
    newNode->Value = Value;
    newNode->Next  = NULL;
    newNode->Last  = NULL;

    Node *CurNode    = NULL;
    Node *NodeBefore = NULL;


    // If Index is 0, adding the node at the start of the list.
    if (Index == 0) {

        // Cache head node's reference to CurNode
        CurNode = list->Head;

        // Set Head Node's Last Node Value to new node
        CurNode->Last = newNode;

        // Set new node's next value to head node ( connecting each other )
        newNode->Next = CurNode;

        // Now set list's head to new node, because that's our new head node now right?
        list->Head = newNode;

    }

    // If Index is the last index, adding the node at the end of the list.
    else if (Index == list->Size - 1) {

        // Cache tail node's reference to CurNode
        CurNode = list->Tail;

        // Set Tail Node's Next Value to new node
        CurNode->Next = newNode;

        // Set new node's last value to head node ( connecting each other )
        newNode->Last = CurNode;

        // Now set list's tail to new node, because that's our new tail node now right?
        list->Tail = newNode;

    }

    //Well, if the index is somewhere between, we need to find the particular node at index now.
    else {

        // Cache reference to the node once we find it.
        CurNode = get(list,Index);

        // Cache reference to the node before it after we find it.
        NodeBefore = get(list,Index-1);

        // NB NN <- CN
        // (NB: NodeBefore, NN: NewNode, CN: CurNode, Connections: - or =, Direction: < or > )

        // Now set CurNode's last value to our new node.
        CurNode->Last = newNode;

        // NB NN <=> CN

        // Now set newNode's next to CurNode
        newNode->Next = CurNode;

        // NB -> NN <=> CN

        // Now set NodeBefore's next to cur node
        NodeBefore->Next = newNode;

        // NB <=> NN <=> CN

        // Now set curNode's last to NodeBefore
        newNode->Last = CurNode;

    }

    // Making sure our NodeAtCursor is not corrupted while adding nodes
    if (list->Cursor == Index)
        list->NodeAtCursor = newNode;

    //Incrementing List Size
    list->Size++;

}

/*

    void clearList(LinkedList *list)

    Clears all elements in the list, and collects garbage.

*/

void clearList(LinkedList *list) {

    // Get first node
    Node *curNode = list->Head;

    // To store reference to next node
    Node *NextNode;

    while (curNode != NULL) {
        NextNode = curNode->Next;

        // GC Data Stored in the Node
        free(curNode->Value);

        // GC Node
        free(curNode);

        // Assign Node
        curNode = NextNode;

    }

    list->Head = NULL;
    list->Tail = NULL;
    list->NodeAtCursor = NULL;

    list->Size = 0;
    list->Cursor = 0;

}


/*

    void deleteList(LinkedList *list)

    Completely clears all the elements in the list,
    and deletes the list.

*/

void deleteList(LinkedList *list) {

    // Clear all elements in the list.
    clearList(list);

    // Delete List
    free(list);

    // Assign Pointer to Null
    list = NULL;
}

/*

    Algorithms

*/


/*

    void forEachElementInList(LinkedList *list, void(*f)(void*))

    Apply the function f to the elements of the list passed. On each iteration
    the function f is passed the value of that element in the list.

    Yeah, I stole it from Java, GOT A PROBLEM BRO?

 */

void forEachElementInList(LinkedList *list, void(*f)(void*)) {

    // Get Start Node
    Node *curNode = list->Head;

    // Iterate through all Nodes
    while (curNode != NULL) {
        f(curNode->Value);
        curNode = curNode->Next;
    }

}

/*

    void BinarySearch(LinkedList *list, int(*Evaluate)(void* Value,unsigned short int* MoveRight),void *Destination, unsigned int *Index)

    Perform a Binary Search on the list, applies the function Evaluate on the indexed element to evaluate it.
    Once evaluated, it will return assigned *Destination the value of the node, and *Index the index of the node.
    Target, Value and a pointer MoveRight is passed on to the function Evaluate.
    Evaluate Function MUST RETURN NON - ZERO VALUE IF TRUE, IT SHOULD RETURN ZERO IF FALSE
    Evaluate Function MUST SET MOVE RIGHT TO NON - ZERO VALUE IF BINARY SEARCH SHOUlD MOVE RIGHT,
    OR TO ZERO IF BINARY SEARCH SHOULD MOVE LEFT

 */
void BinarySearch(LinkedList *list,void *Target ,int(*Evaluate)(void* Value, void* Target, unsigned short int* MoveRight),void *Destination, unsigned int *Index){

    // Binary Search Algorithm

    unsigned int Start  = 0;
    unsigned int End   = getListSize(list) - 1;

    void *Value = NULL;
    unsigned short int MoveRight = 0;

    // Run until Middle is less than or equal to Size
    while (Start <= End) {

        // Get the Middle
        unsigned int Middle = Start + (End - Start) / 2;

        // Get Middle Value
        Value = getFromList(list,Middle);

        // If Evaluated, set Destination and Index values, break out of loop
        if (Evaluate(Value,Target,&MoveRight)) {
            Destination = Value;
            *Index = Middle;
            break;
        }


        // If Move Right
        if (MoveRight)
            //Ignore left
            Start = Middle + 1;
        else
            //Ignore right
            End = Middle - 1;

    }

}
