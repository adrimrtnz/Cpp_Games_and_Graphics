#include <iostream>
#include <conio.h>

// Program prints out value of n to screen
int main(void)
{
    int age = 18;
    int *pointer;

    pointer = &age;
    *pointer = 12;

    std::cout << age << std::endl;
        
    _getch();
}