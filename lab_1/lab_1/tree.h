#pragma once
#include <iostream>

class MySet {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;

        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void copyHelper(Node*& newNode, Node* originalNode) {
        if (originalNode) {
            newNode = new Node(originalNode->key);
            copyHelper(newNode->left, originalNode->left);
            copyHelper(newNode->right, originalNode->right);
        }
    }

    void printHelper(Node* node) {
        if (node) {
            printHelper(node->left);
            std::cout << node->key << " ";
            printHelper(node->right);
        }
    }

    bool insertHelper(Node*& node, int key) {
        if (!node) {
            node = new Node(key);
            return true;
        }

        if (key < node->key) {
            return insertHelper(node->left, key);
        }
        else if (key > node->key) {
            return insertHelper(node->right, key);
        }

        return false; // элемент уже существует
    }

    bool containsHelper(Node* node, int key) {
        if (!node) {
            return false;
        }

        if (key < node->key) {
            return containsHelper(node->left, key);
        }
        else if (key > node->key) {
            return containsHelper(node->right, key);
        }

        return true; // элемент найден
    }

    void eraseHelper(Node*& node, int key) {
        if (!node) {
            return;
        }

        if (key < node->key) {
            eraseHelper(node->left, key);
        }
        else if (key > node->key) {
            eraseHelper(node->right, key);
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
                eraseHelper(node->right, temp->key);
            }
        }
    }

public:
    MySet() : root(nullptr) {}

    MySet(const MySet& other) : root(nullptr) {
        copyHelper(root, other.root);
    }

    ~MySet() {
        // реализация деструктора
    }

    MySet& operator=(const MySet& other) {
        if (this != &other) {
            // реализация оператора присваивания
        }
        return *this;
    }

    void print() {
        printHelper(root);
        std::cout << std::endl;
    }

    bool insert(int key) {
        return insertHelper(root, key);
    }

    bool contains(int key) {
        return containsHelper(root, key);
    }

    bool erase(int key) {
        bool result = contains(key);
        eraseHelper(root, key);
        return result;
    }
};