#include <iostream>
#include <conio.h>

#define MAX_N 5

// Program prints out value of n to screen
int main(void)
{
    int *p = NULL;   // declare a null pointer
    int age[MAX_N] = { 12, 6, 18, 7, 9};
    p = age;

    std::cout << *p << std::endl;

    p++;

    std::cout << *p << std::endl;
    std::cout << *(p + 3) << std::endl;
    std::cout << *p << std::endl;
        
    _getch();
}