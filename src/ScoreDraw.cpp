/* 
 * File:   ScoreDraw.cpp
 * Author: cecco
 * 
 * Created on 12 aprile 2015, 15.13
 */

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "ScoreDraw.h"
#include "SysTetris.h"

inline std::string to_string(int number);

ScoreDraw::ScoreDraw(TTF_Font *Font, float l) {
    this->Font = Font;

    this->l = l;
    //position relative to the center of field
    
    setPlayPosition();
    
    Xreal = Xpos;
    Yreal = Ypos;
    Zreal = Zpos;
    XrealRot = Xrot;
    
    scorel = l;
}

ScoreDraw::~ScoreDraw() {
}

void ScoreDraw::update(int score, float dt) {
    realScore= score;
    
    for(int i=0; i<5; i++) {
        if(toRotate[i])
           RotateAngle += 180*dt; 
        
        if(RotateAngle >= 90) {
            for(int j=0; j<5; j++)
                toRotate[j]=false;
            RotateAngle =0;
            displayScore = realScore;
        }
    }
     
    moveToPos(dt);
}

void ScoreDraw::moveToPos(float dt) {
    float delta;
    float dx = fabs(Xreal - Xpos);
    float dy = fabs(Yreal - Ypos);
    float dz = fabs(Zreal - Zpos);
    

    delta = dx*speed*dt;
    if(dx > delta)
        Xreal > Xpos ? Xreal -= dx*speed*dt : Xreal += dx*speed*dt;
    else
        Xreal = Xpos;

    delta = dy*speed*dt;
    if(dy > delta)
        Yreal > Ypos ? Yreal -= dy*speed*dt : Yreal += dy*speed*dt;
    else
        Yreal = Ypos;

    delta = dz*speed*dt;
    if(dz > delta)
        Zreal > Zpos ? Zreal -= dz*speed*dt : Zreal += dz*speed*dt;
    else
        Zreal = Zpos;


    float dxr = fabs(XrealRot - Xrot);

    delta = dxr*speed*dt;
    if(dxr > delta)
        XrealRot > Xrot ? XrealRot -= dxr*speed*dt : XrealRot += dxr*speed*dt;
    else
        XrealRot = Xrot;
}


void ScoreDraw::draw() {
    glTranslatef(Xreal, Yreal, Zreal);
    glRotatef(XrealRot,1,0,0);
    
    drawColoredCharCube(scorel, {0,0,1.0,0.2}, {0,255,255,0}, "S", Font);
    glTranslatef(2*scorel, 0, 0);
    drawColoredCharCube(scorel, {0,0,1.0,0.2}, {0,255,255,0}, "c", Font);
    glTranslatef(2*scorel, 0, 0);
    drawColoredCharCube(scorel, {0,0,1.0,0.2}, {0,255,255,0}, "o", Font);
    glTranslatef(2*scorel, 0, 0);
    drawColoredCharCube(scorel, {0,0,1.0,0.2}, {0,255,255,0}, "r", Font);
    glTranslatef(2*scorel, 0, 0);
    drawColoredCharCube(scorel, {0,0,1.0,0.2}, {0,255,255,0}, "e", Font);
    glTranslatef(2*scorel, 0, 0);
    drawColoredCube(scorel, {0,0,1.0,0.2});

    std::string realS = to_string(realScore);
    std::string S = to_string(displayScore);
    
    for(int i=4; i>=0; i--) {
        char Sc[] = "0";
        
        if(S.size() >i)
            Sc[0] = S[S.size()-1- i];
        
        char realSc[] = "0";
        
        if(realS.size() >i)
            realSc[0] = realS[realS.size()-1- i];
        
        glTranslatef(2*scorel, 0, 0);
        
        glPushMatrix();
        if(toRotate[i])
            glRotatef(RotateAngle, 1,0,0);
        drawColoredCharCube(scorel, {0,0,1.0,0.2}, {0,255,255,0}, Sc, Font);
        
        
        if(realSc[0] != Sc[0]) {
            glRotatef(-90, 1,0,0);
            drawColoredCharCube(scorel, {0,0,1.0,0.2}, {0,255,255,0}, realSc, Font);
            glRotatef(90, 1,0,0);
            toRotate[i] = true;
        }
        glPopMatrix();
    }
    
}

void ScoreDraw::setPausePosition() {
    Zpos = Zpos + l*20;
    Ypos = -l*(FIELD_H/2);
    Xrot = 11120;
}

void ScoreDraw::setPlayPosition() {
    Xpos = -l*(FIELD_W);
    Ypos = l*(FIELD_H)+ l*4;
    Zpos = 0;
    Xrot = 15;
}


inline std::string to_string(int number){
    std::string number_string = "";
    char ones_char;
    int ones = 0;
    while(true){
        ones = number % 10;
        switch(ones){
            case 0: ones_char = '0'; break;
            case 1: ones_char = '1'; break;
            case 2: ones_char = '2'; break;
            case 3: ones_char = '3'; break;
            case 4: ones_char = '4'; break;
            case 5: ones_char = '5'; break;
            case 6: ones_char = '6'; break;
            case 7: ones_char = '7'; break;
            case 8: ones_char = '8'; break;
            case 9: ones_char = '9'; break;
            default : printf("Trouble converting number to string.\n");
        }
        number -= ones;
        number_string = ones_char + number_string;
        if(number == 0){
            break;
        }
        number = number/10;
    }
    return number_string;
}
