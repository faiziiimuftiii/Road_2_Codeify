#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h> // For usleep in Unix-based systems
#define Sleep(x) usleep((x) * 1000) // Convert milliseconds to microseconds
#endif

#define WIDTH 20
#define HEIGHT 20
#define MAX_TAIL 100

int x, y, fruitX, fruitY, score;
int tailX[MAX_TAIL], tailY[MAX_TAIL];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirection dir;

void Setup()
{
    score = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    nTail = 0;
}

void Draw()
{
    #ifdef _WIN32
    system("cls"); // Clear the console
    #else
    printf("\033[H\033[J"); // ANSI escape codes to clear the console on Unix-based systems
    #endif

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == WIDTH - 1)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == fruitY && j == fruitX)
                printf("F");
            else
            {
                bool isTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        printf("o");
                        isTail = true;
                    }
                }
                if (!isTail)
                    printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
    printf("Score: %d\n", score);
}

void Input()
{
    #ifdef _WIN32
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            exit(0);
        }
    }
    #else
    // For Unix-based systems, implement input handling if needed
    #endif
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
    tailX[i] = prevX;