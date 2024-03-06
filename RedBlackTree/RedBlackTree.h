/* RedBlackTree.h CS210 SDSU
* Header file for RedBlackTree
* You may add to this file as needed.
*/
#ifndef REDBLACKTREE
#define REDBLACKTREE
// Defines BLACK = 0, RED = 1
enum COLOR {BLACK, RED};

// Node class 
// Contains already defined methods
// You may add helper methods if needed
class Node {
public:
    int val;
    int color;
    Node *parent;
    Node *left;
    Node *right;

    Node(int val) : val(val) {
	    parent = left = right = nullptr;
	    color = RED;
    }
    int getColor() { return color; }
    Node* getLeftChild() { return left; }
    Node* getRightChild() { return right; }
    Node* getParent() { return parent; }
    int getValue() { return val; };
};

// RedBlackTree class
class RedBlackTree {
private:
    Node* root;

public:
    // You must implement the following five methods

    // Default constructor for RedBlackTree
    RedBlackTree();

    //Inserts a value into the tree and performs the necessary balancing
    void add(int value);

    //Removes a value from the tree if present and performs the necessary balancing
    void remove(int value);

    //Returns true if the tree contains the specified value
    bool contains(int value);

    //Returns Node containing specified value
    Node* get(int value);


    // Helper Methods
    // You may remove these methods or add more if needed
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixRedRed(Node* x);
    void fixBlackBlack(Node* x);
};

#endif // REDBLACKTREE