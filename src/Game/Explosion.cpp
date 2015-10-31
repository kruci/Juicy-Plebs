#include "Explosion.h"

Explosion::Explosion(float centre_x, float centre_y) : c_x(centre_x), c_y(centre_y)
{
    bitmap = al_load_bitmap("resources/graphics/exp.png");
    if(bitmap == nullptr)
    {
        error_message("Could not load file : resources/graphics/exp.png");
    }
}

Explosion::~Explosion()
{
    if(bitmap != nullptr)
        al_destroy_bitmap(bitmap);
}

bool Explosion::Print()
{
    if(stage > max_stages)
    {
        active = false;
        return false;
    }

    al_draw_bitmap_region(bitmap,
    stage * x_change, 0, x_change, 100, c_x - x_change/2, c_y - 100/2, 0);
    stage++;

    return true;
}
