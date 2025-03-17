#include <iostream>

using namespace std;

class String
{
    char *data;
    size_t size;

public:
    /**
     * @brief Construct a new String object and it should have a default value of ""
     *
     */
    String()
    {
        size = 0;
        data = new char[1];
        data[0] = '\0';
    }

    /**
     * @brief Construct a new String object with the provided value
     *
     * @param str
     */
    String(const char *str)
    {
        size = 0;
        while (str[size] != '\0')
        {
            size++;
        }

        data = new char[size + 1];
        for (size_t i = 0; i <= size; i++)
        {
            data[i] = str[i];
        }
    }

    /**
     * TODO: Implement the copy constructor
     * @brief Construct a new String object by copying another string
     *
     * @param other
     */
    String(const String &other) {
        if(this != &other) {
            this->data = new char[other.size + 1]; 
            for(size_t i = 0; i < other.size; i++) {
                this->data[i] = other.data[i];
            }
            this->data[other.size] = '\0';
            this->size = other.size;
        }
    }

    /**
     * TODO: Implement the assignment operator
     * @brief Copies the values from the other string in this string
     *
     * @param other
     * @return String&
     */
    String &operator=(const String &other) {
        if(this != &other) {
            delete[] this->data;
            this->data = new char[other.size + 1]; 
            for(size_t i = 0; i < other.size; i++) {
                this->data[i] = other.data[i];
            }
            this->data[other.size] = '\0';
            this->size = other.size;
        }
        return *this;
    }

    /**
     * TODO: Implement the insert method
     * @brief Inserts a character at the provided index, if the index is bigger than the size of the string, just return the string, withouth modifying it
     *
     * @param index
     * @param c
     * @return String&
     */
    String &insert(size_t index, char c) {
        if(index > size)
            return *this;
        for(size_t i = size; i > index; i--) {
            data[i] = data[i-1];
        }
        data[index] = c;
        size++;
        return *this;
    }

    /**
     * TODO: Implement the replace method
     * @brief Replaces the character at the provided index, if the index is bigger than the size of the string, just return the string, withouth modifying it
     *
     * @param index
     * @param c
     * @return String&
     */
    String &replace(size_t index, char c) {
        if(index > size)
            return *this;

        data[index] = c;
        return *this;
    }

    /**
     * TODO: Implement the findFirstOf method
     * @brief Finds the first index, where the provided character is found, return -1 if the character is not found
     *
     * @param c
     * @return int
     */
    int findFirstOf(char c) const {
        for(size_t i = 0; data[i] != '\0'; i++) {
            if(data[i] == c)
                return i;
        }
        return -1;
    }

    /**
     * @brief Destroy the String object
     *
     */
    ~String()
    {
        delete[] data;
    }

    /**
     * @brief Returns the string as a C-style string - char*
     *
     * @return const char*
     */
    char *toCString() const
    {
        return data;
    }

    /**
     * @brief Returns the length of the string
     *
     * @return size_t
     */
    size_t length() const
    {
        return size;
    }

    /**
     * @brief Appends a character to the string
     *
     * @param ch
     */
    void append(char ch) {
        data[size++] = ch;
        data[size] = '\0';
    }

    /**
     * @brief Append the provided string to the current string
     *
     * @param str
     */
    void concat(const char *str) {
        for(int i = 0; str[i] != '\0'; i++) {
            append(str[i]);
        }
    }

    /**
     * @brief Compares 2 strings
     *
     * @param other
     * @return int 0 if the strings are equal, 1 if the current string is greater, -1 if the current string is smaller
     */
    int compare(const String &other) const {
        size_t i = 0;
        while(data[i] != '\0' && other.data[i] != '\0') {
            if(data[i] < other.data[i])
                return -1;
            if(data[i] > other.data[i])
                return 1;
            i++;
        }
        if (data[i] == '\0' && other.data[i] != '\0') {
            return -1;
        }
        if (data[i] != '\0' && other.data[i] == '\0') {
            return 1;
        }
        return 0;
    }
};