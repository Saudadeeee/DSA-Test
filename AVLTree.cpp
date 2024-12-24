#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct AVLNode {
    int key;
    int nodeHeight;
    AVLNode* leftChild;
    AVLNode* rightChild;

    AVLNode(int k) : key(k), nodeHeight(1), leftChild(nullptr), rightChild(nullptr) {}
};

class AVLTree {
private:
    AVLNode* rootNode;

    int getNodeHeight(AVLNode* node) {
        return node ? node->nodeHeight : 0;
    }

    void updateNodeHeight(AVLNode* node) {
        if (node) {
            node->nodeHeight = 1 + max(getNodeHeight(node->leftChild), getNodeHeight(node->rightChild));
        }
    }

    int getBalance(AVLNode* node) {
        return node ? getNodeHeight(node->leftChild) - getNodeHeight(node->rightChild) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->leftChild;
        AVLNode* T2 = x->rightChild;

        x->rightChild = y;
        y->leftChild = T2;

        updateNodeHeight(y);
        updateNodeHeight(x);

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->rightChild;
        AVLNode* T2 = y->leftChild;

        y->leftChild = x;
        x->rightChild = T2;

        updateNodeHeight(x);
        updateNodeHeight(y);

        return y;
    }

    AVLNode* balance(AVLNode* node) {
        int balanceFactor = getBalance(node);

        if (balanceFactor > 1) {
            if (getBalance(node->leftChild) < 0) {
                node->leftChild = leftRotate(node->leftChild);
            }
            return rightRotate(node);
        }

        if (balanceFactor < -1) {
            if (getBalance(node->rightChild) > 0) {
                node->rightChild = rightRotate(node->rightChild);
            }
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) {
            return new AVLNode(key);
        }

        if (key < node->key) {
            node->leftChild = insert(node->leftChild, key);
        } else if (key > node->key) {
            node->rightChild = insert(node->rightChild, key);
        } else {
            return node;
        }

        updateNodeHeight(node);
        return balance(node);
    }

    void inorder(AVLNode* node, vector<int>& result) {
        if (node) {
            inorder(node->leftChild, result);
            result.push_back(node->key);
            inorder(node->rightChild, result);
        }
    }

    void preorder(AVLNode* node, vector<int>& result) {
        if (node) {
            result.push_back(node->key);
            preorder(node->leftChild, result);
            preorder(node->rightChild, result);
        }
    }

public:
    AVLTree() : rootNode(nullptr) {}

    void insertKey(int key) {
        rootNode = insert(rootNode, key);
    }

    void displaySteps(const vector<int>& elements) {
        for (size_t i = 0; i < elements.size(); ++i) {
            cout << "Step " << i + 1 << ": Insert " << elements[i] << endl;
            insertKey(elements[i]);

            vector<int> inorderResult, preorderResult;
            inorder(rootNode, inorderResult);
            preorder(rootNode, preorderResult);

            cout << "Inorder Traversal: ";
            for (int val : inorderResult) {
                cout << val << " ";
            }
            cout << endl;

            cout << "Preorder Traversal: ";
            for (int val : preorderResult) {
                cout << val << " ";
            }
            cout << endl;

            cout << "-------------------------------------" << endl;
        }
    }
};

int main() {
    vector<int> elements = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    AVLTree tree;
    tree.displaySteps(elements);
    return 0;
}