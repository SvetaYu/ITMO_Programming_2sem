#pragma once
#include <iostream>
struct node {
    node *next = nullptr;
};

class freeChunks {
public:

    void push(node *data) {
        data->next = head;
        head = data;
    }

    void *pop() {
        if (head == nullptr)
            throw std::exception();
        void *returned = (void *) head;
        head = head->next;
        return returned;
    }

    bool empty() const {
        return head == nullptr;
    }

    node *head = nullptr;
};