#pragma once

#include <iostream>

template<class T>
class Rc{
private:
    T *val;
    size_t *count;
public:
    Rc() : val(new T), count(new size_t(1)) {
        std::cout << "Allocated memory, default constructor\n";
    }

    Rc(T&& value) : val(new T(value)), count(new size_t(1)) {
        std::cout << "Allocated memory, moved value\n";
    }

    template<class... Args>
    Rc(Args... args) : val(new T(args...)), count(new size_t(1)) {
        std::cout << "Allocated memory, with arguments\n";
    }

    Rc(Rc& other) : val(other.val), count(other.count) {
        std::cout << "Added a reference\n";
        (*count)++;
    }

    Rc(Rc&& other) = delete;

    ~Rc() {
        std::cout << "\nDestructor called\n";
        (*count)--;
        if(*count == 0) {
            std::cout << "Freed memory\n";
            delete val;
            delete count;
        }
    }

    T* operator->() {
        return val;
    }

    T& operator*() {
        return *val;
    }
};
