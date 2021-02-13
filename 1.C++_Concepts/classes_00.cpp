#include <iostream>
#include <conio.h>

class shape {
    int a, b;

    public:
        shape(int _lenght, int _width) {
            a = _lenght;
            b = _width;

            std::cout << "length is: " << a << " width is: " << b << std::endl;
        }

        void area() {
            std::cout << "Area is: " << a * b << std::endl;
        }
};

int main(void)
{
    shape square(8, 8);
    square.area();

    shape rectangle(12, 20);
    rectangle.area();

    _getch;
}