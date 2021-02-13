#include <iostream>
#include <conio.h>

// Program prints out value of n to screen
int main(void)
{
    int age = 32;
    int *location = &age;

    std::cout << location << std::endl;
        
    _getch();
}