#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <stdexcept>

template<typename T>
class BinarySearchTree {
private:
    class Node {
    public:
        T data;
        Node* left;
        Node* right;

        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;


    size_t compute_height(Node *node) const {
        if (node == nullptr) {
            return 0;
        }
        size_t leftHeight = compute_height(node->left);
        size_t rightHeight = compute_height(node->right);
        return 1 + std::max(leftHeight, rightHeight);
    }

    size_t countLeaves(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1; // Node is a leaf
        }
        return countLeaves(node->left) + countLeaves(node->right);
    }

    void inorder(Node* node, std::ostream& os) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left, os);
        os << node->data << " ";
        inorder(node->right, os);
    }

    void preorder(Node* node, std::ostream& os) const {
        if (node == nullptr) {
            return;
        }
        os << node->data << " ";
        preorder(node->left, os);
        preorder(node->right, os);
    }    

    void postorder(Node* node, std::ostream& os) const {
        if (node == nullptr) {
            return;
        }
        postorder(node->left, os);
        postorder(node->right, os);
        os << node->data << " ";
    } 


public:

    size_t calculateHeight() const {
        if (root == nullptr) {
            throw std::domain_error("empty tree");
        }
        return compute_height(root);
    }

    bool exists(T value) const {
        return exists(root, value);
    }

    bool exists(Node* node, T value) const {
        if (node == nullptr) {
            return false;
        }
        if (node->data == value) {
            return true;
        }
        if (value < node->data) {
            return exists(node->left, value);
        } else {
            return exists(node->right, value);
        }
    }

    Node* deleteNode(Node* node, T value) {
        if (node == nullptr) {
            return node;
        }

        // Locate the node with the given value
        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            node->data = minValueNode(node->right)->data;
            
            // Delete the inorder successor
            node->right = deleteNode(node->right, node->data);
        }
        return node;
    }    

};

#endif
