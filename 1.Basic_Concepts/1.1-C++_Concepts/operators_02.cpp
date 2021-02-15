#include <iostream>
#include <conio.h>

// Program prints out values to screen
int main(void)
{
    int a = 36;
    int b = 5;

    std::cout << "Value of ++a is : " << ++a << std::endl;
    std::cout << "Value of --b is : " << --b << std::endl;

    std::cout << "Value of a++ is : " << a++ << std::endl;
    std::cout << "Value of b-- is : " << b-- << std::endl;
    
    std::cout << "Value of a : " << a << std::endl;
    std::cout << "Value of b is : " << b << std::endl;

    _getch();
}