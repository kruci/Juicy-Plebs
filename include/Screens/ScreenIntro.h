#ifndef SCREENINTRO_H
#define SCREENINTRO_H

#include "global.h"

class ScreenIntro
{
private:
    bool *it_is;
public:
    ScreenIntro(bool *is_intro_running);
    virtual ~ScreenIntro();

    void Print();
};

#endif // SCREENINTRO_H
