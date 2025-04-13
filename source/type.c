#include "type.h"

// stack functions
Node* createStack(void* data) {
    Node* headPtr = malloc(sizeof(Node));
    if (!headPtr) return NULL;
    Node head = {data, NULL};
    *headPtr = head;
    return headPtr;
}

Node* stackPush(Node* node, void* data) {
    if (!data) return node;
    Node* newNodePtr = malloc(sizeof(Node));
    if (!newNodePtr) return node;
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
}
