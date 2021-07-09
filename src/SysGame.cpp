/* 
 * File:   Game.cpp
 * Author: cecco
 * 
 * Created on 24 marzo 2015, 17.57
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "SysGame.h"
#include "utils.h"

SysGame::SysGame() {
    BackField = new BackgroundField(10);
    Music = new SysMusic(BackField);
    Menu = new SysMenu(CubeL);
    Logo = new SysLogo();
}


SysGame::~SysGame() {

    TTF_CloseFont(Font);
    Font=NULL;

    delete BackField;
    delete Music;
    delete Menu;
    delete Logo;
}

bool SysGame::load() {

    if(Font == NULL)
        Font = TTF_OpenFont(data("data/FreeSans.ttf").c_str(), 100);

    if(Font == NULL) {
        printf("%s\n", TTF_GetError());
        return false;
    }
    Menu->setFont(Font);

    Tetris = new SysTetris(Font);
    Tetris->setL(CubeL);
    Tetris->setXYZField(0,-2,-60);
    Tetris->setXYZFieldRot(0,0,0);
    Tetris->updateLastFieldRot();

    return true;
}


void SysGame::update(float dt) {

    Music->update(Tetris);
    
    float delta = abs(RotMenuPlayAnim - RotMenuPlay);
    if (delta >2*dt*RotVel) {
        RotMenuPlayAnim<RotMenuPlay?
            RotMenuPlayAnim += RotVel*dt : RotMenuPlayAnim -= RotVel*dt;
    } else {
        RotMenuPlayAnim = RotMenuPlay;
    }
    
    if(Tetris->isGameOver() && !Tetris->isPaused()) {
        Menu->setStat(Menu->MENU);
        Music->setRoutine(Music->MENU);
        
        if(RotMenuPlayAnim == 0) {
            Tetris->switchPause();
            delete Tetris;
            load();
        }
    }
        
    BackField->update(dt);
    
    if(Menu->getStat() == Menu->PLAY) {
        if(Tetris->isPaused() && Tetris->isGameOver())
            Music->setRoutine(Music->END);
        else if (Tetris->isPaused())
            Music->setRoutine(Music->PAUSE);
        else
            Music->setRoutine(Music->PLAY);
        RotMenuPlay = 90;
        Tetris->update(dt);
    } else if(Menu->getStat() == Menu->MENU) {
        Music->setRoutine(Music->MENU);
        RotMenuPlay = 0;
        Menu->update(dt);
    } else if(Menu->getStat() == Menu->EXIT) {
        RotMenuPlay =-90;
        if(RotMenuPlayAnim == -90)
            quit = true;
    } else if(Menu->getStat() == Menu->LOGO) {
        RotMenuPlay =-90;
        if(Logo != NULL && !Logo->isEnd()) {
            Logo->update(dt);
        } else {
            Menu->setStat(Menu->MENU);
        }
    }

    if(Logo != NULL && RotMenuPlayAnim>=-20) {
        delete Logo;
        Logo = NULL;
    }

}

void SysGame::render() {
    glLoadIdentity();
    BackField->draw();
    
    glLoadIdentity();

    glRotatef(RotMenuPlayAnim,0,1,0);
    glPushMatrix();
    if(RotMenuPlayAnim <= 80)
        Menu->draw();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90,0,1,0);
    if(RotMenuPlayAnim >= 20)
        Tetris->draw();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,1,0);
    if(RotMenuPlayAnim<=-20 && Logo != NULL)
        Logo->draw();
    glPopMatrix();
}




void SysGame::keypressed(SDL_Event& ev) {
    if(Menu->getStat() == Menu->PLAY) {
        if(ev.key.keysym.sym == SDLK_ESCAPE) {
            Menu->setStat(Menu->MENU);
            if(Tetris->isGameOver())
                Tetris->switchPause();
        }
        
        Tetris->keypressed(ev);
    } else if(Menu->getStat() == Menu->MENU) {
        Menu->keypressed(ev);
    }
}

void SysGame::keyrelased(SDL_Event& ev) {
    if(Menu->getStat() == Menu->PLAY) {
        Tetris->keyrelased(ev);
    } if(Menu->getStat() == Menu->MENU) {
        Menu->keyrelased(ev);
    }
}
