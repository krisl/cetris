/* 
 * File:   SystemGL.h
 * Author: cecco
 *
 * Created on 23 marzo 2015, 22.14
 */

#ifndef SYSTEMGL_H
#define	SYSTEMGL_H


#include "Primitives.h"
#include "SysGame.h"

class SystemSDL {
public:
    SystemSDL(int height, int width, int bpp);
    virtual ~SystemSDL();
    
    bool init();
    
    void loop();
       
    void eventUpdate();

    
private:
    int height;
    int width;
    int bpp;
    
    bool quitLoop;
    SDL_Event event;
    float dt;
    
    SysGame *Game;
    


};

#endif	/* SYSTEMGL_H */