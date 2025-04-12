#include "type.h"

// stack functions
Node* createStack(void* data) {
    Node* headPtr = malloc(sizeof(Node));
    if (!headPtr) return NULL;
    Node head = {data, NULL};
    *headPtr = head; // points to 0x20000a8 the first few times, then points to 0x20000 the last time for some reason
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
