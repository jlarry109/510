# Binary Search Tree
Binary search trees (BSTs) are a type of data structure that facilitate efficient searching, insertion, and deletion of data. Some Key characteristics:

- _Node Structure_: Each node in a BST has up to three components: a value, a left child, and a right child.
- _Ordered Arrangement_: In a BST, the left child of a node always contains a value less than its parent node, and the right child contains a value greater than its parent. This ordering applies recursively to all nodes in the tree.
- _Search Efficiency_: Searching in a BST is fast. Starting from the root, you compare the search value with the current node's value and traverse left or right accordingly, significantly reducing the number of comparisons needed compared to linear data structures like arrays.
- _Balanced vs. Unbalanced Trees_: A balanced BST, where the left and right subtrees of any node differ in height by no more than one, ensures that operations remain efficient. Unbalanced trees can degrade to linked lists in the worst case, leading to slower operations.
- _Traversal Methods_: BSTs support several traversal methods:
  - _In-order_(left,right,root): Processes elements in sorted order
  - _Pre-order_(root,left,right): Useful when cloning a tree or processing prefixed notation expressions
  - _Post-order_(lef,right,root): Useful when the results of the children need to computed in the current node's computation. Also used when deleting (freeing) nodes in a destructor.
- _Complexity_: The average case time complexity for search, insert, and delete operations in a BST is O(log n), but in the worst case, it can degrade to O(n), particularly in unbalanced trees.

In the distribution folder, we have provided four files:
1. __BinarySearchTree.hpp__ declares two templated classes: 
   - `BinarySearchTree` models a binary search tree. The class contains
     a link to the root node and then a variety of methods.
   - `Node` is a nested class in `BinarySearchTree` that represents a node. `Node` contains the data element being stored and then two pointers to the left and right children.
2. __main.cpp__ provides the main function. Add code to this file to validate your program.
4. __Makefile__ generates the `test` executable.


For this assignment, you will implement some additional methods 
on the provided code for a binary search tree.

Specifically - 
- `size_t compute_height(Node *node);` // computes the height of the tree. This is the highest number of edges from the root node to a leaf node.
- `size_t countLeaves(Node* node) const;` // counts the number of leaves in a tree.  This is any node that does not have a child.
- `void inorder(Node* node, std::ostream& os) const;` // Performs an in-order traversal, printing(inserting) the node data element to the stream `os`.
   Each element should be separated by a space.
- `void preorder(Node* node, std::ostream& os) const;` // Performs an pre-order traversal, printing(inserting) the node data element to the stream `os`.
   Each element should be separated by a space.
- `void postorder(Node* node, std::ostream& os) const;` // Performs a post-order traversal, printing(inserting) the node data element to the stream `os`.
   Each element should be separated by a space.
- `size_t calculateHeight();`  // Implement functionality. Additionally,  modify this method to throw `std::domain_error` if the tree is empty.
- `bool exists(T value) const;` // returns true if the value exists in the tree, false otherwise
- `void deleteValue(T value);`  // removes the node containing value if it exists.

## Removing a Node
Removing an existing node from a BST is one of the more complex operations for a BST. You need to consider three possibilities:
1. Removing a leaf node
   - Update the parent link to the node to `nullptr`
   - Delete(free) the node
2. Node has a single child
   - Bypass the node by linking the parent to the child
   - Delete(free) the node
3. Node has two children.
   - Find the node's in-order successor (the smallest node in the right subtree).  Alternatively, you can also find the node's
     in-order predecessor (the largest node in the left subtree).
   - Swap the value of the node to be deleted with the in-order successor / predecessor.
   - Delete(free) the node that was the in-order successor/predecessor.  This will either be a leaf node or a node with a single child.
     You should make a recursive call for this deletion. 
     `BinarySearchTree` has a method to find the minimum node from a given node.

In each case, you will also need to consider if the root node has been updated.


## Assignment Review Questions
In a file called `answers.txt`, answer the following questions.

1. What is the big-O runtime of `insert()` (average case)?
2. What is the big-O runtime of `insert()` (worst case)?
3. What is the big-O runtime of the traversal methods?
4. In which of the following scenarios would a pre-order traversal of a Binary Search Tree (BST) be most appropriate?

   A. To display all elements of the BST in sorted order.

   B. To create a copy of the BST with the same structure.

   C. To count the total number of nodes in the BST.

   D. To find the minimum or maximum element in the BST.

5. What property must be true for all nodes in a Binary Search Tree (BST)?
  
   A. The left child must have a value equal to its parent node.

   B. The right child must have a value less than its parent node.

   C. The left child must have a value greater than its parent node.

   D. The right child must have a value greater than its parent node.

## Submission
Submit `BinarySearchTree.cpp` and `answers.txt` to the Gradescope assignment.
