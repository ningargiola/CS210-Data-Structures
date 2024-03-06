//Nick Ingargiola
//827476189
// PQOrdered.cpp
// Implement your Ordered Priority Queue in this file
#include "PriorityQueue.h"
#include "TestDriver.h"
// Your code here

//Constructor
PriorityQueue::PriorityQueue() {
    max_capacity = DEFAULT_MAX_CAPACITY;
    pq = std::unique_ptr<Element[]>(new Element[max_capacity]);
}
//Constructor with size parameter
PriorityQueue::PriorityQueue(int size) {
    max_capacity = size;
    pq = std::unique_ptr<Element[]>(new Element[max_capacity]);

}
//Inserts a new element
bool PriorityQueue::insert(Element &element) {
    if (size() == max_capacity) {
        return false; // Queue is full
    }

    int index = size();
    while (index > 0 && (element.priority < pq[index - 1].priority || (element.priority == pq[index - 1].priority && element.fifo < pq[index - 1].fifo))) {
        pq[index] = pq[index - 1];
        index--;
    }

    pq[index] = element;

    return true;
}
//Removes and returns the element with highest priority
Element PriorityQueue::remove() {
    if (isEmpty()) {
        return Element(); // Return a default-constructed Element for an empty queue
    }

    Element oldestElement = pq[0]; // Get the oldest element at the front of the queue

    // Shift the remaining elements to fill the gap
    for (int i = 1; i < size(); i++) {
        pq[i - 1] = pq[i];
    }

    // Clear the last element to maintain the size
    pq[size() - 1] = Element();

    return oldestElement;
}
//Deletes all instances of parameter
bool PriorityQueue::del(Element &element) {
    int count = 0;
    for(int i = 0; i < size(); i++) {
        if(pq[i].name == element.name && pq[i].priority == element.priority) {
            count++;
        } else {
            pq[i - count] = pq[i];
        }
    }
    if(count > 0) {
        //Clear the remaianing element after deletion
        for(int i = size() - count; i < size(); i++) {
            pq[i] = Element();
        }
    }
    return count > 0;
}
//Returns highest priority element without removing it
Element PriorityQueue::peek(){
    if(isEmpty()) {
        return Element();//Returns default-constructed Element for an empty queue
    }
    return pq[0];
}
//Returns true if the queue contains a specific element
bool PriorityQueue::contains(Element &element) {
    for(int i = 0; i < size(); i++) {
        if(pq[i].name == element.name) {
            return true;
        }
    }
    return false;
}
//Returns the number of objects currently in the PQ
int PriorityQueue::size() {
    int count = 0;
    for (int i = 0; i < max_capacity; i++) {
        if (!pq[i].name.empty() && pq[i].priority >= 0) {
            count++;
        }
    }
    return count;
}
//Clears the PriorityQueue to its deafault state
void PriorityQueue::clear() {
    for(int i = 0; i < max_capacity; i++) {
        pq[i] = Element();
    }
}
//Returns true if empty
bool PriorityQueue::isEmpty() {
    return size() == 0;
}
// Returns true if full
bool PriorityQueue::isFull() {
    return size() == max_capacity;
}

/* IMPORTANT: main() must be EXACTLY how it was provided
** provided to you when you submit your assignment.
**
** If you edit main for your own testing purposes,
** you MUST restore it to how it was provided to
** you before submission. 
*/
int main() {
    test_PQOrdered();
    return 0;
}