//Nick Ingargiola
//827476189
// PQHeap.cpp
// Implement your Heap Priority Queue in this file
#include "PriorityQueue.h"
#include "TestDriver.h"
// Your code here
int current_size;

//Constructor 
PriorityQueue::PriorityQueue() {
    max_capacity = DEFAULT_MAX_CAPACITY;
    head = nullptr;
    pq = std::unique_ptr<Element[]>(new Element[max_capacity]);
    current_size = 0;

}
//Constructor with parameter
PriorityQueue::PriorityQueue(int size) {
    max_capacity = size;
    head = nullptr;
    pq = std::unique_ptr<Element[]>(new Element[max_capacity]);
    current_size = 0;
}
//Insert element
bool PriorityQueue::insert(Element &element) {
    if (current_size < max_capacity) {
        pq[current_size] = element;
        pq[current_size].fifo = current_size;
        //Move the newly inserted element into correct position
        int index = current_size;
        int parent = (index - 1) / 2;
        while (index > 0 && pq[index].priority < pq[parent].priority) {
            std::swap(pq[index], pq[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }

        current_size++;
        return true;
    }
    return false; //Queue is full
}
//Remove and return the element with the highest priority
Element PriorityQueue::remove() {
    if (current_size > 0) {
    Element highestPriority = pq[0];
    current_size--;

    if (current_size > 0) {
        pq[0] = pq[current_size];
        pq[0].fifo = 0;
        //Restore the heap structure 
        int index = 0;
        int left, right, smallest;
        while (true) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;

            if (left < current_size && pq[left].priority < pq[smallest].priority) {
                smallest = left;
            }
            if (right < current_size && pq[right].priority < pq[smallest].priority) {
                smallest = right;
            }

            if (smallest != index) {
                std::swap(pq[index], pq[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }
    return highestPriority;
    }
    return Element();//Queue is empty, return default Element

}
//Delete all instances of a specified element from the priority queue
bool PriorityQueue::del(Element &element) {
    bool found = false;
    int i = 0;
    while (i < current_size) {
        if (pq[i].name == element.name && pq[i].priority == element.priority) {
            found = true;
            current_size--;

            if (i < current_size) {
                pq[i] = pq[current_size];
                pq[i].fifo = i;
                //Maintain heap property
                int index = i;
                int parent = (index - 1) / 2;
                while (index > 0 && pq[index].priority < pq[parent].priority) {
                    std::swap(pq[index], pq[parent]);
                    index = parent;
                    parent = (index - 1) / 2;
                }
                //Restore heap structure
                int left, right, smallest;
                while (true) {
                    left = 2 * index + 1;
                    right = 2 * index + 2;
                    smallest = index;

                    if (left < current_size && pq[left].priority < pq[smallest].priority) {
                        smallest = left;
                    }
                    if (right < current_size && pq[right].priority < pq[smallest].priority) {
                        smallest = right;
                    }

                    if (smallest != index) {
                        std::swap(pq[index], pq[smallest]);
                        index = smallest;
                    } else {
                        break;
                    }
                }
            }
        } else {
            i++;
        }
    }
    return found;
}
// Return the element with the highest priority without removinb
Element PriorityQueue::peek(){
    if (current_size > 0) {
        return pq[0];
    }
    return Element();//Queue is empty, return default Element
}
//Check if the pq contains a specified element 
bool PriorityQueue::contains(Element &element) {
    for (int i = 0; i < current_size; i++) {
        if (pq[i].name == element.name && pq[i].priority == element.priority) {
            return true;
        }
    }
    return false;
}
//Return the cuurent number of elements
int PriorityQueue::size() {
    return current_size;

}
//Clear the pq and return it to its default state
void PriorityQueue::clear() {
    current_size = 0;
}
//Chceck if pq is empty
bool PriorityQueue::isEmpty() {
    return current_size == 0;
}
//Check if pq is full
bool PriorityQueue::isFull() {
    return current_size = max_capacity;
}

/* IMPORTANT: main() must be EXACTLY how it was provided
** provided to you when you submit your assignment.
**
** If you edit main for your own testing purposes,
** you MUST restore it to how it was provided to
** you before submission. 
*/
int main() {
    test_PQHeap();
    return 0;
}


