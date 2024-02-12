#pragma once

#include <atomic>

template<class T>
class __Rc__{
private:
    T val;
    std::atomic_size_t count;
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
    }

    Rc(T&& value) : counter(new __Rc__<T>(value)) {
    }

    template<class... Args>
    Rc(Args... args) : counter(new __Rc__<T>(args...)) {
    }

    Rc(Rc& other) : counter(other.counter) {
        ++(*counter);
    }

    Rc(Rc&& other) = delete;

    ~Rc() {
        --(*counter);
        if(counter->Count() == 0) {
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
