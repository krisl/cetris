/* 
 * File:   Game.h
 * Author: cecco
 *
 * Created on 24 marzo 2015, 17.57
 */


#ifndef GAME_H
#define	GAME_H

#include <SDL2/SDL_mixer.h>
#include "SysTetris.h"
#include "Primitives.h"
#include "KeyEvent.h"
#include "BackgroundField.h"
#include "SysMenu.h"
#include "SysLogo.h"
#include "SysMusic.h"

class SysGame : KeyEvent {
public:
    SysGame();
    virtual ~SysGame();
    
    bool load();
    void update(float dt);
    void render();
    

    virtual void keypressed(SDL_Event& ev);
    virtual void keyrelased(SDL_Event& ev);

    bool toQuit() { return quit;}

private:
    SysLogo *Logo;
    SysMenu *Menu;
    SysTetris *Tetris;
    BackgroundField *BackField;

    SysMusic *Music;

    TTF_Font *Font = NULL;

    float CubeL = 1;


    float RotMenuPlayAnim = -90;
    float RotMenuPlay = -90;
    float RotVel= 180;

    float quit=false;

};

#endif	/* GAME_H */

