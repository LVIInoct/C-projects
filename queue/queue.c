/* This is a simple implementation of a queue using a linked list. It's my first attempt, following FIFO (First In and
First Out order, dynamic array rules, and with a time complexity of O(1) for enqueue and dequeue operations, O(n) for
traversing and O(1) for checking size. */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
// declaring a node constructor
struct Node {
    int data;
    struct Node* next;
};

// prototypes
void peekFirst(struct Node* head); 
void peekLast(struct Node* tail);
void enqueue(struct Node** head, struct Node** tail, int data);
void poll(struct Node** head, struct Node** tail);
void display(struct Node* head);
void clear(struct Node** head, struct Node** tail);

int main(void){
    // declaring values
    struct Node* head = NULL; // defining head
    struct Node* tail = NULL; // defining tail
    int choice;
    while (1){
            printf("What would you like to do?\n 1) enqueue \n 2) poll \n 3) Peek first (head)\n 4) peek last (tail) \n 5) Check size of array and content\n 6) Exit\n");
            scanf("%d", &choice);
            switch (choice) {
                case 1: { // enqueue first element
                    int value; // element value
                    printf("Enter value:\n> "); 
                    scanf("%d", &value);
                    enqueue(&head, &tail, value);
                    break;
                    }
                case 2:
                    poll(&head, &tail); // remove first element, manipulates the queue so it takes & for the address
                    break;
                case 3:
                    peekFirst(head); // peek first (head)
                    break;
                case 4:
                    peekLast(tail); // peek last (tail)
                    break;
                case 5:
                    display(head);
                    break;
                case 6:
                    clear(&head, &tail); // free any leftovers in the list before exiting
                    printf("Exiting program & clearing leftovers.\n");
                    return 0; // force exit
                default:
                    printf("Invalid choice. (Out of bounds)\n");
                    continue;
            }
    }

}


// enqueueing
void enqueue(struct Node** head, struct Node** tail, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
    printf("Memory allocation failed. (Somehow)\n");
    return;
    }
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL) { 
        *head = *tail = newNode;
    }
    else {
        (*tail)->next = newNode;
        *tail = newNode; 
    }
}

// peek first
void peekFirst(struct Node* head) { 
    if (head == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    else {
        printf("First element: %d\n", head->data);
    }
    printf("\n");

}
// peek last
void peekLast(struct Node* tail){
    if (tail == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    else {
        printf("Last element: %d\n", tail->data);
    }
}
// poll
void poll(struct Node** head, struct Node** tail){
    if (*head == NULL){
        printf("Queue is empty.\n");
        *tail = NULL;
        return;
    }
    struct Node* temp = *head;
    printf("Removed: %d\n", temp->data);
    *head = (*head)->next;
    if (*head == NULL){
        *tail = NULL;
    }
    free(temp);
}

// display list
void display(struct Node* head) {
    struct Node* trav = head;
    int size = 0;
    if (trav == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    while (trav != NULL) {
        printf("[%d] ", trav->data);
        size++;
        trav = trav->next;
    }
    printf("\n");
    printf("Size: %d\n", size);
}
// clear data
void clear(struct Node** head, struct Node** tail) {
    struct Node* trav = *head;
    struct Node* nextNode;
    while (trav != NULL) {
        nextNode = trav->next;
        free(trav);
        trav = nextNode;
    }
    *head = NULL;
    *tail = NULL;
}