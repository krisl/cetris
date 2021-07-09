/* 
 * File:   Brick.cpp
 * Author: cecco
 * 
 * Created on 24 marzo 2015, 18.16
 */

#include <SDL2/SDL.h>

#include "Brick.h"

Brick::Brick() {
    for(int i=0; i<4; i++)
        bodyBricks[i] = NULL;
}


Brick::Brick(int x) {
    this->x = x-2;
    this->y = 0;
    this->id = 0;
    this->rotation =0;

    for(int i=0; i<4; i++)
        bodyBricks[i] = NULL;
}

Brick::~Brick() {
}

void Brick::init3dCubes() {
    for(int i=0; i<4; i++) {
        bodyBricks[i] = new Brick3dCube(id, 5,0);
    }
    
    setBodyCubesSpeed(ROTATE);
}

void Brick::delete3dCubes() {
    for(int i=0; i<4; i++) {
        if(bodyBricks[i] != NULL)
            delete bodyBricks[i];
    }
}


bool Brick::checkPos(int x, int y, Brick3dCube* field[FIELD_H][FIELD_W]) {

    for(int i=y; i<y+4; i++) {
        for(int j=x; j<x+4; j++) {
            if(i<0 || i>=FIELD_H || j<0 || j>=FIELD_W)
               if(this->getBodyValue(i-y,j-x) != 0)
                   return false;
            
            if(field[i][j] != NULL && this->getBodyValue(i-y,j-x) != 0)
                return false;
        }
    }
    return true;
}

void Brick::saveOnField(Brick3dCube* field[FIELD_H][FIELD_W]) {
    
    setBodyCubesSpeed(ROWFALL);
    
    int k=0;
    for(int i=y; i<y+4; i++) {
        for(int j=x; j<x+4; j++) {            
            if(this->getBodyValue(i-y,j-x) != 0) {
                field[i][j] = bodyBricks[k];
                bodyBricks[k] = NULL;
                field[i][j]->setXY(j,i);
                k++;
            }
        }
    }
}

void Brick::setBodyCubesSpeed(SPEEDS s) {
    float speed;
    
    switch (s) {
        case LATERAL:  speed = 10; break;
        case VERTICAL: speed = 10; break;
        case ROTATE:   speed = 20; break;
        case ROWFALL:  speed = 5;  break;
        default:       speed = 5;  break;
    }
   
    for(int i=0; i<4; i++) {
        bodyBricks[i]->setSpeed(speed);
    }
    
}


void Brick::rotate() {
    setBodyCubesSpeed(ROTATE);
    rotation = (rotation+1)% maxRotation;
}

void Brick::rotatedCheckPos(Brick3dCube* field[FIELD_H][FIELD_W]) {
    int r = rotation;
    rotation = (rotation+1)% maxRotation;
    
    if(checkPos(this->x, this->y, field)) {
        setBodyCubesSpeed(ROTATE);
        return;
    } else {
        rotation = r;
    }
}

void Brick::update(float dt) {
    
    int k=0;
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            if(getBodyValue(i,j)== 1) {
                bodyBricks[k++]->setXY(x+j, y+i);
            }
        }
    }
    
    for(int i=0; i<4; i++)
        bodyBricks[i]->updatePosition(dt);
}
