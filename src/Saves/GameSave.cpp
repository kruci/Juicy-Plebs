//R.K.
#include "GameSave.h"

GameSave::GameSave()
{
    //ctor
}

GameSave::~GameSave()
{
    if(gamesave != nullptr)
        al_destroy_config(gamesave);
}

bool GameSave::Create(std::string filename, std::string player_name)
{
    file_name = filename;
    gamesave = al_create_config();
    al_add_config_section(gamesave, "Player");
    al_set_config_value(gamesave, "Player", "Name", player_name.c_str());
    al_set_config_value(gamesave, "Player", "Mission", std::to_string(1).c_str());

    al_add_config_section(gamesave, "Items");
    std::cout << al_save_config_file(filename.c_str(), gamesave) << std::endl;

    return true;
}

bool GameSave::Load(std::string filename)
{
    file_name = filename;

    if(gamesave != nullptr)
        al_destroy_config(gamesave);

    gamesave = al_load_config_file(filename.c_str());

    if(gamesave == nullptr)
    {
        //Create(filename, "Whyyy?!");
        return false;
    }

    return true;
}

bool GameSave::Save()
{
    if(gamesave != nullptr)
        al_save_config_file(file_name.c_str(), gamesave);

    return true;
}

std::string GameSave::Get_player_name()
{
    std::string s;
    if(al_get_config_value(gamesave, "Player", "Name") == nullptr)
    {
        al_add_config_section(gamesave, "Player");
        al_set_config_value(gamesave, "Player", "Name", "Dont play with save files!");
        s = "Dont play with save files!";
    }
    s = al_get_config_value(gamesave, "Player", "Name");
    return s;
}

int GameSave::Get_mission_number()
{
    std::string s;
    if(al_get_config_value(gamesave, "Player", "Mission") == nullptr)
    {
        al_add_config_section(gamesave, "Player");
        s = std::to_string(1);
        al_set_config_value(gamesave, "Player", "Mission", s.c_str());
    }
    s = al_get_config_value(gamesave, "Player", "Mission");
    return stoi(s);
}

int GameSave::Set_mission_number(int nmb)
{
    al_add_config_section(gamesave, "Player");
    al_set_config_value(gamesave, "Player", "Mission", std::to_string(nmb).c_str());

    return nmb;
}
