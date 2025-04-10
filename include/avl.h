#ifndef avlh
#define avlh

#include "type.h"

int getHeight(TreeNode* node);

int getBalance(TreeNode* node);

TreeNode* leftRotate(TreeNode* x);

TreeNode* rightRotate(TreeNode* y);

TreeNode* insertTreeNode(TreeNode* head, void* data);

Node* traverseTree(Node* firstNode, int data, int* length);

void deleteAllTreeNodes(TreeNode* head);

#endif
