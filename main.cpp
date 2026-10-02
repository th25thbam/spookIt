#include "raylib.h"
#include "functions.h"
#include "globals.h"
int main(){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800,600, "spookIt");
    SetTargetFPS(60);
    initStars();
    RenderTexture2D target = LoadRenderTexture(800, 600);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
    while(!WindowShouldClose()){
        updateStars();

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

        drawStars();

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
                DrawText("Press Escape to exit", 240, 380, 18, GRAY);
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