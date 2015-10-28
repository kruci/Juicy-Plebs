#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "global.h"
class ScreenGame;
#include "ScreenGame.h"

struct universal_data{
    int vectro_poz;
    int which_vector;
};

class CollisionHandler : public b2ContactListener
{
    public:
    ScreenGame *refscreen;

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

};
#endif // COLLISIONHANDLER_H
