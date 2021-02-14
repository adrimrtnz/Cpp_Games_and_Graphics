#include <iostream>
#include <conio.h>

// Program prints out value of n to screen

void add(int a, int b)
{
    int c = a + b;

    std::cout << "Sum of " << a << " and " << b << " is " << c << std::endl;
}

int main(void)
{
    int x = 28;
    int y = 12;
    add(x, y);
    
    _getch();
}