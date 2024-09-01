#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WIDTH 20
#define HEIGHT 20
#define TILE_SIZE 30
#define MAX_TAIL 100

int snakeX, snakeY, fruitX, fruitY, score;
int tailX[MAX_TAIL], tailY[MAX_TAIL];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;
bool gameOver;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void setup() {
    score = 0;
    dir = STOP;
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    nTail = 0;
    gameOver = false;
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background to black
    SDL_RenderClear(renderer);

    // Draw the fruit
    SDL_Rect fruitRect = { fruitX * TILE_SIZE, fruitY * TILE_SIZE, TILE_SIZE, TILE_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
    SDL_RenderFillRect(renderer, &fruitRect);

    // Draw the snake
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
    for (int i = 0; i < nTail; i++) {
        SDL_Rect tailRect = { tailX[i] * TILE_SIZE, tailY[i] *
