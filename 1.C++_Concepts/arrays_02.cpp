#include <iostream>
#include <conio.h>

#define MAX_N 4

// Program prints out value of n to screen
int main(void)
{
    int matrix[MAX_N][MAX_N] = {
        {2, 8, 10, -5},
        {15, 21, 22, 32},
        {3, 0, 19, 5},
        {5, 7, -23, 18}
    };

    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "" << std::endl;
    }
    
    _getch();
}