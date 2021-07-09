/* 
 * File:   ScoreDraw.h
 * Author: cecco
 *
 * Created on 12 aprile 2015, 15.13
 */

#ifndef SCOREDRAW_H
#define	SCOREDRAW_H

#include <string>
#include <SDL2/SDL_ttf.h>

class ScoreDraw {
public:
    ScoreDraw(TTF_Font *Font, float l);
    virtual ~ScoreDraw();
    
    void update(int score, float dt);
    void draw();
    
    void moveToPos(float dt);
    void setPausePosition();
    void setPlayPosition();

    void setFont(TTF_Font *Font) { this->Font =Font;}

private:
    TTF_Font *Font=NULL;

    int displayScore=0;
    int realScore=0;
    
    float Xpos, Ypos, Zpos;
    float Xreal, Yreal, Zreal;
    float Xrot, XrealRot;
    float speed= 10;
    float l;
    float scorel;
    
    bool toRotate[5] = {false, false, false, false,false};
    float RotateAngle=0;
};

#endif	/* SCOREDRAW_H */

