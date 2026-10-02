#ifndef GLOBALS_H
#define GLOBALS_H
extern int pumpkins;
extern int pumpkinX;
extern int pumpkinY;
extern int pumpkinRadius;
extern int score;
extern float pumpkinTimer;
extern float pumpkinDuration;
extern bool popping;
extern float popTimer;
extern int pumpkinPoints;
extern int lives;
extern bool gameOver;
extern bool gameStarted;
extern float difficultyTimer;
extern int popX;
extern int popY;
extern int popRadius;

struct Star {
    float x;
    float y;
    float speed;
    float size;
};
const int num_stars = 40;
extern Star stars[num_stars];
#endif