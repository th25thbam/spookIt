#include "raylib.h"
using namespace std;

int pumpkinX=400;
int pumpkinY=300;
int pumpkinRadius=40;
int score=0;
float pumpkinTimer=0.0f;
float pumpkinDuration=3.0f;
bool popping=false;
float popTimer=0.0f;
int pumpkinPoints=1;

void drawPumpkin(){
    float scale=1.0f;
    if(popping){
        scale=1.0f - popTimer/0.2f;
    }
    float currentRadius=pumpkinRadius*scale;
    DrawCircle(pumpkinX, pumpkinY, currentRadius, ORANGE);

    DrawCircle(pumpkinX-15 * scale, pumpkinY-10 * scale , 6 * scale, BLACK);
    DrawCircle(pumpkinX+15 * scale, pumpkinY-10 * scale, 6 * scale, BLACK);

    DrawRectangle(pumpkinX-18 * scale, pumpkinY+10 * scale, 36 * scale, 8 * scale, BLACK);
    DrawRectangle(pumpkinX-6 * scale, pumpkinY-pumpkinRadius * scale - 10 * scale, 12 * scale, 15 * scale, DARKGREEN);
}\

void spawnPumpkin(){
    pumpkinX=GetRandomValue(50,750);
    pumpkinY=GetRandomValue(50,550);
    pumpkinRadius=GetRandomValue(20,50);
    if(pumpkinRadius<=25){
        pumpkinPoints=3;
    }
    else if(pumpkinRadius<=40){
        pumpkinPoints=2;
    }
    else{
        pumpkinPoints=1;
    }

}

int main(){
    InitWindow(800,600, "spookIt");
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        Vector2 mouse = GetMousePosition();
        pumpkinTimer += GetFrameTime();

        if(pumpkinTimer >= pumpkinDuration){
            spawnPumpkin();
            pumpkinTimer=0.0f;
        }

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if(CheckCollisionPointCircle(mouse, {(float)pumpkinX, (float)pumpkinY}, pumpkinRadius)){
                score+=pumpkinPoints;
                // pumpkinX=GetRandomValue(50,600);
                // pumpkinY=GetRandomValue(50,600);
                // pumpkinTimer=0.0f;
                // if(pumpkinDuration > 0.5f){
                //     pumpkinDuration-=0.05f;
                // }
                popping=true;
                popTimer=0.0f;
            }
        }
        if(popping){
            popTimer+=GetFrameTime();
            if(popTimer>=0.2f){
                popping=false;
                spawnPumpkin();
                pumpkinTimer=0.0f;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        drawPumpkin();
        DrawText(TextFormat("Pumpkins SPOOKED: %d", score), 20, 30, 30, WHITE);
        DrawText(TextFormat("SPOOK Points: +%d", pumpkinPoints), 20, 70, 25, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}