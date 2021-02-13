#include <iostream>
#include <conio.h>

#define MAX_N 5

// Program prints out value of n to screen
int main(void)
{
    int age[MAX_N] = { 12, 6, 18, 7, 9};

    for (int i = 0; i < MAX_N; i++) {
        std::cout << "Element at the " << i << "th index is: " <<
        age[i] << std::endl;
    }
    
    _getch();
}