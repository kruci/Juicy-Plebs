//R.K.
#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "global.h"

class GameSave
{
    private:
        ALLEGRO_CONFIG *gamesave = nullptr;
    public:
        std::string file_name;

        GameSave();
        virtual ~GameSave();

        bool Create(std::string filename, std::string player_name);
        bool Load(std::string filename);
        bool Save();

        std::string Get_player_name();

        int Get_mission_number();
        int Set_mission_number(int nmb);

};

#endif // GAMESAVE_H
