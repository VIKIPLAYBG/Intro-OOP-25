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
    :id(id), data(new int[capacity]) {
        if(capacity < 1)
        throw invalid_argument("The value must be positive.");
    }

    ~Vector() {
        delete[] data;
    }

    size_t getSize() const {
        if(data == NULL)
            return 0;
        return size;
    }

    size_t getCapacity() const {
        if(data == NULL)
            return 0;
        return capacity;
    }

    int getId() const {
        return id;
    }

    void pushBack(int number) {
        insert(size - 1, number);
    }

    int at(int index) const {
        if(data == NULL || index >= size || index < 0) {
            throw invalid_argument("Index is Out of Range.");
        }
        return data[index];
    }

    int insert(int index, int number) {
        if(index < 0 || index > size)
            throw invalid_argument("Index is Out of Range.");
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
        if(data == NULL || index < 0 || index >= size)
            throw invalid_argument("Index is Out of Range.");
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
        if(data == NULL || size == 0)
            throw invalid_argument("The Vector is empty!");
        return remove(size - 1);
    }
};