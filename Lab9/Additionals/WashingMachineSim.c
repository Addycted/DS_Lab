#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char name[50];
    int duration; // in minutes
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct CircularDoublyLinkedList {
    Node* head;
} CircularDoublyLinkedList;

Node* createNode(const char* name, int duration) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->duration = duration;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void initList(CircularDoublyLinkedList* list) {
    list->head = createNode("", 0); // Header node
    list->head->next = list->head; // Point to itself
    list->head->prev = list->head;
}

void enqueue(CircularDoublyLinkedList* list, const char* name, int duration) {
    Node* newNode = createNode(name, duration);
    Node* last = list->head->prev;

    newNode->next = list->head;
    newNode->prev = last;
    last->next = newNode;
    list->head->prev = newNode;
}

void dequeue(CircularDoublyLinkedList* list) {
    if (list->head->next == list->head) {
        printf("No one is waiting to use the washing machine.\n");
        return;
    }

    Node* first = list->head->next;
    printf("%s has finished using the washing machine.\n", first->name);
    list->head->next = first->next;
    first->next->prev = list->head;
    free(first);
}

void simulateWashingMachine(CircularDoublyLinkedList* list) {
    while (1) {
        if (list->head->next != list->head) {
            Node* current = list->head->next;
            current->duration--;
            if (current->duration <= 0) {
                dequeue(list);
            }
        }
        printf("Current queue: ");
        Node* temp = list->head->next;
        while (temp != list->head) {
            printf("%s(%d min) ", temp->name, temp->duration);
            temp = temp->next;
        }
        printf("\n");

        sleep(1);
    }
}

int main() {
    CircularDoublyLinkedList queue;
    initList(&queue);

    enqueue(&queue, "Alice", 7);
    enqueue(&queue, "Bob", 5);
    enqueue(&queue, "Charlie", 2);

    simulateWashingMachine(&queue);

    return 0;
}