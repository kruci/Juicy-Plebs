//R.K.
#include "ScreenPlay.h"
#include <chrono>
#include <random>

ScreenPlay::ScreenPlay(Button *ext_b) : but(ext_b)
{
    n_font = al_load_font("resources/fonts/Asimov.otf",40,0);
    m_font = al_load_font("resources/fonts/Calibri.ttf",30,0);

    std::string bnames[4] = {"Back", "New game"};

    int bpoz[4][4] = {  {1300, global::dHeight -70, 120, 50},
                        { (global::dWidth-120)/2, global::dHeight -70, 120, 50},    };

    for(int a = 0;a < 2;a++)
    {
        buttons.push_back(new Button("resources/fonts/Calibri.ttf", bpoz[a][0], bpoz[a][1], bpoz[a][0] + bpoz[a][2],bpoz[a][1] + bpoz[a][3], bnames[a], al_map_rgb(0,0,128)));
    }

    scba = new ScrollableArea(((float)global::dWidth - 500.0f)/2.0f ,100, 500 ,global::dHeight-200);
    scba->background_col = al_map_rgba(0,0,0,128);

    //Saves loading
    gms = new GameSave();
    std::string dum;
    int a = 0;
    ALLEGRO_FS_ENTRY* dir = al_create_fs_entry("saves/");

    if(al_open_directory(dir) == false)
    {
        al_make_directory("saves/");
    }

    if(al_open_directory(dir))
    {
        ALLEGRO_FS_ENTRY* file;
        while(file = al_read_directory(dir))
        {
            dum = al_get_fs_entry_name(file);
            if( al_get_fs_entry_mode(file) == ALLEGRO_FILEMODE_ISDIR || dum.substr(dum.size()-4,4) != ".sav")
            {
                continue;
            }
            gms->Load(dum);
            savefiles.push_back(dum);

            scba->AddText(5, a * 100 +10, gms->Get_player_name(), al_map_rgb(255,215,0), &n_font);
            scba->AddButton("resources/fonts/Calibri.ttf", 400, a * 100 + 60, 75, 30, "Load", al_map_rgb(0,0,139));
            scba->AddRectangle(1,a * 100 , 500, 100, 2, al_map_rgb(10,10,10));
            scba->AddText(10, a * 100 + 60, "Mission: " + std::to_string(gms->Get_mission_number()), al_map_rgb(255,255,250), &m_font);
            a++;
            gms->Save();
        }
        al_destroy_fs_entry(file);
    }
    al_destroy_fs_entry(dir);
}

ScreenPlay::~ScreenPlay()
{
     if(background != nullptr)
        al_destroy_bitmap(background);
    if(n_font != nullptr)
        al_destroy_font(n_font);
    if(m_font != nullptr)
        al_destroy_font(m_font);

    for(int a = 0;a < buttons.size();a++)
    {
        delete buttons[a];
    }
    buttons.clear();

    savefiles.clear();

    if(scba != nullptr)
        delete scba;

    if(inpf != nullptr)
        delete inpf;

     if(gms != nullptr)
        delete gms;
}

void ScreenPlay::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    int hlp = 0;

    if(is_any_button_clicked() == false)
    {
        scba->Input(event, xscale, yscale);

        for(int a = 0;a < buttons.size();a++)
        {
            buttons[a]->Input(event, xscale, yscale);
        }
    }

    if(buttons[BACK]->is_button_clicked() == true)
    {
        but->unclick();
    }
    else if(buttons[NEWGAME]->is_button_clicked() == true)
    {
        //nasty and not 100% secure
        std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<long> distribution(0,9999999);
        time_t tt;
        time(&tt);
        struct tm *timeseed;
        timeseed = localtime(&tt);
        char bff[20] = {0};

        strftime(bff,20, "saves/%S%M%H%e%m%Y",timeseed);
        std::string s2 = bff;
        s2 += std::to_string(distribution(generator)) + ".sav";

        char bff2[20] = {0};
        strftime(bff2,20, "%D %X",timeseed);
        std::string s = bff2;

        global::save->Create( s2,"Save " + s );
        global::save->Save();
        /*gms->Create( s2,"Save " + s );
        gms->Save();*/
        global::play = true;
    }
    else if( (hlp = scba->What_button_is_clicked()) != 999)
    {
        global::save->Load(savefiles[hlp]);
        global::play = true;
    }


    return;
}

void ScreenPlay::Print()
{
    al_clear_to_color(al_map_rgb(0,125,0));
    scba->Print();

    for(int a = 0;a < buttons.size();a++)
    {
            buttons[a]->Print();
    }
}

bool ScreenPlay::is_any_button_clicked()
{
    for(int a = 0;a < buttons.size();a++)
    {
        if(buttons[a]->is_button_clicked() == true)
        {
            return true;
        }
    }

    return false;
}

bool ScreenPlay::scan_save_files()
{
    //reduntant finction?
    if(gms == nullptr)
        gms = new GameSave();

    savefiles.clear();

    std::string dum;
    int a = 0;
    ALLEGRO_FS_ENTRY* dir = al_create_fs_entry("saves/");

    if(al_open_directory(dir) == false)
    {
        al_make_directory("saves/");
    }

    if(al_open_directory(dir))
    {
        ALLEGRO_FS_ENTRY* file;
        while(file = al_read_directory(dir))
        {
            dum = al_get_fs_entry_name(file);
            if( al_get_fs_entry_mode(file) == ALLEGRO_FILEMODE_ISDIR || dum.substr(dum.size()-4,4) != ".sav")
            {
                continue;
            }
            gms->Load(dum);
            savefiles.push_back(dum);

            scba->AddText(5, a * 100 +10, gms->Get_player_name(), al_map_rgb(255,215,0), &n_font);
            scba->AddButton("resources/fonts/Calibri.ttf", 400, a * 100 + 60, 75, 30, "Load", al_map_rgb(0,0,139));
            scba->AddRectangle(1,a * 100 , 500, 100, 2, al_map_rgb(10,10,10));
            scba->AddText(10, a * 100 + 60, "Mission: " + std::to_string(gms->Get_mission_number()), al_map_rgb(255,255,250), &m_font);
            a++;
            gms->Save();
        }
        al_destroy_fs_entry(file);
    }
    al_destroy_fs_entry(dir);

    return true;
}
