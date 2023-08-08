#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

#include "Box.hpp"
#include "Rc.hpp"

void box_test(bool print){
    Box<int> box(1);
    Box<int> box2(2);
    Box<int> box3 = std::move(box);
    //Box<int> errors = box3;
    //Box<int> errors(box3);

    Box<std::vector<int>> box4(10);
    box4->push_back(1);

    if(print){
        std::cout << *box2 + *box3 << '\n';
    }
    Box<std::vector<int>> box5(*box4);
}

void rc_test(bool print){
    Rc<int> rc(1);
    Rc<int> rc2(2);
    Rc<int> rc3(rc);
    Rc<int> rc4 = rc3;
    //Rc<int> errors = std::move(rc3);

    Rc<std::vector<int>> rc5(10);
    rc5->push_back(1);

    if(print){
        std::cout << *rc2 + *rc3 << '\n';
    }
    Rc<std::vector<int>> rc6(*rc5);
    Rc<std::vector<int>> rc7(rc5);
}

void print_test_mark(const char *test_name){
    std::cout << "======" << test_name << "======\n";
}

void memory_leak_test(){
    print_test_mark("Start box test");
    box_test(true);
    print_test_mark("End box test");
    print_test_mark("Start rc test");
    rc_test(true);
    print_test_mark("End rc test");
}

void performance_test(){
    uint64_t box_iterations = 0, rc_iterations = 0;
    clock_t start = clock();
    while(clock() - start < CLOCKS_PER_SEC){
        box_test(false);
        box_iterations++;
    }
    std::cout << "Box iterations: " << box_iterations << '\n';

    start = clock();
    while(clock() - start < CLOCKS_PER_SEC){
        rc_test(false);
        rc_iterations++;
    }
    std::cout << "Rc iterations: " << rc_iterations << '\n';
}

int main(int argc, const char **args){
    if(argc >= 2){
        std::string mode = args[1];
        std::transform(mode.begin(), mode.end(), mode.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if(mode == "memory"){
            memory_leak_test();
        }else if(mode == "performance"){
            performance_test();
        }else{
            std::cout << "Only valid modes are: [memory] [performance]\n";
        }
    }else{
        memory_leak_test();
        performance_test();
    }
}
