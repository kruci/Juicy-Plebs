//R.K.
#include "MapData.h"

MapData::MapData(std::string map_conf_file)
{
    cfg = al_load_config_file(map_conf_file.c_str());

    if(cfg == nullptr)
    {
        error_message("Could not load file: " + map_conf_file);
    }

     //can be optimized...
    std::string dum, dum2;
    if(al_get_config_value(cfg, "Map", "map_objects") == nullptr)
    {
        error_message("Invalid file: " + map_conf_file);
    }

    dum = al_get_config_value(cfg, "Map", "map_objects");

    long mpobjcts = stol(dum);

    for(int a = 1;a <= mpobjcts;a++ )
    {
        dum = "Object_" + std::to_string(a);

        if(al_get_config_value(cfg, dum.c_str(), "type") == nullptr)
        {
            error_message("Invalid file: " + map_conf_file);
            break;
        }
        dum2 = al_get_config_value(cfg, dum.c_str(), "type");

        if(dum2 == "wall")
        {
            objects.push_back(new rectangle);
            objects[objects.size()-1]->type = WALL;
        }
        else
        {
            objects.push_back(new rectangle);
            if(dum2 == "p_spawn")
            {
                objects[objects.size()-1]->type = PLAYER_SPAWN;
            }
            else if(dum2 == "e_spawn")
            {
                objects[objects.size()-1]->type = ENEMY_SPAWN;
                if(al_get_config_value(cfg, dum.c_str(), "enemy") == nullptr)
                {
                    error_message("Invalid file: " + map_conf_file);
                    break;
                }
                dum2 = al_get_config_value(cfg, dum.c_str(), "enemy");
                objects[objects.size()-1]->enemy = stoi(dum2);

                if(al_get_config_value(cfg, dum.c_str(), "hp") == nullptr)
                {
                    objects[objects.size()-1]->hp = 3.0f;
                }
                else
                {
                    objects[objects.size()-1]->hp = std::stof(al_get_config_value(cfg, dum.c_str(), "hp"));
                }

                if(al_get_config_value(cfg, dum.c_str(), "shield") == nullptr)
                {
                    objects[objects.size()-1]->shield = 3.0f;
                }
                else
                {
                    objects[objects.size()-1]->shield = std::stof(al_get_config_value(cfg, dum.c_str(), "shield"));
                }

                if(al_get_config_value(cfg, dum.c_str(), "speed") == nullptr)
                {
                    objects[objects.size()-1]->speed = 5.0f;
                }
                else
                {
                    objects[objects.size()-1]->speed = std::stof(al_get_config_value(cfg, dum.c_str(), "speed"));
                }
            }
            else if(dum2 == "i_spawn")
            {
                objects[objects.size()-1]->type = ITEM_SPAWN;
                if(al_get_config_value(cfg, dum.c_str(), "item") == nullptr)
                {
                    error_message("Invalid file: " + map_conf_file);
                    break;
                }
                dum2 = al_get_config_value(cfg, dum.c_str(), "item");
                objects[objects.size()-1]->item = stoi(dum2);
            }
        }

        if(al_get_config_value(cfg, dum.c_str(), "x1") == nullptr || al_get_config_value(cfg, dum.c_str(), "y1") == nullptr ||
           al_get_config_value(cfg, dum.c_str(), "x2") == nullptr || al_get_config_value(cfg, dum.c_str(), "y2") == nullptr)
        {
            error_message("Invalid file: " + map_conf_file);
            break;
        }

        objects[objects.size()-1]->x1 = std::stof(al_get_config_value(cfg, dum.c_str(), "x1"));
        objects[objects.size()-1]->y1 = std::stof(al_get_config_value(cfg, dum.c_str(), "y1"));
        objects[objects.size()-1]->x2 = std::stof(al_get_config_value(cfg, dum.c_str(), "x2"));
        objects[objects.size()-1]->y2 = std::stof(al_get_config_value(cfg, dum.c_str(), "y2"));

        if(objects[objects.size()-1]->type == PLAYER_SPAWN)
        {
            player_spawm_x = objects[objects.size()-1]->x1;
            player_spawm_y = objects[objects.size()-1]->y1;
        }
    }
}

MapData::~MapData()
{
    for(int a = 0;a < (int)objects.size();a++)
    {
        delete objects[a];
    }
    objects.clear();

    if(cfg != nullptr)
        al_destroy_config(cfg);
}
