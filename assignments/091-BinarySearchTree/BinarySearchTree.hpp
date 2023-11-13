#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>

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
        // need to implement
        return 0;
    }

    size_t countLeaves(Node* node) const {
        // need to implement
        return 0;
    }

    void inorder(Node* node, std::ostream& os) const {
        // need to implement 
    }

    void preorder(Node* node, std::ostream& os) const {
        // need to implement 
    }    

    void postorder(Node* node, std::ostream& os) const {
        // need to implement 
    } 

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, T value) {
        if (node == nullptr) return node;

        // need to implement
        
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
        // need to implement
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
