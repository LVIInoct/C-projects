/* This is a simple implementation of a queue using a linked list. It's my first attempt, following FIFO (First In and
First Out order, dynamic array rules, and with a time complexity of O(1) for enqueue and dequeue operations, O(n) for
traversing and O(1) for checking size. */

#include <stdio.h>
#include <stdbool.h> // for boolean data type
#include <stdlib.h> // for malloc

struct Node {
    int data;           // data for each pointer
    struct Node* next;  // Node* is a POINTER, trav is the pointer
}; // node struct

// prototypes
void peekFirst(struct Node* head); 
void peekLast(struct Node* tail);
void enqueue(struct Node** head, struct Node** tail, int data);
void poll(struct Node** head, struct Node** tail);
void display(struct Node* head);
void Clear(struct Node** head, struct Node** tail);

int main(void){
    // declaring values
    struct Node* head = NULL; // defining head
    struct Node* tail = NULL; // defining tail
    int choice;
    while (1){
        // menu
            printf("What would you like to do?\n 1) enqueue \n 2) poll \n 3) Peek first (tail)\n 4) peek last (tail) \n 5) Check size of array and content\n 6)Exit\n");
            scanf("%d", &choice);
            if (choice == 1) {                 // enqueue first element
                int value;                     // element value
                printf("Enter value:\n > ");   // prompt for element value
                scanf("%d", &value);           // takes element value as input
            enqueue(&head, &tail, value);      // sends it to the Queue function to be added to the list
            } else if (choice == 2) {
                poll(&head, &tail);            // check size of list
            } else if (choice == 3) {
                peekFirst(head);               // peek first (head)
            } else if (choice == 4) {
                peekLast(tail);                // peek last (tail)
            } else if (choice == 5) {
                display(head);                 // since polling remodels and manipulates the head, it takes its address by &head, so it can poll it
            } else if (choice == 6) {
                Clear(&head, &tail);           // free any leftovers in the list before exiting
                printf("Exiting program & clearing leftovers.\n");
                break;                         // exit the loop and end the program
            } else {
                printf("Invalid choice.\n");
                continue;                        // if the user enters an invalid choice, prompt them again without exiting the program
            }
    }

}

// Functions

// enqueueing
void enqueue(struct Node** head, struct Node** tail, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // create new node and pointer to new node
    newNode->data = data; // set data for this new node
    newNode->next = NULL; // This node is at the very end, so no one is behind it, so next is NULL.
    if (*head == NULL) { 
        // If the list is empty, this person is the first AND the last.
        *head = *tail = newNode;
    }
    else {
        (*tail)->next = newNode; // The current last node's next pointer now points to this new node.
        *tail = newNode; // Update the tail pointer to point to this new node, which is now the last node in the list and official tail.
    }
    if (newNode == NULL) { // if next node is null after trying to create it, then memory allocation failed
    printf("Memory allocation failed.\n");
    return; // return user
}
}

// peek first
void peekFirst(struct Node* head) { // peeks head
    struct Node* trav = head; // start at the beginning
    if (trav == NULL) { // if there is no head, then the list is empty
        printf("List is empty\n");
        return;
    }
    else {
        printf("First element: %d\n", trav->data); // show data of first element ever added
    }

    printf("\n");

}
// peek last
void peekLast(struct Node* tail){
    struct Node* trav = tail; // start at tail, which is the last element
    if (trav == NULL) { // if there is no tail , then the list is empty
        printf("List is empty\n");
        return;
    }
    else {
        printf("Last element: %d\n", trav->data); // show data of last element ever added
    }
}
// poll
void poll(struct Node** head, struct Node** tail){
    struct Node* temp = *head; // temporary pointer to the current head to remove it
    *head = (*head)->next; // point head to next that comes afterwards
    if (*head == NULL) // if there's no head after polling, then the list is empty, so tail should also be NULL
        *tail = NULL;
    free(temp);
}

// display list
void display(struct Node* head) {
    struct Node* trav = head; // start at the beginning
    int size = 0; // initialize size counter
    if (trav == NULL) { // if there is no head, then the list is empty
        printf("List is empty\n");
        return;
    }
    while (trav != NULL) { // traverse through the list until we reach the end (where trav is NULL)
        printf("[%d] ", trav->data); // print the data of each node
        size++; // increment size counter for each node
        trav = trav->next; // move to the next node
    }
    printf("\n");
    printf("Size: %d\n", size);
}
// get rid of any leftovers after leaving
void Clear(struct Node** head, struct Node** tail) {
    struct Node* trav = *head; // starting node
    struct Node* nextNode;    // pointer
    while (trav != NULL) {
        nextNode = trav->next;
        free(trav);           // trav goes through the whole list, freeing each node as it goes, until it reaches the end (NULL)
        trav = nextNode;
    }
    *head = NULL;
    *tail = NULL;
}
