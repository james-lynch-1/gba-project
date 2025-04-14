#include "avl.h"
#include "log.h"

int getHeight(TreeNode* node) {
    if (!node) return -1;
    return node->height;
}

int getBalance(TreeNode* node) {
    if (!node) return 0;
    return getHeight(node->right) - getHeight(node->left);
}

TreeNode* leftRotate(TreeNode* x) {
    if (!x->right) return x;
    TreeNode* y = x->right;
    TreeNode* yLeftOld = y->left;
    y->left = x;
    x->right = yLeftOld;
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    return y;
}

TreeNode* rightRotate(TreeNode* y) {
    if (!y->left) return y;
    TreeNode* x = y->left;
    TreeNode* xOldRight = x->right;
    x->right = y;
    y->left = xOldRight;
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}

TreeNode* insertTreeNode(TreeNode* head, ActionTile tile) {
    TreeNode* newNodePtr = malloc(sizeof(TreeNode));
    if (!newNodePtr) return NULL;
    Node* traversed = createStack(head);
    int traversedLength = 1;
    traversed = traverseTree(traversed, tile.id, &traversedLength);
    TreeNode* lastNode = (TreeNode*)(traversed->data);
    TreeNode newNode = { NULL, NULL, tile, 0, tile.data.respawnTime };
    *newNodePtr = newNode;
    if (tile.id < lastNode->tile.id)
        lastNode->left = newNodePtr;
    else
        lastNode->right = newNodePtr;

    TreeNode* newRoot = head;
    // update heights of traversed nodes and balance
    for (int i = 0; i < traversedLength; i++) { // starting at parent of inserted node
        traversed = balanceTree(traversed);
        newRoot = traversed->data;
        traversed = pop(traversed);
    }
    deleteStack(traversed);
    return newRoot;
}

/** Takes a stack ptr pointing to a tree node and balances the subtree at that tree node.
 *  Returns a pointer to the new subtree's root.
 */
Node* balanceTree(Node* traversed) {
    TreeNode* n = getNodeDataAsTreeNode(traversed);
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    int balance = getBalance(n);
    if (balance < -1) {
        if (getBalance(n->left) < 0) { // ll
            n = rightRotate(n);
        }
        else if (getBalance(n->left) >= 0) { // lr
            n->left = leftRotate(n->left);
            n = rightRotate(n);
        }
    }
    else if (balance > 1) {
        if (getBalance(n->right) > 0) { // rr
            n = leftRotate(n);
        }
        else if (getBalance(n->right) <= 0) { // rl
            n->right = rightRotate(n->right);
            n = leftRotate(n);
        }
    }
    traversed->data = n;
    TreeNode* parent = getNodeDataAsTreeNode(traversed->next);
    if (parent) { // update parent node's appropriate child pointer, if node != head
        if ((n->tile.id) < parent->tile.id)
            parent->left = n;
        else
            parent->right = n;
    }
    return traversed;
}

/** Searches tree for node with supplied key */
TreeNode* findTreeNode(TreeNode* head, int key) {
    TreeNode* node = head;
    while (node && node->tile.id != key) {
        if (node->tile.id > key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

/** Traverses the tree and adds to a supplied stack of nodes until it finds the appropriate place to
 *  add a new node of supplied value. Returns a generic Node* with data of type TreeNode* (cast from void*)
 *  and amends the supplied stack length. (If key is in tree, returns its TreeNode* (in Node* stack form))
*/
Node* traverseTree(Node* firstNode, int tileIndex, int* length) {
    if (!firstNode) return NULL;
    Node* stackPtr = firstNode;
    TreeNode* treeNode = (TreeNode*)(firstNode->data);
    int l = *length;
    do {
        if (!treeNode) break;
        treeNode = tileIndex <= (treeNode->tile.id) ? treeNode->left : treeNode->right;
        stackPtr = stackPush(stackPtr, treeNode);
        l++;
    } while (treeNode);
    *length = l - 1; // because stackPush fails on the last iteration
    return stackPtr;
}

void deleteAllTreeNodes(TreeNode* head) {
    if (!head) return;
    Node* traversed = NULL;
    TreeNode* nextNode = head;
    do {
        if (!nextNode) {
            nextNode = getNodeDataAsTreeNode(traversed)->right;
            free(getNodeDataAsTreeNode(traversed));
            traversed = pop(traversed);
            if (!traversed) { // when we reach the top of the tree
                traversed = stackPush(traversed, nextNode);
                if (nextNode) nextNode = nextNode->left;
            }
        }
        else {
            traversed = stackPush(traversed, nextNode);
            nextNode = nextNode->left;
        }
    } while (traversed);
}

// must be leaf node... will change later
void deleteTreeNode(TreeNode* head, int key) {
    Node* traversed = createStack((void*)head);
    traversed = traverseTree(traversed, key, NULL);
    TreeNode* node = getNodeDataAsTreeNode(traversed);
    if (node && node->tile.id == key) {
        TreeNode* parent = getNodeDataAsTreeNode(traversed->next);
        if (parent->tile.id > key)
            parent->left = NULL;
        else
            parent->right = NULL;
        free(node);
    }
    deleteStack(traversed);
}

TreeNode* getNodeDataAsTreeNode(Node* node) {
    if (!node) return NULL;
    return (TreeNode*)node->data;
}
