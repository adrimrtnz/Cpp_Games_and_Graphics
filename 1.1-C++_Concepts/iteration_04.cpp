#include <iostream>
#include <conio.h>

// Program prints out values to screen
int main(void)
{
    for(int n = 0; n < 10; n++)
    {
        if (n == 5) {
            std::cout << "continue" << std::endl;
            continue;
        }
        std::cout << "Value of n is: "<< n << std::endl;
    }
    _getch();
}