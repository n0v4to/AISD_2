#pragma once
#include <iostream>

class Set {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void copy_helper(Node*& newNode, Node* original_node) {
        if (original_node) {
            newNode = new Node(original_node->key);
            copy_helper(newNode->left, original_node->left);
            copy_helper(newNode->right, original_node->right);
        }
    }

    void print_helper(Node* node) {
        if (node) {
            print_helper(node->left);
            std::cout << node->key << " ";
            print_helper(node->right);
        }
    }

    bool insert_helper(Node*& node, int key) {
        if (!node) {
            node = new Node(key);
            return true;
        }

        if (key < node->key) {
            return insert_helper(node->left, key);
        }
        else if (key > node->key) {
            return insert_helper(node->right, key);
        }

        return false;
    }

    bool contains_helper(Node* node, int key) {
        if (!node) {
            return false;
        }

        if (key < node->key) {
            return contains_helper(node->left, key);
        }
        else if (key > node->key) {
            return contains_helper(node->right, key);
        }

        return true;
    }

    void erase_helper(Node*& node, int key) {
        if (!node) {
            return;
        }

        if (key < node->key) {
            erase_helper(node->left, key);
        }
        else if (key > node->key) {
            erase_helper(node->right, key);
        }
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                node = temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                node = temp;
            }
            else {
                Node* temp = node->right;
                while (temp->left) {
                    temp = temp->left;
                }
                node->key = temp->key;
                erase_helper(node->right, temp->key);
            }
        }
    }

    void delete_same(Set& tree, Node* node) {
        if (node) {
            delete_same(tree, node->left);
            if (tree.contains(node->key)) tree.erase(node->key);
            delete_same(tree, node->right);
        }
    }
public:
    Node*& get_root() {
        return root;
    }

    Set() : root(nullptr) {}

    Set(const Set& other) : root(nullptr) {
        copy_helper(root, other.root);
    }

    ~Set() {
        while (root) {
            erase(root->key);
        }
    }

    Set& operator=(const Set& other) {
        if (this != &other) {
            if (root) {
                while (root) {
                    erase(root->key);
                }
            }
            copy_helper(root, other.root);
        }
        return *this;
    }

    void print() {
        print_helper(root);
        std::cout << std::endl;
    }

    bool insert(int key) {
        return insert_helper(root, key);
    }

    bool contains(int key) {
        return contains_helper(root, key);
    }

    bool erase(int key) {
        bool result = contains(key);
        erase_helper(root, key);
        return result;
    }

    Set intersection(Set& lhs, Set& rhs) {
        Set dif = difference(lhs, rhs);
        return difference(lhs, dif);
    }

    Set difference(Set& lhs, Set& rhs) {
        Set dif(lhs);
        delete_same(dif, rhs.get_root());
        return dif;
    }
};