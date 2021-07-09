//
// Created by cecco on 22/05/15.
//

#ifndef SYSMUSIC_H
#define SYSMUSIC_H

#include <SDL2/SDL_mixer.h>
#include "SysTetris.h"
#include "BackgroundField.h"

class SysMusic {


public:
    SysMusic(BackgroundField *BField);
    virtual ~SysMusic();

    enum TYPE { BASS_INTRO, BATT_INTRO1, BATT_INTRO2,
                BASS1, BASS2, BASS3, BASS4,
                BATT1, BATT2,
                LEAD1, LEAD2, LEAD3, LEAD4
    };

    enum ROUTINE { MENU, PLAY, PAUSE, END, NONE};

    int playChannel(int channel, TYPE t, int loop);

    void setRoutine(ROUTINE r) { RoutineToSet=r; }
    int getRoutine() { return RoutineToSet; }
    void update(SysTetris *Tetris);



private:
    BackgroundField *BField;


    void menuRoutine();
    void playRoutine(SysTetris *Tetris);
    void pauseRoutine();
    void endRoutine();

    static const int nChunks =13;
    Mix_Chunk *Music[nChunks];

    int RoutineToSet;
    int ActualRoutine;

    int PlayStatus=0;


    const char MusicPaths[nChunks][256] = {
            "data/sound/bass_intro.wav",
            "data/sound/batt_intro1.wav",
            "data/sound/batt_intro2.wav",
            "data/sound/bass1.wav",
            "data/sound/bass2.wav",
            "data/sound/bass3.wav",
            "data/sound/bass4.wav",
            "data/sound/batt1.wav",
            "data/sound/batt2.wav",
            "data/sound/lead1.wav",
            "data/sound/lead2.wav",
            "data/sound/lead3.wav",
            "data/sound/lead4.wav",
    };

};


#endif //SYSMUSIC_H
