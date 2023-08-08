#pragma once

template<class T>
class Box{
private:
    T *val;
public:
    Box() : val(new T) {
    }

    Box(T&& value) : val(new T(value)) {
    }

    Box(Box& other) = delete;

    Box(Box&& other) : val(other.val) {
        other.val = NULL;
    }

    template<class... Args>
    Box(Args... args) : val(new T(args...)) {
    }

    ~Box() {
        if(val != NULL){
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
