/* 
 * File:   Primitives.cpp
 * Author: cecco
 * 
 * Created on 24 marzo 2015, 17.31
 */
#include <SDL2/SDL_ttf.h>

#include "Primitives.h"


void drawColoredCube(float l, COLOR col) {
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.5);
    
    glColor4f(col.r, col.g, col.b, col.a);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
     
    glPolygonMode(GL_BACK, GL_FILL);
    drawCube(l);
    
    glColorMaterial(GL_FRONT, GL_EMISSION);
    glColor4f(0, 0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawCube(l);
    
    //reset changes
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawCharQuad(float l, SDL_Color charcol, const char* text, TTF_Font *font) {

    if(font ==NULL) {
        printf("Primitive draw error: font not setted\n");
        return;
    }

    glEnable(GL_TEXTURE_2D);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
    glPolygonMode(GL_FRONT, GL_FILL);
    
    glPolygonMode(GL_BACK, GL_LINE); //try

    
    GLuint charText;

    glGenTextures(1, &charText);
    glBindTexture(GL_TEXTURE_2D, charText);

    SDL_Surface * sFont = TTF_RenderText_Blended(font, text, charcol);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

    SDL_FreeSurface(sFont);

    
    glColor3f(1.0f,1.0f,1.0f); //white
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-l, -l,  l);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( l, -l,  l);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( l,  l,  l);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-l,  l,  l); 
    
    glEnd();
    
    glDeleteTextures(1, &charText);
    glDisable(GL_TEXTURE_2D);
}


void drawColoredCharCube(float l, COLOR col, SDL_Color charcol, const char* text, TTF_Font *font) {
    drawColoredCube(l, col);

    if(font ==NULL) {
        printf("Primitive draw error: font not setted\n");
        return;
    }
    drawCharQuad(l, charcol, text, font);
}


void drawCube(float l) {
	 
 
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	  // Top face (y = 1.0f)
	  // Define vertices in counter-clockwise (CCW) order with normal pointing out
	     
          
	  glVertex3f( l, l, -l);
	  glVertex3f(-l, l, -l);
	  glVertex3f(-l, l,  l);
	  glVertex3f( l, l,  l);
 
	  // Bottom face (y = -1.0f)
	  glVertex3f( l, -l,  l);
	  glVertex3f(-l, -l,  l);
	  glVertex3f(-l, -l, -l);
	  glVertex3f( l, -l, -l);
 
	  // Front face  (z = 1.0f)
	  glVertex3f( l,  l, l);
	  glVertex3f(-l,  l, l);
	  glVertex3f(-l, -l, l);
	  glVertex3f( l, -l, l);
 
	  // Back face (z = -1.0f)
	  glVertex3f( l, -l, -l);
	  glVertex3f(-l, -l, -l);
	  glVertex3f(-l,  l, -l);
	  glVertex3f( l,  l, -l);
 
	  // Left face (x = -1.0f)
	  glVertex3f(-l,  l,  l);
	  glVertex3f(-l,  l, -l);
	  glVertex3f(-l, -l, -l);
	  glVertex3f(-l, -l,  l);
 
	  // Right face (x = 1.0f)
	  glVertex3f(l,  l, -l);
	  glVertex3f(l,  l,  l);
	  glVertex3f(l, -l,  l);
	  glVertex3f(l, -l, -l);
	glEnd();  // End of drawing color-cube

}


void drawText(float h, float w, SDL_Color charcol, const char* text, TTF_Font *font, float alpha) {

    if(font ==NULL) {
        printf("Primitive draw error: font not setted\n");
        return;
    }

    glEnable(GL_TEXTURE_2D);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glPolygonMode(GL_FRONT, GL_FILL);

    glPolygonMode(GL_BACK, GL_LINE); //try


    GLuint charText;

    glGenTextures(1, &charText);
    glBindTexture(GL_TEXTURE_2D, charText);

    SDL_Surface * sFont = TTF_RenderText_Blended(font, text, charcol);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sFont->pixels);

    w=  ( float(sFont->w) / float(sFont->h) )*w;
    SDL_FreeSurface(sFont);



    glColor4f(1.0f,1.0f,1.0f,alpha); //white
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0,  0,  0);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( w,  0,  0);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( w,  h,  0);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0,  h,  0);

    glEnd();

    glDeleteTextures(1, &charText);
    glDisable(GL_TEXTURE_2D);
}
