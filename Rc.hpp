#pragma once

#include <iostream>

template<class T>
class __Rc__{
private:
    T val;
    size_t count;
public:
    __Rc__() : val(), count(1){}

    __Rc__(T&& value) : val(value), count(1){}

    template<class ... Args>
    __Rc__(Args... args) : val(args...), count(1){}

    void operator++(){ count++; }

    void operator--(){ count--; }

    size_t Count() const { return count; }

    T* Value(){ return &val; }
};

template<class T>
class Rc{
private:
    __Rc__<T> *counter;
public:
    Rc() : counter(new __Rc__<T>) {
        std::cout << "Allocated memory, default constructor\n";
    }

    Rc(T&& value) : counter(new __Rc__<T>(value)) {
        std::cout << "Allocated memory, moved value\n";
    }

    template<class... Args>
    Rc(Args... args) : counter(new __Rc__<T>(args...)) {
        std::cout << "Allocated memory, with arguments\n";
    }

    Rc(Rc& other) : counter(other.counter) {
        std::cout << "Added a reference\n";
        ++(*counter);
    }

    Rc(Rc&& other) = delete;

    ~Rc() {
        std::cout << "\nDestructor called\n";
        --(*counter);
        if(counter->Count() == 0) {
            std::cout << "Freed memory\n";
            delete counter;
        }
    }

    T* operator->() {
        return counter->Value();
    }

    T& operator*() {
        return *counter->Value();
    }
};
