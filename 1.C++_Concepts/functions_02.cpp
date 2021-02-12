#include <iostream>
#include <conio.h>

// Program prints out value of n to screen

int multiply(int a, int b)
{
    return a * b;
}

float multiply(float a, float b)  // function overloading
{
    return a * b;
}

int main(void)
{
    float x = 8.352f;
    float y = -12.365f;
    
    float d = multiply(x, y);

    std::cout << "Value returned by multiplying " << x << " and " << y << " is " << d << std::endl;
    
    _getch();
}