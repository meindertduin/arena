#pragma once

namespace core {
    template<typename T>
    class SinglyLinkedList {
    public:
        struct Node {
            T data;
            Node* next = nullptr;
        };

        Node *head;

        inline void insert_back(Node* new_node) {
            if (head != nullptr) {
                head->next = new_node;
            } else {
                head = new_node;
            }
        }

        inline void insert(Node* new_node, Node* previous_node) {
            if (previous_node == nullptr) {
                // is the first node
                if (head != nullptr) {
                    // list has more elements
                    new_node->next = head;
                } else {
                    new_node->next = nullptr;
                }
                head = new_node;
            } else {
                if (previous_node->next == nullptr) {
                    // is the last node
                    previous_node->next = new_node;
                    new_node->next = nullptr;
                } else {
                    // is a middle node
                    new_node->next = previous_node->next;
                    previous_node->next = new_node;
                }
            }
        }

        inline void remove(Node* remove_node, Node* previous_node) {
            if (previous_node == nullptr) {
                // remove_node is the first node
                if (remove_node->next == nullptr) {
                    // list has only one element
                    head = nullptr;
                } else {
                    // list has more elements
                    head = remove_node->next;
                }
            } else {
                previous_node->next = remove_node->next;
            }
        }
    };
}