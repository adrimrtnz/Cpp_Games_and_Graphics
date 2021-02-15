#include <iostream>
#include <conio.h>

// Program prints out value of n to screen

int multiply(int a, int b)
{
    return a * b;
}

int main(void)
{
    int x = 28;
    int y = 12;
    
    int c = multiply(x, y);

    std::cout << "Value returned by multiplying " << x << " and " << y << " is " << c << std::endl;
    
    _getch();
}