/* 
 * File:   Primitives.h
 * Author: cecco
 *
 * Created on 24 marzo 2015, 17.31
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

#ifndef PRIMITIVES_H
#define	PRIMITIVES_H

struct COLOR {
    GLfloat r,g,b,a;
};
    
void drawCube(float l);
void drawColoredCube(float l, COLOR col);
void drawColoredCharCube(float l, COLOR col, SDL_Color charcol, const char* text, TTF_Font *font);
void drawCharQuad(float l, SDL_Color charcol, const char* text, TTF_Font *font);
void drawText(float h, float w, SDL_Color charcol, const char* text, TTF_Font *font, float alpha);

#endif	/* PRIMITIVES_H */

