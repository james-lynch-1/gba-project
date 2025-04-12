#ifndef avlh
#define avlh

#include "type.h"

int getHeight(TreeNode* node);

int getBalance(TreeNode* node);

TreeNode* leftRotate(TreeNode* x);

TreeNode* rightRotate(TreeNode* y);

TreeNode* insertTreeNode(TreeNode* head, ActionTile data);

Node* balanceTree(Node* traversed);

TreeNode* findTreeNode(TreeNode* head, int key);

Node* traverseTree(Node* firstNode, int data, int* length);

void deleteAllTreeNodes(TreeNode* head);

void deleteTreeNode(TreeNode* head, int key);

TreeNode* getNodeDataAsTreeNode(Node* node);

#endif
