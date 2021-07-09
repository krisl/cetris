/* 
 * File:   Event.h
 * Author: cecco
 *
 * Created on 29 marzo 2015, 16.09
 */

#ifndef KeyEVENT_H
#define	KeyEVENT_H

#include <SDL2/SDL.h>

class KeyEvent {
public:
    virtual void keypressed(SDL_Event &ev) = 0;
    virtual void keyrelased(SDL_Event &ev) = 0;
    
};


#endif	/* EVENT_H */

