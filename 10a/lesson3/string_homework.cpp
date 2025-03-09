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
    String() {
        size = 0;
        data = new char[size + 1];
        data[0] = '\0';
    }

    /**
     * @brief Construct a new String object with the provided value
     *
     * @param str
     */
    String(const char *str) {
        size = strlen(str);
        data = new char[size + 1];
        strcpy(data, str);
    }

    /**
     * @brief Destroy the String object
     *
     */
    ~String() {
        delete[] data;
        size = 0;
    }

    /**
     * @brief Returns the string as a C-style string - char*
     *
     * @return const char*
     */
    char *toCString() const {
        return data;
    }

    /**
     * @brief Returns the length of the string
     *
     * @return size_t
     */
    size_t length() const {
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