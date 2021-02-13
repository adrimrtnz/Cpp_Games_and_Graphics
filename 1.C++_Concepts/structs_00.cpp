#include <iostream>
#include <conio.h>

struct student {
    int age;
    float height;
};

// Program prints out value of n to screen
int main(void)
{
    student section[3];

    section[0].age = 17;
    section[0].height = 39.45f;

    section[1].age = 12;
    section[1].height = 29.45f;

    section[2].age = 7;
    section[2].height = 13.45f;

    for (int i = 0; i < 3; i++) {
        std::cout << "Student " << i << " age: " << section[i].age << " height: " << 
            section[i].height << std::endl;
    }
        
    _getch();
}