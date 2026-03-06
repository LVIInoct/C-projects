#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void peek(struct Node* head); 
void push(struct Node** head, int data);
void pop(struct Node** head);
void display(struct Node* head);
void clear(struct Node** head);

int main(void){
    struct Node* head = NULL;
    int choice;
    while (1){
            printf("What would you like to do?\n 1) push \n 2) pop \n 3) Peek first (top) \n 4) Check size of list and content\n 5)Exit\n");
            scanf("%d", &choice);
            
            switch (choice) {
                case 1: {
                    int value;
                    printf("Enter value:\n > ");
                    scanf("%d", &value);
                    push(&head, value);
                    break;
                }
                case 2:
                    pop(&head);
                    break;
                case 3:
                    peek(head);
                    break;
                case 4:
                    display(head);
                    break;
                case 5:
                    clear(&head);
                    printf("Exiting program & clearing leftovers.\n");
                    return 0;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
    }
}

void push(struct Node** head, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
    printf("Memory allocation failed.\n");
    return;
    }
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

void peek(struct Node* head) {
    struct Node* trav = head;
    if (trav == NULL) {
        printf("List is empty\n");
        return;
    }
    else {
        printf("First element: %d\n", trav->data);
    }

    printf("\n");

}
void pop(struct Node** head){
    if (*head == NULL){
        printf("Stack is empty\n");
        return;
        }
    
    struct Node* temp = *head;
    int data = temp->data;
    *head = (*head)->next;  
    free(temp);
    temp->next = NULL;
    printf("Popped element: %d\n", data);

}

void display(struct Node* head) {
    struct Node* trav = head;
    int size = 0;
    if (trav == NULL) {
        printf("List is empty\n");
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
void clear(struct Node** head) {
    struct Node* trav = *head;
    struct Node* nextNode;
    while (trav != NULL) {
        nextNode = trav->next;
        free(trav);
        trav = nextNode;
    }
    *head = NULL;
}
