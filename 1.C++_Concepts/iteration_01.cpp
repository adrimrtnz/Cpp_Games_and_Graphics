#include <iostream>
#include <conio.h>

// Program prints out values to screen
int main(void)
{
    int a = 10;
    int n = 0;

    do {
        std::cout << "Value of n is: " << n << std::endl;
        n++;
    } while (n < a);

    _getch();
}