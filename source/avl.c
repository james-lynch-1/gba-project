#include "avl.h"

int getHeight(TreeNode* node) {
    if (node == NULL) return -1;
    return node->height;
}

int getBalance(TreeNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->right) - getHeight(node->left);
}

TreeNode* leftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* yLeftOld = y->left;
    y->left = x;
    x->right = yLeftOld;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

TreeNode* rightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* xOldRight = x->right;
    x->right = y;
    y->left = xOldRight;
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}

TreeNode* insertTreeNode(TreeNode* head, void* data) {
    Node* traversed = createStack((void*)head);
    int traversedLength = 1;
    traversed = traverseTree(traversed, *(int*)data, &traversedLength);
    TreeNode* lastNode = (TreeNode*)(traversed->data);
    TreeNode newNode = { NULL, NULL, data, 0, 0 };
    TreeNode* newNodePtr = malloc(sizeof(TreeNode));
    *newNodePtr = newNode;
    if (*(int*)data < *(int*)(lastNode->data))
        lastNode->left = newNodePtr;
    else
        lastNode->right = newNodePtr;

    // update heights of traversed nodes and balance TODO figure out what this is doing actually
    int rotated = 0;
    TreeNode* parent;
    for (int i = traversedLength; i > 0; i--) {
        TreeNode* n = (TreeNode*)(traversed->data);
        traversed = pop(traversed);
        parent = (TreeNode*)(traversed->next->data);
        n->height = traversedLength - i - rotated;
        int balance = getBalance(n);
        if (balance < -1 && getBalance(n->left) < 0) {
            rotated = 1;
            n = rightRotate(n);
        }
        if (balance < -1 && getBalance(n->left) >= 0) {
            rotated = 1;
            n->left = leftRotate(n->left);
            n = rightRotate(n);
        }
        if (balance > 1 && getBalance(n->right) > 0) {
            rotated = 1;
            n = leftRotate(n);
        }
        if (balance > 1 && getBalance(n->right) <= 0) {
            rotated = 1;
            n->right = rightRotate(n->right);
            n = leftRotate(n);
        }
        if (traversed->next) { // update parent node's appropriate child pointer
            if (*(int*)(n->data) < *(int*)(parent->data)) {
                parent->left = n;
            }
            else {
                parent->right = n;
            }
        }
    }
    return newNodePtr;
}

/** Traverses the tree and adds to a supplied stack of nodes until it finds the appropriate place to
 *  add a new node of supplied value. Returns a generic Node* with data of type TreeNode* (cast from
 *  void*) and amends the supplied stack length.
*/
// doesn't currently check to see if key already exists in tree
Node* traverseTree(Node* firstNode, int data, int* length) {
    Node* stackPtr = firstNode;
    if (!firstNode) return NULL;
    TreeNode* node = (TreeNode*)(firstNode->data);
    TreeNode* nextNode = data <= *(int*)(firstNode->data) ? node->left : node->right;
    int l = *length;
    while (nextNode) {
        nextNode = data <= *(int*)(nextNode->data) ? nextNode->left : nextNode->right;
        stackPtr = push(stackPtr, (void*)nextNode);
        l++;
    }
    *length = l;
    return stackPtr;
}

void deleteAllTreeNodes(TreeNode* head) {
    int traversedLength = 0;
    Node* traversed = createStack((void*)head);
    traversed = traverseTree(traversed, 0, &traversedLength);
    TreeNode* currTreeNode = (TreeNode*)(traversed->data);
    int treeNodeChildData;
    TreeNode* nodeToFree;
    while (traversed) {
        if (!(currTreeNode->left)) {
            if (!(currTreeNode->right)) {
                traversed = pop(traversed);
                traversedLength--;
                treeNodeChildData = *(int*)(currTreeNode->data); // id
                currTreeNode = (TreeNode*)(traversed->data);
                if (treeNodeChildData < *(int*)(currTreeNode->data)) { // was child left or right
                    nodeToFree = currTreeNode->left;
                    currTreeNode->left = NULL;
                }
                else {
                    nodeToFree = currTreeNode->right;
                    currTreeNode->right = NULL;
                }
                free(nodeToFree);
            }
            else if (currTreeNode->right) {
                traversed = traverseTree(traversed, *(int*)(currTreeNode->data) + 1, &traversedLength);
            }
        }
    }
}
