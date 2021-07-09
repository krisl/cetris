/*
 * File:   BackgroundField.cpp
 * Author: cecco
 *
 * Created on 13 aprile 2015, 21.47
 */
#include <iostream>
#include <OpenGL/gl.h>
#include "BackgroundField.h"

BackgroundField::BackgroundField(int nCubes) {
    this->nCubes = nCubes;

    Cubelist = new Brick* [nCubes];

    srand(time(0));
    
    for(int i=0; i<nCubes; i++) {
        Cubelist[i] = SysTetris::newBrick();
        Cubelist[i]->setH(float(rand()%1000)*l*3/1000);
        Cubelist[i]->setAngle(360/nCubes*i);
    }
}



BackgroundField::~BackgroundField() {
    
    for(int i=0; i<nCubes; i++) {
        if(Cubelist[i] != NULL)
            delete Cubelist[i];
    }    
    delete [] Cubelist;
}

void BackgroundField::update(float dt) {

    for(int i=0; i<nCubes; i++) {
        float a = Cubelist[i]->getAngle();
        Cubelist[i]->setAngle(a += vel*dt);
    }
    
}


void BackgroundField::draw() {


    glPushMatrix();
    
    for(int i=0; i<nCubes; i++) {
        glPopMatrix();
        glPushMatrix();
        
        glRotatef(Cubelist[i]->getAngle(), 0, 1,0);
        glTranslatef(0, Cubelist[i]->getH(), -100); //posizione
        glTranslatef(2*l*2, -2*l, 0.0f);          //accentra
        glRotatef(Cubelist[i]->getAngle(), 1, 1, 1);    //ruota
        glTranslatef(-2*l*2, +2*l, 0.0f);         //decentra

        if(Cubelist[i] != NULL) {
            for(int k=0; k<4; k++) {
                for(int j=0; j<4; j++) {
                    if(Cubelist[i]->getBodyValue(k,j) != 0) {
                        //glDisable(GL_BLEND);
                        drawColoredCube(l, {0,0,0.1, alpha});
                        //glEnable(GL_BLEND);
                        //drawColoredCube(l, {0,0,0.1, 0.2});
                    }
                    glTranslatef(2*l, 0.0f, 0.0f);
                }
                glTranslatef(-(2*l*4), -(2*l), 0.0f);
            }
        }
        
    }
    
    glPopMatrix();
}
