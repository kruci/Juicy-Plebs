//R.K.
#ifndef MAPDATA_H
#define MAPDATA_H

#include "global.h"

class MapData
{
private:
    ALLEGRO_CONFIG *cfg = nullptr;

    struct rectangle{
        float x1, y1, x2, y2;
        int type;
        int item;
        int enemy;
        float hp, shield, speed;
    };

public:
    enum {WALL = 0, PLAYER_SPAWN, ENEMY_SPAWN, ITEM_SPAWN};
    float player_spawm_x, player_spawm_y;

    std::vector<rectangle *> objects;

    MapData(std::string map_conf_file);
    virtual ~MapData();

};

#endif // MAPDATA_H
