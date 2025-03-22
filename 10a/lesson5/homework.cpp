#include <iostream>
#include <exception>
using namespace std;

class Vector
{
    int* data;
    size_t size;
    size_t capacity;
    const int id;

    void resize() {
        capacity *= 2;
        int *tmp = new int[capacity];
        for (size_t i = 0; i < size; i++)
        {
            tmp[i] = data[i];
        }
        delete[] data;
        data = tmp;
    }

public:
    Vector(int id, int capacity)
    : id(id), capacity(capacity), data(nullptr), size(0) {
    if (capacity < 1)
        throw invalid_argument("Capacity must be positive.");
    if (id < 1)
        throw invalid_argument("ID must be positive.");

    data = new int[capacity];
    }

    ~Vector() {
        delete[] data;
    }

    size_t getSize() const {
        return this->size;
    }

    size_t getCapacity() const {
        return this->capacity;
    }

    int getId() const {
        return this->id;
    }

    void pushBack(int number) {
        insert(size, number);
    }

    int at(int index) const {
        if(this == nullptr || index >= size || index < 0) {
            throw out_of_range("Index is Out of Range.");
        }
        return data[index];
    }

    int insert(int index, int number) {
        if(index < 0 || index > size) {
            throw out_of_range("Index is Out of Range.");
        }
        if (size == capacity) {
            resize();
        }
        for(size_t i = size; i > index; i--) {
            data[i] = data[i-1];
        }
        data[index] = number;
        size++;
        return 0;
    }

    int remove(int index) {
        if(this == nullptr || index < 0 || index >= size)
            throw out_of_range("Index is Out of Range.");
        size_t result = data[index];
        for(size_t i = index; i < size - 1; i++) {
            data[i] = data[i+1];
        }
        size--;
        if(size < capacity / 4 && capacity > 2) {
            capacity /= 2;
            resize();
        }
        return result;
    }

    int pop() {
        if(this == nullptr || size == 0)
            throw out_of_range("Index is Out of Range.");    
        return remove(size - 1);
    }
};