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

    Node* insert(Node* node, T value) {
        if (!node) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }
    
    void destroy_tree(Node* node) {
        if (node) {
            destroy_tree(node->left);
            destroy_tree(node->right);
            delete node;
        }
    }

    Node* copy_tree(Node* otherNode) {
        if (!otherNode) return nullptr;
        Node* newNode = new Node(otherNode->data);
        newNode->left = copy_tree(otherNode->left);
        newNode->right = copy_tree(otherNode->right);
        return newNode;
    }

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
            return 1;
        }

        return countLeaves(node->left) + countLeaves(node->right);
    }

    void inorder(Node* node, std::ostream& os) const {
        if (node != nullptr) {
            inorder(node->left, os);
            os << node->data << ' ';
            inorder(node->right, os);
        }
    }

    void preorder(Node* node, std::ostream& os) const {
        if (node != nullptr) {
            os << node->data << ' ';
            preorder(node->left, os);
            preorder(node->right, os);
        }
    }

    void postorder(Node* node, std::ostream& os) const {
        if (node != nullptr) {
            postorder(node->left, os);
            postorder(node->right, os);
            os << node->data << ' ';
        }
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, T value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = deleteNode(node->left, value);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }    

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroy_tree(root);
    }

    BinarySearchTree(const BinarySearchTree& other) {
        root = copy_tree(other.root);
    }

    BinarySearchTree(BinarySearchTree&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }

    BinarySearchTree& operator=(const BinarySearchTree& other) {
        if (this != &other) {
            destroy_tree(root);
            root = copy_tree(other.root);
        }
        return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
        if (this != &other) {
            destroy_tree(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    void insert(T value) {
        root = insert(root, value);
    }

    void inorder(std::ostream& os) const {
        inorder(root,os);
    }

    void preorder(std::ostream& os) const {
        preorder(root,os);
    }    

    void postorder(std::ostream& os) const {
        postorder(root,os);
    } 

    size_t countLeaves() const {
        return countLeaves(root);
    } 

    size_t calculateHeight()  const {
        if (root == nullptr) {
            throw std::domain_error("empty tree");
        }
        return compute_height(root) - 1;
    }

    bool exists(T value) const {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return true;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void deleteValue(T value) {
        root = deleteNode(root, value);
    } 

    T& findMinimumValue() {
        if (root == nullptr) {
            throw std::domain_error("empty tree");
        }
        return minValueNode(root)->data;
    }

    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst) {
        bst.inorder(bst.root,os);          //->inorder(bst.root, os);
        return os;
    }
};

#endif
