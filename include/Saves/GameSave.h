//R.K.
#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "global.h"

#define SAVE_PATH "saves/"

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

        bool Get_item(int nmb);
        bool Set_item(int nmb);

        /**if cd or ct == -1 then it is not set*/
        float Get_ab_cd(int ab_numeber);
        bool Set_ab_cd(int ab_numeber, float cd);

        float Get_ab_cast_t(int ab_numeber);
        bool Set_ab_cast_t(int ab_numeber, float ct);

        float Set_final_boss_HP_scale(float scale);
        float Get_final_boss_HP_scale();
};

#endif // GAMESAVE_H
