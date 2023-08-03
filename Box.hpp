#pragma once

#include <iostream>

template<class T>
class Box{
private:
    T *val;
public:
    Box() : val(new T) {
        std::cout << "Allocated memory, default constructor\n";
    }

    Box(T&& value) : val(new T(value)) {
        std::cout << "Allocated memory, moved value\n";
    }

    Box(Box& other) = delete;

    Box(Box&& other) : val(other.val) {
        std::cout << "Moved pointer\n";
        other.val = NULL;
    }

    template<class... Args>
    Box(Args... args) : val(new T(args...)) {
        std::cout << "Allocated memory, with arguments\n";
    }

    ~Box() {
        std::cout << "\nDestructor called\n";
        if(val != NULL){
            std::cout << "Freed memory\n";
            delete val;
        }
    }

    T* operator->() {
        return val;
    }

    T& operator*() {
        return *val;
    }
};
