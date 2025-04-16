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

Node* traverseTree(Node* firstNode, int key, int* length);

Node* traverseFind(Node* firstNode, int key);

void deleteAllTreeNodes(TreeNode* head);

TreeNode* deleteTreeNode(TreeNode* head, int key);

TreeNode* getNodeDataAsTreeNode(Node* node);

#endif
