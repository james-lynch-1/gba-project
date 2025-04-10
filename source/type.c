#include "type.h"

// stack functions
Node* createStack(void* data) {
    Node* headPtr = malloc(sizeof(Node));
    Node head = {data, NULL};
    *headPtr = head;
    return headPtr;
}

Node* push(Node* node, void* data) {
    if (!data) return node;
    Node* newNodePtr = malloc(sizeof(Node));
    if (!newNodePtr) return NULL;
    Node newNode = { data, node };
    *newNodePtr = newNode;
    return newNodePtr;
}

Node* pop(Node* node) {
    if (!node) return NULL;
    Node* nextNode = node->next;
    free(node);
    return nextNode;
}

void deleteStack(Node* node) {
    while (node) {
        node = pop(node);
    }
    return;
}
