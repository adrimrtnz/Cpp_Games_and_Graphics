#include <iostream>
#include <conio.h>

// Program prints out values to screen
int main(void)
{
    int a = 28;
    int b = 28;

    if (a > b)
    {
        std::cout << a << " is greater than " << b << std::endl;
    }
    else if (a == b)
    {
        std::cout << a << " is equal to " << b << std::endl;
    }
    else
    {
        std::cout << b << " is greater than " << a << std::endl;
    }

    _getch();
}