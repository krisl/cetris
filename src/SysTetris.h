/* 
 * File:   Tetris.h
 * Author: cecco
 *
 * Created on 24 marzo 2015, 17.36
 */

#define FIELD_H 20
#define FIELD_W 10

#ifndef SYSTETRIS_H
#define	SYSTETRIS_H


#include <SDL2/SDL.h>
#include <list>
#include <time.h>

#include "KeyEvent.h"
#include "Brick3dCube.h"
#include "SysTetris/Eliminated3dCube.h"
#include "ScoreDraw.h"
#include "Primitives.h"

#include "SysTetris/Brick.h"


class Brick;

class SysTetris : KeyEvent {
public:
    SysTetris(TTF_Font *Font);
    virtual ~SysTetris();
    
    void update(float dt);
    void draw();
    void switchPause() { 
        pause = !pause; pause? 
        drawScore->setPausePosition(): drawScore->setPlayPosition();
    }
    bool isPaused() { return pause; }
    bool isGameOver() { return gameOver; }
    
    void drawFieldLimits();
    void updateBackColor(float dt);
    
    void setXYZField(float x, float y, float z) { XField=x; YField=y; ZField=z;}
    void setXYZFieldRot(float x, float y, float z)
        { XFieldRot=x; YFieldRot=y; ZFieldRot=z; }
    void updateLastFieldRot()
        { lastXFieldRot= XFieldRot;
          lastYFieldRot= YFieldRot;
          lastZFieldRot= ZFieldRot; }
    
    void setCubel (float l) { this->l = l; }
    
    Brick3dCube* getField(int r, int c);
 
    static Brick* newBrick();
    void createBrick();
    
    COLOR colorFromId(int id);

    void moveLeft(bool s)  { Left  = s; MinTimeMove=0; }
    void moveRight(bool s) { Right = s; MinTimeMove=0; }
    void fallBrick();
    void rotateBrick();
    
    void addFallSpeed(bool s);
    
    float getL() { return l; }
    void setL(float l) { this->l = l; }
    
    void removeLines();
    

    virtual void keypressed(SDL_Event& ev);
    virtual void keyrelased(SDL_Event& ev);


    int getScore() const { return score;}
    int getFieldCount();

private:
    void checkFullLines();
    void removeLine(int n);
    bool copyLine(int s, int d);
    
    Brick3dCube* field[FIELD_H][FIELD_W];
    std::list <Eliminated3dCube*> freeBrick3dCube;
    
    //bool for control movement
    bool Left=false, Right=false;
    bool pause=false;
    bool gameOver=false;

    int score=0;
    ScoreDraw *drawScore;
    
    //control move animation
    float MinTimeMove =0;
    const float MoveSpeed = 80;
    
    //3d position of the field
    float XField=0, YField=0, ZField=0;
    float XFieldRot=0, YFieldRot=0, ZFieldRot=0;
    float lastXFieldRot=0, lastYFieldRot=0, lastZFieldRot=0;
    
    //lenght of half a cube
    float l = 1;
    
    //control fall animation
    float FallTime = 0;
    const float FallSpeed = 10;
    float AdditionFallSpeed = 0;
    float MaxFallSpeed = 100;
    
    Brick *currentBrick = NULL;
    Brick *nextBrick = NULL;
    
    //control animation of next brick
    float nextBrickRotation=0;

    COLOR backColor;
    
    bool toRemove[FIELD_H];
};

#endif	/* TETRIS_H */

