#include <iostream>
#include <conio.h>

class shape {
    
    protected:
        float a, b;

    public:
        void setValues(float _lenght, float _width) {
            a = _lenght;
            b = _width;

            std::cout << "length is: " << a << " width is: " << b << std::endl;
        }

        void area() {
            std::cout << "Area is: " << a * b << std::endl;
        }
};

class triangle : public shape {

    public:
        void area() {
            std::cout << "Area of the triangle is: " << 0.5f * a * b << std::endl;
        }
};

int main(void)
{
    shape rectangle;
    rectangle.setValues(8.0f, 12.0f);
    rectangle.area();

    triangle tri;
    tri.setValues(3.0f, 23.0f);
    tri.area();

    _getch;
}