#include <iostream>
#include <cmath> 

class Node {
public:
    char op;  
    double value; 
    Node* left; 
    Node* right; 
    Node(char o) : op(o), left(nullptr), right(nullptr) {}
    Node(double v) : value(v), op('\0'), left(nullptr), right(nullptr) {}
};
class ExpressionTree {
public:
    Node* root;
    ExpressionTree(Node* r) : root(r) {}
    double evaluate(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        if (node->op == '\0') {
            return node->value;
        }
        double leftVal = evaluate(node->left);
        double rightVal = evaluate(node->right);

        switch (node->op) {
            case '+':
                return leftVal + rightVal;
            case '-':
                return leftVal - rightVal;
            case '*':
                return leftVal * rightVal;
            case '/':
                return leftVal / rightVal;
            case '^':
                return pow(leftVal, rightVal);
            default:
                return 0;
        }
    }
    double evaluate() {
        return evaluate(root);
    }
};

int main() {
    double a, b, c, d, e;
    // (a + (5b/c)) - (c^8) + (d*e^(1/2))
    std::cin >> a >> b >> c >> d >> e;
    Node* n1 = new Node('+'); 
    Node* n2 = new Node('-');  
    Node* n3 = new Node('*');  
    Node* n4 = new Node(a);
    Node* n5 = new Node('+');
    Node* n6 = new Node('/');
    Node* n7 = new Node(5 * b);
    Node* n8 = new Node(c);
    Node* n9 = new Node('^');
    Node* n10 = new Node(c);
    Node* n11 = new Node(8);
    Node* n12 = new Node('*');
    Node* n13 = new Node(d);
    Node* n14 = new Node('^');
    Node* n15 = new Node(e);
    Node* n16 = new Node(0.5);
    n1->left = n2;
    n1->right = n12;
    n2->left = n5;
    n2->right = n9;
    n5->left = n4;
    n5->right = n6;
    n6->left = n7;
    n6->right = n8;
    n9->left = n10;
    n9->right = n11;
    n12->left = n13;
    n12->right = n14;
    n14->left = n15;
    n14->right = n16;
    ExpressionTree tree(n1);
    std::cout << "Result: " << tree.evaluate() << std::endl;

    return 0;
}