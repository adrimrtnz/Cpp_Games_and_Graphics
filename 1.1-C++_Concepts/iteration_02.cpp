#include <iostream>
#include <conio.h>

// Program prints out values to screen
int main(void)
{
    for(int n = 0; n < 10; n += 2)
    {
        std::cout << "Value of n is: "<< n << std::endl;
    }
    _getch();
}