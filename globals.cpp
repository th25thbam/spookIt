#include "globals.h"

int pumpkins = 0;
int pumpkinX = 400;
int pumpkinY = 300;
int pumpkinRadius = 40;
int score = 0;
float pumpkinTimer = 0.0f;
float pumpkinDuration = 2.0f;
bool popping = false;
float popTimer = 0.0f;
int pumpkinPoints = 1;
int lives = 5;
bool gameOver = false;
bool gameStarted = false;
float difficultyTimer = 0.0f;
int popX = 0;
int popY = 0;
int popRadius = 0;

Star stars[num_stars];