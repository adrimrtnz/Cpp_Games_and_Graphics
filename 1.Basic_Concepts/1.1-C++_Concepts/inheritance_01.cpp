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

        // Overloaded version to calculate the area of a circle
        void setValues(float _r) {
            a = _r;
        }

        void area() {
            std::cout << "Area is: " << a * b << std::endl;
        }
};

class triangle : public shape {

    public:
        void area() {
            std::cout << "Area of the Triangle is: " << 0.5f * a * b << std::endl;
        }
};

class circle : public shape {

    public:
        void area() {
            std::cout << "Area of the Circle is: " << 3.14f * a * a << std::endl;
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

    circle c;
    c.setValues(5.0f);
    c.area();

    _getch;
}