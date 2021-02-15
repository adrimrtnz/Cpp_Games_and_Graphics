#include <iostream>
#include <conio.h>

// Program prints out value of bool, char and float
int main(void)
{
    bool a = false;
    char b = 'b';
    float c = 3.1416f;
    unsigned int d = 82;

    std::cout << "Value of a is: " << a << std::endl;
    std::cout << "Value of b is: " << b << std::endl;
    std::cout << "Value of c is: " << c << std::endl;
    std::cout << "Value of d is: " << d << std::endl;

    _getch();
}