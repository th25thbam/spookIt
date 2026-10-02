#include "functions.h"
#include "globals.h"
#include "raylib.h"

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

void updateStars(){
    for(int i=0; i<num_stars; i++){
        stars[i].x-=stars[i].speed;
        if(stars[i].x < 0) stars[i].x=800;
    }
}

void drawStars(){
    for(int i=0; i<num_stars; i++){
            DrawCircle((int)stars[i].x, (int)stars[i].y, stars[i].size, (Color){200, 200, 220, 150});
    }
}