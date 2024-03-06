//Nick Ingargiola
//827476189
//CS210
#include "SortableArray.h"

SortableArray::SortableArray() {     //Default Constructor
    max_size = DEFAULT_TEST_SIZE;
    count = 0;
    arr = new int[max_size];
}

SortableArray::SortableArray(int size) {  //Default constructor with size
    max_size = size;
    arr = new int[max_size];
    count = 0;
}

bool SortableArray::add(int element) {  //Adds element to the array
    if(count < max_size) {
        arr[count++] = element;
        return true;
    }
    return false;
}

bool SortableArray::add(int element, int index) { //adds element to the array to a specific index
    if(index >= 0 && index <= count && count < max_size) { //and shifts the rest of the array
        for(int i = count; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = element;
        count++;
        return true;
    }
    return false;
}

int SortableArray::get(int index) { //returns the value at a specific index
    if(index >= 0 && index < count) {
        return arr[index];
    }
    return -1;
}

int SortableArray::remove(int index) { //returns and removes value from the array at a specific index
    if(index >= 0 && index < count) {
        int removed = arr[index];
        for(int i = index; i < count-1; i++) {
            arr[i] = arr[i + 1];
        }
        count--;
        return removed;
    }
    return -1;
}

int SortableArray::size() const { //returns the size of the array
    return max_size;
}

bool SortableArray::readFile(std::string fileName) { //reads the file and stores each number
    std::ifstream file(fileName);                //into the array
    if (!file.is_open()) {
        return false; // Failed to open file
    }
    int num;
    while (file >> num) {
        if (count < max_size) {
            arr[count++] = num;
        } else {
            break;
        }
    }
    file.close();
    return true;
}


bool SortableArray::saveFile(std::string fileName) { //saves the array into a text file
    std::ofstream file(fileName);
    if (!file.is_open()) {
        return false; // Failed to open file
    }
    for (int i = 0; i < count; i++) {
        file << arr[i] << " ";
    }
    file.close();
    return true;
}


void SortableArray::insertionSort() { //sorts the array with insertionSort
    for (int i = 1; i < count; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


