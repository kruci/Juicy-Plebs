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

class RayCastCallBack : public b2RayCastCallback
{
    public:
    b2Vec2 neocconepouzijem1, neocconepouzijem2;

    ScreenGame *refscreen;

    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
};
#endif // COLLISIONHANDLER_H
