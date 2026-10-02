#include "raylib.h"

int pumpkinX=400;
int pumpkinY=300;
int pumpkinRadius=40;
int score=0;
float pumpkinTimer=0.0f;
float pumpkinDuration=2.0f;
bool popping=false;
float popTimer=0.0f;
int pumpkinPoints=1;
int lives=5;
bool gameOver=false;
bool gameStarted=false;
float difficultyTimer=0.0f;
int popX=0.0;
int popY=0.0;
int popRadius=0;


void drawPumpkin(){
    if(popping){
        float scale=1.0f - popTimer/0.15f;
        if(scale<0) scale=0;
        float currentRadius=popRadius*scale;
        DrawCircle(popX, popY, currentRadius, ORANGE);
        DrawCircle(popX - (int)(15*scale), popY - (int)(10*scale), (int)(6*scale), BLACK);
        DrawCircle(popX + (int)(15*scale), popY - (int)(10*scale), (int)(6*scale), BLACK);
        DrawRectangle(popX - (int)(18*scale), popY + (int)(10*scale), (int)(36*scale), (int)(8*scale), BLACK);
    }
    
    else{
        DrawCircle(pumpkinX, pumpkinY, pumpkinRadius, ORANGE);

        DrawCircle(pumpkinX-15, pumpkinY-10, 6, BLACK);
        DrawCircle(pumpkinX+15, pumpkinY-10, 6, BLACK);

        DrawRectangle(pumpkinX-18, pumpkinY+10, 36, 8, BLACK);
        DrawRectangle(pumpkinX-6, pumpkinY-pumpkinRadius-10, 12, 15, DARKGREEN);
    }
}

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
        if(!gameStarted){
            if(IsKeyPressed(KEY_SPACE)){
                gameStarted=true;
                spawnPumpkin();
            }
        }
        else if(!gameOver){
            Vector2 mouse = GetMousePosition();
            pumpkinTimer += GetFrameTime();

            if(pumpkinTimer >= pumpkinDuration){
                lives--;
                if(lives<=0){
                    gameOver=true;
                }
                else{
                    spawnPumpkin();
                    pumpkinTimer=0.0f;
                }
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(CheckCollisionPointCircle(mouse, {(float)pumpkinX, (float)pumpkinY}, pumpkinRadius)){
                    score+=pumpkinPoints;
                    popX=pumpkinX;
                    popY=pumpkinY;
                    popRadius=pumpkinRadius;
                    popping=true;
                    popTimer=0.0f;
                    spawnPumpkin();
                    pumpkinTimer=0.0f;
                }
            }

            if(popping){
                popTimer+=GetFrameTime();
                if(popTimer>=0.15f){
                    popping=false;
                }
            }
            
            difficultyTimer+=GetFrameTime();
            if(difficultyTimer>=4.0f){
                if(pumpkinDuration>0.3f){
                    pumpkinDuration-=0.15f;
                }
                difficultyTimer=0.0f;
            }
        }
        if(gameOver && IsKeyPressed(KEY_R)){
            score=0;
            lives=5;
            pumpkinDuration=2.5f;
            pumpkinTimer=0.0f;
            popping=false;
            popTimer=0.0f;
            gameOver=false;
            spawnPumpkin();
        }

        BeginDrawing();
        ClearBackground((Color){15, 10, 25, 25});

        DrawCircle(700, 100, 50, (Color){220, 220, 200, 255});
        DrawCircle(680, 85, 8, (Color){170, 170, 160, 255});
        DrawCircle(715, 110, 6, (Color){170, 170, 160, 255});
        DrawCircle(705, 75, 5, (Color){170, 170, 160, 255});

        DrawRectangle(0, 550, 800, 50, (Color){10, 8, 15, 255});

        for(int i=0; i<800; i+=20){
            DrawLine(i, 550, i+5, 535, DARKGREEN);
        }

        if(!gameStarted){
            DrawText("PUMPKIN POP", 260, 220, 50, ORANGE);
            DrawText("Press SPACE to start!!", 275, 300, 25, WHITE);
        }
        else{
            drawPumpkin();

            DrawText(TextFormat("Pumpkins SPOOKED: %d", score), 20, 30, 30, WHITE);
            DrawText(TextFormat("SPOOK Points: +%d", pumpkinPoints), 20, 70, 25, WHITE);
            DrawText(TextFormat("Lives Remaining: %d", lives), 20, 100, 25, WHITE);

            if(gameOver){
                DrawText("GAME SPOOKED", 280, 250, 50, RED);
                DrawText(TextFormat("Final Score: %d", score), 300, 320, 25, WHITE);
                DrawText("Press R to Restart spookIt", 290, 370, 20, GRAY);
            }
        } 
        EndDrawing();
    }
    CloseWindow();
    return 0;
}