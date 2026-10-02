#include "raylib.h"

int pumpkins=0;
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

struct Star{
    float x;
    float y;
    float speed;
    float size;
};

const int num_stars=40;
Star stars[num_stars];

void initStars(){
    for(int i=0; i < num_stars; i++ ){
        stars[i].x=(float)GetRandomValue(0,800);
        stars[i].y=(float)GetRandomValue(0,800);
        stars[i].speed=(float)GetRandomValue(1,3)*0.2f;
        stars[i].size=(float)GetRandomValue(1,3);
    }
}

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
    pumpkinRadius=GetRandomValue(15,30);
    if(pumpkinRadius<=20){
        pumpkinPoints=3;
    }
    else if(pumpkinRadius<=35){
        pumpkinPoints=2;
    }
    else{
        pumpkinPoints=1;
    }

}

int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800,600, "spookIt");
    SetTargetFPS(60);
    initStars();
    RenderTexture2D target = LoadRenderTexture(800, 600);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
    while(!WindowShouldClose()){

        for(int i=0; i<num_stars; i++){
            stars[i].x-=stars[i].speed;
            if(stars[i].x < 0) stars[i].x=800;
        }

        Vector2 realMouse = GetMousePosition();
        Vector2 mouse = {
            realMouse.x * (800.0f / (float)GetScreenWidth()),
            realMouse.y * (600.0f / (float)GetScreenHeight())
        };

        if(!gameStarted){
            if(IsKeyPressed(KEY_SPACE)){
                gameStarted=true;
                spawnPumpkin();
            }
        }
        else if(!gameOver){
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
                    pumpkins++;
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
        BeginTextureMode(target);
        ClearBackground((Color){15, 10, 25, 25});

        for(int i=0; i<num_stars; i++){
            DrawCircle((int)stars[i].x, (int)stars[i].y, stars[i].size, (Color){200, 200, 220, 150});
        }

        DrawCircle(700, 100, 50, (Color){220, 220, 200, 255});
        DrawCircle(680, 85, 8, (Color){170, 170, 160, 255});
        DrawCircle(715, 110, 6, (Color){170, 170, 160, 255});
        DrawCircle(705, 75, 5, (Color){170, 170, 160, 255});

        DrawRectangle(0, 550, 800, 50, (Color){10, 8, 15, 255});

        for(int i=0; i<800; i+=20){
            DrawLine(i, 550, i+5, 535, DARKGREEN);
        }

        if(!gameStarted){
            DrawText("SpookIt - PUMPKIN POP", 130, 140, 45, ORANGE);
            DrawRectangle(180, 205, 440, 170, (Color){25, 20, 35, 230});
            DrawRectangleLines(180, 205, 440, 170, (Color){100, 70, 120, 255});
            DrawText("How to play:", 335, 220, 18, (Color){200, 180, 220, 255});
            DrawText("- Click spooky pumpkins before they spook themself!", 205, 255, 15, WHITE);
            DrawText("- Smaller pumpkins = more points(upto 3 points)!", 205, 285, 15, WHITE);
            DrawText("- Missing a pumpkin spooks 1 life(total 5 lives)!", 205, 315, 15, WHITE);

            DrawText("Press SPACE to start!!", 265, 410, 20, (Color){167, 243, 208, 255});
        }
        else{
            if(!gameOver) {
                drawPumpkin();
            }

            DrawText(TextFormat("Total SPOOK Points: %d", score), 20, 30, 25, WHITE);
            DrawText(TextFormat("SPOOK Points: +%d", pumpkinPoints), 20, 65, 20, WHITE);
            DrawText(TextFormat("Lives Remaining: %d", lives), 20, 95, 20, WHITE);

            if(gameOver){
                DrawText("GAME SPOOKED", 240, 210, 45, RED);
                DrawText(TextFormat("Final Score: %d", score), 240, 280, 22, WHITE);
                DrawText(TextFormat("Total Pumpkins Spooked: %d", pumpkins), 240, 310, 22, WHITE);
                DrawText("Press R to Restart spookIt", 240, 350, 18, GRAY);
            }
        }
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            target.texture, 
            (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height }, 
            (Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() }, 
            (Vector2){ 0.0f, 0.0f }, 
            0.0f, 
            WHITE
        );

        EndDrawing();
        
    }
    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}