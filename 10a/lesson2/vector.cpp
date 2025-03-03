#include <iostream>

using namespace std;

///////////////////////////////
//* snake_case
//* PascalCase
//* camileCase
//* kebab-case
//////////////////////////////

//////////////////////////////
// Diff between i++ and ++i
//////////////////////////////
// int i++(int i)
// {
//     int tmp = i;
//     i = i + 1;
//     return tmp;
// }

// int ++i(int)
// {
//     return i + 1;
// }
//////////////////////////////

int VERROR = -1;

struct vector_t
{
    int *data;
    size_t size;
    size_t capacity;
} typedef Vector;

Vector* initVector();

void pushBack(Vector *v, int number);

void resize(Vector *v);

//////////////////////////////
// Vector's size:
// Vector's capacity:
// Vector's data:
//////////////////////////////
void print(Vector *v);

/**
 * @brief Returns the element at the provided index
 *
 * @param v
 * @param index
 * @return int
 */
int at(Vector *v, int index);

/**
 * @brief Pops the last element of the vector
 *
 * @param v
 * @return int if successful, VERROR - if not
 */
int pop(Vector *v);

/**
 * @brief Frees the memory allocated by the vector
 *
 * @param v
 */
void destroy(Vector *v);

/**
 * @brief Adds an element in the beginning of the vector
 *
 * @param v
 * @param number
 */
void pushFront(Vector *v, int number);

/**
 * @brief Pops the first element of the vector
 *
 * @param v
 * @return int if successful, VERROR - if not
 */
int popFront(Vector *v);

/**
 * @brief Inserts an element at a given index
 *
 * @param v
 * @param index
 * @param number
 * @return int 0 if successful, VERROR - if not
 */
int insert(Vector *v, int index, int number);

/**
 * @brief Removes an element at a given index
 *
 * @param v
 * @param index
 * @param number
 * @return int the number if usccesful, VERROR - if not
 */
int remove(Vector *v, int index);

Vector* initVector()
{
    Vector *v = new Vector();
    v->size = 0;
    v->capacity = 2;
    v->data = new int[v->capacity];

    return v;
}

void pushBack(Vector *v, int number)
{
    if (v->size == v->capacity) {
        resize(v);
    }
    v->data[v->size++] = number;
}

void resize(Vector *v)
{
    v->capacity *= 2;
    int *tmp = new int[v->capacity];
    for (size_t i = 0; i < v->size; i++)
    {
        tmp[i] = v->data[i];
    }
    delete[] v->data;
    v->data = tmp;
}

void print(Vector *v)
{
    cout << "Vector's size: " << v->size << endl;
    cout << "Vector's capacity: " << v->capacity << endl;
    cout << "Vector's data: [";

    if (v->size > 0)
        cout << v->data[0];
    for (size_t i = 1; i < v->size; i++)
    {
        cout << " " << v->data[i];
    }
    cout << "]" << endl;
}


int at(Vector *v, int index) 
{
    if(v == NULL || index >= v->size || index < 0) {
        return VERROR;
    }
    return v->data[index];
}

int pop(Vector *v) 
{
    if(v == NULL) 
        return VERROR;
    return remove(v, v->size - 1);
}

void destroy(Vector *v) 
{
    delete[] v->data;
    v->data = NULL;

    v->capacity = 0;
    v->size = 0;
}

void pushFront(Vector *v, int number) 
{
    insert(v, 0, number);
}

int popFront(Vector *v) 
{
    return remove(v, 0);
}

int insert(Vector *v, int index, int number) 
{
    if (v->size == v->capacity) {
        resize(v);
    }
    for(size_t i = v->size - 1; i > index; i--) {
        v->data[i] = v->data[i-1];
    }
    return v->data[index] = number;
}

int remove(Vector *v, int index) 
{
    if(v == NULL || index < 0 || index >= v->size)
        return VERROR;
    size_t result = v->data[index];
    for(size_t i = index; i < v->size - 1; i++) {
        v->data[i] = v->data[i+1];
    }
    v->size--;
    if(v->size < v->capacity / 4) {
        v->capacity /= 4;
        resize(v);
    }
    return result;
}