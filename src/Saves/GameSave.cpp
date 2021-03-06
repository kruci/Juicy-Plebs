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
    /**check if save dir is still here*/
    ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(SAVE_PATH);

    if(al_open_directory(dir) == false)
    {
        al_make_directory(SAVE_PATH);
    }
    al_destroy_fs_entry(dir);
    //---------------------------------

    file_name = filename;
    gamesave = al_create_config();
    al_add_config_section(gamesave, "Player");
    al_set_config_value(gamesave, "Player", "Name", player_name.c_str());
    al_set_config_value(gamesave, "Player", "Mission", std::to_string(1).c_str());

    al_add_config_section(gamesave, "Items");
    Set_global_HP_scale(1);
    Set_global_speed_scale(1);
    Set_final_boss_HP_scale(1);
    al_save_config_file(filename.c_str(), gamesave);

    return true;
}

bool GameSave::Load(std::string filename)
{
    file_name = filename;

    if(gamesave != nullptr)
    {
        al_destroy_config(gamesave);
        gamesave = nullptr;
    }

    if( (gamesave = al_load_config_file(filename.c_str())) == nullptr)
    {
        return false;
    }

    //std::cout << al_get_config_value(gamesave, "Player", "Name") << std::endl;

    return true;
}

bool GameSave::Save()
{
    /**check if save dir is still here*/
    ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(SAVE_PATH);

    if(al_open_directory(dir) == false)
    {
        al_make_directory(SAVE_PATH);
    }
    al_destroy_fs_entry(dir);
    //---------------------------------

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

bool GameSave::Get_item(int nmb)
{
    if(al_get_config_value(gamesave, "Items", std::to_string(nmb).c_str()) == nullptr)
    {
        return false;
    }
    std::string s = al_get_config_value(gamesave, "Items", std::to_string(nmb).c_str());

    return stoi(s);
}

bool GameSave::Set_item(int nmb)
{
     al_set_config_value(gamesave, "Items", std::to_string(nmb).c_str(), "1");
     return true;
}

float GameSave::Get_ab_cd(int ab_numeber)
{
    std::string s = "cd" + std::to_string(ab_numeber);
    if(al_get_config_value(gamesave, "Items", s.c_str()) == nullptr)
    {
        return -1;
    }
    s = al_get_config_value(gamesave, "Items", s.c_str());
    return stof(s);
}

bool GameSave::Set_ab_cd(int ab_numeber, float cd)
{
    std::string s = "cd" + std::to_string(ab_numeber);
    al_set_config_value(gamesave, "Items",s.c_str(), std::to_string(cd).c_str());
    return true;
}

float GameSave::Get_ab_cast_t(int ab_numeber)
{
    std::string s = "ct" + std::to_string(ab_numeber);
    if(al_get_config_value(gamesave, "Items", s.c_str()) == nullptr)
    {
        return -1;
    }
    s = al_get_config_value(gamesave, "Items", s.c_str());
    return stof(s);
}

bool GameSave::Set_ab_cast_t(int ab_numeber, float ct)
{
    std::string s = "ct" + std::to_string(ab_numeber);
    al_set_config_value(gamesave, "Items",s.c_str(), std::to_string(ct).c_str());
    return true;
}

float GameSave::Set_final_boss_HP_scale(float scale)
{
    al_set_config_value(gamesave, "Player", "Mission4s", std::to_string(scale).c_str());
    return scale;
}

float GameSave::Get_final_boss_HP_scale()
{
    std::string s;
    if(al_get_config_value(gamesave, "Player", "Mission4s") == nullptr)
    {
        return 1;
    }
    s = al_get_config_value(gamesave, "Player", "Mission4s");
    return stof(s);
}

float GameSave::Set_global_HP_scale(float scale)
{
    al_set_config_value(gamesave, "Player", "GlobalHPs", std::to_string(scale).c_str());
    return scale;
}

float GameSave::Get_global_HP_scale()
{
     std::string s;
    if(al_get_config_value(gamesave, "Player", "GlobalHPs") == nullptr)
    {
        return 1;
    }
    s = al_get_config_value(gamesave, "Player", "GlobalHPs");
    return stof(s);
}

float GameSave::Set_global_speed_scale(float scale)
{
    al_set_config_value(gamesave, "Player", "GlobalSpeeds", std::to_string(scale).c_str());
    return scale;
}

float GameSave::Get_global_speed_scale()
{
    std::string s;
    if(al_get_config_value(gamesave, "Player", "GlobalSpeeds") == nullptr)
    {
        return 1;
    }
    s = al_get_config_value(gamesave, "Player", "GlobalSpeeds");
    return stof(s);
}
