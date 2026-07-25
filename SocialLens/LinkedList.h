#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <new>

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node* next;

        explicit Node(const T& value)
            : data(value), next(nullptr)
        {
        }
    };

    Node* head;
    Node* tail;
    int itemCount;

public:
    LinkedList()
        : head(nullptr), tail(nullptr), itemCount(0)
    {
    }

    ~LinkedList()
    {
        clear();
    }

    LinkedList(const LinkedList& other) = delete;
    LinkedList& operator=(const LinkedList& other) = delete;

    bool addToEnd(const T& value)
    {
        Node* newNode = new (std::nothrow) Node(value);
        if (newNode == nullptr) {
            return false;
        }

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        ++itemCount;
        return true;
    }

    bool remove(const T& value)
    {
        Node* previous = nullptr;
        Node* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                if (previous == nullptr) {
                    head = current->next;
                }
                else {
                    previous->next = current->next;
                }

                if (current == tail) {
                    tail = previous;
                }

                delete current;
                --itemCount;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    void print(std::ostream& os = std::cout) const
    {
        os << "[";
        Node* current = head;

        while (current != nullptr) {
            os << current->data;
            if (current->next != nullptr) {
                os << ", ";
            }
            current = current->next;
        }

        os << "]";
    }

    int size() const
    {
        return itemCount;
    }

    bool isEmpty() const
    {
        return itemCount == 0;
    }

    void clear()
    {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = nullptr;
        tail = nullptr;
        itemCount = 0;
    }
};

#endif
