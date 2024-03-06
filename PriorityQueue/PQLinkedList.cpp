//Nicholas Ingargiola
//827476189
// PQLinkedList.cpp
// Implement your Linked List Priority Queue in this file.
#include "PriorityQueue.h"
#include "TestDriver.h"
// Your code here
// Note: For linked list do NOT use std::unique_ptr<Element[]> pq;
// You must create your own node struct in this file.

// Constrcutor for PriorityQueue
PriorityQueue::PriorityQueue() {
    max_capacity = DEFAULT_MAX_CAPACITY;
    head = nullptr;
}
//Constructor with set size
PriorityQueue::PriorityQueue(int size) {
    max_capacity = size;
    head = nullptr;
}
//Insert an element into Priority Queue
bool PriorityQueue::insert(Element &element) {
    if (isFull()) {
        return false; // Queue is full, insertion not possible
    } else {
        Node* newNode = new Node;
        newNode->data = element;

        if (!head || element.priority < head->data.priority) {
            // Insert at the beginning if the queue is empty or the new element has higher priority
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && element.priority >= current->next->data.priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }

        return true;
    }
}
//Remove and return highest priority element
Element PriorityQueue::remove() {
     if (isEmpty()) {
        return Element(); // Queue is empty, return default element
    } else {
        Element data = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return data;
    }
}

//Delete a specific element from the priority queue
bool PriorityQueue::del(Element &element) {
    bool found = false;
    
    Node* current = head;
    Node* prev = nullptr;

    while (current != nullptr) {
        // Check if the current node's element matches the specified element
        if (current->data.name == element.name && current->data.priority == element.priority) {
            found = true;
            if (prev == nullptr) {
                // If the matching node is the head, update the head
                head = current->next;
            } else {
                // If it's not the head, update the previous node's next pointer
                prev->next = current->next;
            }
            // Delete the current node to free memory
            delete current;
            current = nullptr;
            if (prev == nullptr) {
                current = head;
            } else {
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }

    return found;
}
// Peek at highest priority element without removing it
Element PriorityQueue::peek(){
    if (isEmpty()) {
        return Element(); // Queue is empty, return default element
    } else {
        Node* temp = head;
        Element max = head->data;
        while (temp != nullptr) {
            if (temp->data.priority < max.priority) {
                max = temp->data;
            }
            temp = temp->next;
        }
        return max;
    }
}
//Check if the priority queue contains a specific elemtn
bool PriorityQueue::contains(Element &element) {
   if(isEmpty()) {
    return false; //Queue is empty, the element cannot be present
   } else {
    Node *temp = head;
    while(temp != nullptr) {
        if(temp->data.name == element.name) {
            return true;//Element found
        }
        temp = temp->next;
    }
    return false; //Element not found
   }

}
//Get the current size of the priority queue
int PriorityQueue::size() {
    //Calculate the size by counting the number of elements in the linked list
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

//Clear the priority queue
void PriorityQueue::clear() {
    //Set the head to nullptr to clear the queue
    head = nullptr;
}

//Check if priority queue is empty
bool PriorityQueue::isEmpty() {
    return head == nullptr;
}

//Chcek if the priority queue is full
bool PriorityQueue::isFull() {
    return size() >= max_capacity;
}


/* IMPORTANT: main() must be EXACTLY how it was provided
** provided to you when you submit your assignment.
**
** If you edit main for your own testing purposes,
** you MUST restore it to how it was provided to
** you before submission. 
*/
int main() {
    test_PQLinkedList();
    return 0;
}