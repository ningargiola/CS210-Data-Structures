// Nicholas Ingargiola
// 827476189
/* RedBlackTree.cpp
* Source file for RedBlackTree
*/
#include "RedBlackTree.h"

// Default Constructor
RedBlackTree::RedBlackTree() {
    root = nullptr;
}

// Inserts value into tree and performs neccessary balance
void RedBlackTree::add(int value) {
    // Creates a new node with value
    Node* newNode = new Node(value);

    // If the tree is empty, set newNode as root and color as black
    if(root == nullptr) {
        root = newNode;
        root->color = BLACK;
        return;
    }
    Node* current = root;

    // Find the right position for the new node in the tree
    while(current != nullptr) {
        if(value < current->val) {
            // Inserts as the left child value is greater
            if(current->left == nullptr) {
                current->left = newNode;
                newNode->parent = current;
                break;
            }
            current = current->left;
        } else {
            // Inserts as the rightChild if current value is smaller or equal
            if(current->right == nullptr) {
                current->right = newNode;
                newNode->parent = current;
                break;
            }
            current = current->right;
        }
    }
    // Newly inserted nodes is marked RED by default
    newNode->color = RED;

    // Fix any Red-Red violations that occured during insertion
    fixRedRed(newNode);
}  

// Removes a value from the tree if present and performs the necessary balancing
void RedBlackTree::remove(int value) {
    Node* current = root;
    Node* parent = nullptr;
    Node* remove = nullptr;

    // Find the node with the value to be removed
    while (current != nullptr) {
        if (value == current->val) {
            remove = current;
            break;
        } else {
            parent = current;
            if (value < current->val) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
    }

    if (remove == nullptr) {
        return; // Node with given value is not found
    }

    Node* successor = nullptr;

    // Find the successor if the node has two children
    if (remove->left != nullptr && remove->right != nullptr) {
        successor = remove->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        remove->val = successor->val; // Replace with successor's value
        remove = successor; // Update remove pointer to point to successor
    }

    Node* child = (remove->left != nullptr) ? remove->left : remove->right;

    if (child != nullptr) {
        child->parent = remove->parent;
    }

    if (remove->parent == nullptr) {
        root = child; // If remove is root, update root to child
    } else {
        if (remove == remove->parent->left) {
            remove->parent->left = child;
        } else {
            remove->parent->right = child;
        }
    }

    // Fix any Black-Black violations that may occured
    if (remove->color == BLACK) {
        if (child != nullptr && child->color == RED) {
            child->color = BLACK; // Color child black if red
        } else {
            fixBlackBlack(child ? child : remove->parent); //Fix the tree if no red child
        }
    }

    delete remove; // Delete the node
}


//Returns true if tree contains specific value
bool RedBlackTree::contains(int value) {
    Node* current = root;

    // Traverse the tree to find the value
    while(current != nullptr) {
        if(value == current->val) {
            return true; // Found the value
        } else if(value < current->val) {
            current = current->left; // Move left if value is smaller
        } else {
            current = current->right; // Move right if value is greater
        }
    }
    return false; // Value not found in the tree
}

//Returns node containing specific value
Node* RedBlackTree::get(int value) {
    Node* current = root;

    // Traverse the tree to find the node with the value
    while(current != nullptr) {
        if(value == current->val) {
            return current; // Found the node with the value
        } else if(value < current->val) {
            current = current->left; // Move left if value is smaller
        } else {
            current = current->right; // Move right if value is greater
        }
    }
    return nullptr; // Node with the value not found
}

// Helper Methods
void RedBlackTree::leftRotate(Node* x) {
    // Store the right child of x
    Node* rightChild = x->right;

    // Assign the left subtree of the right child to x's right subtree
    x->right = rightChild->left;

    // Update the parent of the left child of the right subtree, if it exist
    if(rightChild->left != nullptr) {
        rightChild->left->parent = x;
    }

    // Update the parent of the right child
    rightChild->parent = x->parent;

    // Update the root if x was the root; otherwise, update x's parent's child pointer
    if(x->parent == nullptr) {
        root = rightChild;
    } else if(x == x->parent->left) {
        x->parent->left = rightChild;
    } else {
        x->parent->right = rightChild;
    }

    // Perform the rotation: make x the left child of the right child 
    rightChild->left = x;
    x->parent = rightChild;
}

void RedBlackTree::rightRotate(Node* x) {
    // Store the left child of x
    Node* leftChild = x->left;

    // Assign the right subtree of the left child to x's left subtree
     x->left = leftChild->right;

    // Update the parent of the right child of the left subtree, if it exists
    if(leftChild->right != nullptr) {
        leftChild->right->parent = x;
    }

    // Update the parent of the left child 
    leftChild->parent = x->parent;

    // Update the root if x was the root; otherwise, update x's parent's child pointer
    if(x->parent == nullptr) {
        root = leftChild;
    } else if(x == x->parent->right) {
        x->parent->right = leftChild;
    } else {
        x->parent->left = leftChild;
    }

    // Perform the rotation: make x the right child of the left child 
    leftChild->right = x;
    x->parent = leftChild;

}

void RedBlackTree::fixRedRed(Node* x) {
    while(x != root && x->color == RED && x->parent->color == RED) {
        Node* parent = x->parent;
        Node* grandparent = parent->parent;

        if(parent == grandparent->left) {
            Node* uncle = grandparent->right;

            if(uncle != nullptr && uncle->color == RED) {
                // Case: Uncle is red
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            } else {
                // Case: Uncle is black
                if(x == parent->right) {
                    // If x is the right child, left rotate x and update parent 
                    x = parent;
                    leftRotate(x);
                    parent = x->parent;
                }
                // Update colors and perform right rotation around the grandparent
                parent->color = BLACK;
                grandparent->color = RED;
                rightRotate(grandparent);
                x = parent;
            }
        } else {
            Node* uncle = grandparent->left;
            if(uncle != nullptr && uncle->color == RED) {
                // Case: Uncle is red
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            } else {
                // Case: Uncle is black 
                if(x == parent->left) {
                    // If x is the left child, right rotate x and update parent
                    x = parent;
                    rightRotate(x);
                    parent = x-> parent;
                }
                // Update colors and perform left rotation around the grandparent
                parent->color = BLACK;
                grandparent->color = RED;
                leftRotate(grandparent);
                x = parent;
            }
        }
    }
    root->color = BLACK; // Set the root to black to maintain the property
}

void RedBlackTree::fixBlackBlack(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* sibling = x->parent->right;
            if (sibling != nullptr) {
                if (sibling->color == RED) {
                    // Case: Sibling is red 
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    sibling = x->parent->right;
                }
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    // Case: Both sibling's children are black
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        // Case: sibling's right child is black
                        if (sibling->left != nullptr) {
                            sibling->left->color = BLACK;
                        }
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = x->parent->right;
                    }
                    if (sibling != nullptr) {
                        // Case: Adjust colors and perform rotation
                        sibling->color = x->parent->color;
                        x->parent->color = BLACK;
                        if (sibling->right != nullptr) {
                            sibling->right->color = BLACK;
                        }
                        leftRotate(x->parent);
                        x = root;
                    }
                }
            }
        } else {
            Node* sibling = x->parent->left;
            if (sibling != nullptr) {
                if (sibling->color == RED) {
                    // Case: Sibling is red
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    sibling = x->parent->left;
                }
                if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == BLACK)) {
                    // Case: Both sibling's children are black
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        // Case: Sibling's left child is black
                        if (sibling->right != nullptr) {
                            sibling->right->color = BLACK;
                        }
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = x->parent->left;
                    }
                    if (sibling != nullptr) {
                        // Case: Adjust colors and perform rotation
                        sibling->color = x->parent->color;
                        x->parent->color = BLACK;
                        if (sibling->left != nullptr) {
                            sibling->left->color = BLACK;
                        }
                        rightRotate(x->parent);
                        x = root;
                    }
                }
            }
        }
    }
    if (x != nullptr) {
        x->color = BLACK; // Ensure the root's color remains black
    }
}
