#include <iostream>
#include <Windows.h>

using namespace std;

const int MAX_PIECES = 7;
wstring tetromino[MAX_PIECES];

const int BOARD_WIDTH = 12;
const int BOARD_HEIGHT = 18;
unsigned char* board_array = nullptr;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 30;
wchar_t* screen = nullptr;

bool isGameOver = false;

void init_tetrominos();
void init_game_board();
void init_screen();
int Rotate(int px, int py, int r);

int main()
{
    // Create tetrominos (tetris pieces)
    init_tetrominos();
    init_game_board();
    init_screen();

    HANDLE Console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(Console);
    DWORD BytesWritten = 0;

    while (!isGameOver)
    {
        // Draw Field
        for (int x = 0; x < BOARD_WIDTH; x++) {
            for (int y = 0; y < BOARD_HEIGHT; y++) {
                screen[(y + 2) * SCREEN_WIDTH + (x + 2)] = L" ABCDEFG=#"[board_array[y * BOARD_WIDTH + x]];
            }
        }

        // Display Screen Frame
        WriteConsoleOutputCharacter(Console, screen, SCREEN_WIDTH * SCREEN_HEIGHT, {0,0}, &BytesWritten);
    }

    return 0;
}

void init_tetrominos()
{
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");
}

void init_game_board()
{
    board_array = new unsigned char[BOARD_WIDTH * BOARD_HEIGHT];

    // Create Board Boundaries
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            board_array[y * BOARD_WIDTH + x] = (x == 0 || x == BOARD_WIDTH - 1 || y == BOARD_HEIGHT - 1) ? 9 : 0;
        }
    }
}

void init_screen()
{
    screen = new wchar_t[SCREEN_WIDTH * SCREEN_HEIGHT];

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        screen[i] = L' ';
    }
}

int Rotate(int px, int py, int r)
{
    // The following will work mapping the tetrominos as 4x4 matrices
    switch (r % 4)
    {
    case 0: return py * 4 + px;         // 0 deg
    case 1: return 12 + py - (px * 4);  // 90 deg
    case 2: return 15 - (py * 4) - px;  // 180 deg
    case 3: return 3 - py + (px * 4);   // 270 ded
    }

    return 0;
}