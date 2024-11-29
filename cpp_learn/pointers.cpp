#include <iostream>

int main(int args, char* argv[]) {

    int x = 2137; //random number
    int *ptr = &x; //pointer that stores memory address of x.

    std::cout << "Number: " << x << "." << std::endl;

    std::cout << "Pointer of number: " << &ptr << std::endl;

    std::cout << "Pointer points to: " << *ptr << std::endl;

    return 0;
}