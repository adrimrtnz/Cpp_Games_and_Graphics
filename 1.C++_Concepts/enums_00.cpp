#include <iostream>
#include <conio.h>

enum Weekdays {
    Monday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

// Program prints out value of n to screen
int main(void)
{
    Weekdays today;

    today = Friday;

    if (today == Friday) {
        std::cout << "The weekend is here!!!" << std::endl;
    }
        
    _getch();
}