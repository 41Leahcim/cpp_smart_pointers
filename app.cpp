#include <iostream>
#include <vector>

#include "Box.hpp"
#include "Rc.hpp"

void box_test(){
    Box<int> box(1);
    Box<int> box2(2);
    Box<int> box3 = std::move(box);
    //Box<int> errors = box3;
    //Box<int> errors(box3);

    Box<std::vector<int>> box4(10);
    box4->push_back(1);

    std::cout << *box2 + *box3 << '\n';
    Box<std::vector<int>> box5(*box4);
}

void rc_test(){
    Rc<int> rc(1);
    Rc<int> rc2(2);
    Rc<int> rc3(rc);
    Rc<int> rc4 = rc3;
    //Rc<int> errors = std::move(rc3);

    Rc<std::vector<int>> rc5(10);
    rc5->push_back(1);

    std::cout << *rc2 + *rc3 << '\n';
    Rc<std::vector<int>> rc6(*rc5);
    Rc<std::vector<int>> rc7(rc5);
}

void print_test_mark(const char *test_name){
    std::cout << "======" << test_name << "======\n";
}

int main(){
    print_test_mark("Start box test");
    box_test();
    print_test_mark("End box test");
    print_test_mark("Start rc test");
    rc_test();
    print_test_mark("End rc test");
}
