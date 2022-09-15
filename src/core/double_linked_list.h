#pragma once

namespace core {
    template<typename T>
    class DoubleLinkedList {
    public:
        struct Node {
            T data;
            Node* previous = nullptr;
            Node* next = nullptr;
        };

        Node *head;

        DoubleLinkedList() = default;

        inline void insert(Node* new_node) {
            if (head != nullptr) {
                head->next = new_node;
                new_node->previous = head;
            } else {
                head = new_node;
            }
        }

        inline void insert(Node* new_node, Node* previous) {
            // check if new_node should be inserted between nodes
            if (previous->next != nullptr) {
                // linking the next node
                new_node->next = previous->next;
                new_node->next->previous = new_node;

                // linking the previous node
                previous->next = new_node;
                new_node->previous = previous;
            } else {
                // insert new_node at the back
                previous->next = new_node;
                new_node->previous = previous;
            }
        }

        inline void remove(Node* node) {
            // check if node is the first
            if (node->previous == nullptr) {
                if (node->next == nullptr) {
                    head = nullptr;
                } else {
                    head = node->next;
                    head->previous = nullptr;
                }
            } else { // node is not the last
                if (node->next == nullptr) {
                    // node is the last
                    node->previous->next = nullptr;
                } else {
                    node->previous->next = node->next;
                    node->next->previous = node->previous;
                }
            }
        }
    };
}