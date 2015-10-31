#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "global.h"

class Explosion
{
private:
    ALLEGRO_BITMAP *bitmap = nullptr;

    int stage = 0;
    int max_stages = 16;
    float c_x, c_y, s_w, s_h;
public:
    bool active = true;
    int x_change = 71;

    Explosion(float centre_x, float centre_y);
    virtual ~Explosion();
    bool Print();
};

#endif // EXPLOSION_H
