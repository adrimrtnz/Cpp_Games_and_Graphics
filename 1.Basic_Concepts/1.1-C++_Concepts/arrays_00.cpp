#include <iostream>
#include <conio.h>

#define MAX_N 5

// Program prints out value of n to screen
int main(void)
{
    int age[MAX_N] = { 12, 6, 18, 7, 9};

    std::cout << "Element at the 0th index " << age[0] << std::endl;
    std::cout << "Element at the 4th index " << age[4] << std::endl;
    
    _getch();
}