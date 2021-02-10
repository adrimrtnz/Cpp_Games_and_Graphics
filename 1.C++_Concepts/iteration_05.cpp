#include <iostream>
#include <conio.h>

// Program prints out values to screen
int main(void)
{
    int a = 28;
    
    switch (a)
    {
        case 1:
            std::cout << "Value of a is " << a << std::endl;
            break;
        case 2:
            std::cout << "Value of a is " << a << std::endl;
            break;
        case 3:
            std::cout << "Value of a is " << a << std::endl;
            break;
        case 4:
            std::cout << "Value of a is " << a << std::endl;
            break;
        case 5:
            std::cout << "Value of a is " << a << std::endl;
            break;
        default:
            std::cout << "Value of a is out of range" << std:: endl;
    }

    _getch();
}