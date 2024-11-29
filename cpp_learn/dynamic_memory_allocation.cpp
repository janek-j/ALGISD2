#include <iostream>

int main(int args, char* argv[]) {

    int *ptr = new int;
    *ptr = 5;

    std::cout << "Number: " << *ptr << std::endl;

    std::cout << "Address of the pointer: " << &ptr << std::endl;

    delete ptr;

    return 0;
}