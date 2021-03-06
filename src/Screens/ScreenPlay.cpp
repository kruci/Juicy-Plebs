//R.K.
#include "ScreenPlay.h"
#include <chrono>
#include <random>

#define SCREENPLAY_NMB 3  //number of buttons

ScreenPlay::ScreenPlay(Button *ext_b) : but(ext_b)
{
    n_font = al_load_font("resources/fonts/Asimov.otf",40,0);
    m_font = al_load_font("resources/fonts/Calibri.ttf",30,0);
    s_font = al_load_font("resources/fonts/Calibri.ttf",20,0);

    std::string bnames[SCREENPLAY_NMB] = {"Back", "New game", "OK"};

    int bpoz[SCREENPLAY_NMB][4] = {  {1300, global::dHeight -70, 120, 50},
                                     {(global::dWidth-120)/2, global::dHeight -70, 120, 50},
                                     {(global::dWidth-120)/2, (global::dHeight-50)/2 +45, 120, 50}  };

    for(int a = 0;a < SCREENPLAY_NMB;a++)
    {
        buttons.push_back(new Button("resources/fonts/Calibri.ttf", bpoz[a][0], bpoz[a][1], bpoz[a][0] + bpoz[a][2],bpoz[a][1] + bpoz[a][3], bnames[a], al_map_rgb(0,0,128)));
    }
    buttons[OK]->Active(false);
    buttons[OK]->Print_active(false);

    scba = new ScrollableArea(((float)global::dWidth - 500.0f)/2.0f ,100, 500 ,global::dHeight-200);
    scba->background_col = al_map_rgba(50,50,50,120);

    //graphic background trash
    zemak_bitmpa = al_load_bitmap("resources/graphics/zemiacik.png");
    if(zemak_bitmpa == nullptr)
    {
        error_message("Could not load image : resources/graphics/zemiacik.png");
    }

    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1,5);
    std::uniform_real_distribution<float> change(-10, 10);

    std::uniform_int_distribution<int> width(0,global::dWidth - ZEMIAK_SIZE);
    std::uniform_int_distribution<int> height(0,global::dHeight-ZEMIAK_SIZE);

    number_of_zemaky = distribution(generator);
    zemaky = new float[number_of_zemaky*4];

    for(int a = 0;a < number_of_zemaky*4;a+=4)
    {
        zemaky[a] = width(generator);
        zemaky[a+1] = height(generator);
        zemaky[a+2] = round(change(generator));
        zemaky[a+3] = round(change(generator));
    }
    //------------------------------------------


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

            std::stringstream sss1, sss2;
            scba->AddText(150, a*100 +65, "HP x", al_map_rgb(255,255,250), &s_font);
            sss1 << std::fixed << std::setprecision(3) << gms->Get_global_HP_scale();
            scba->AddInputField("resources/fonts/Calibri.ttf", sss1.str(),200,a*100 +65, 45,20);
            scba->AddText(250, a*100 +65, "Speed x", al_map_rgb(255,255,250), &s_font);
            sss2 << std::fixed << std::setprecision(3) << gms->Get_global_speed_scale();
            scba->AddInputField("resources/fonts/Calibri.ttf", sss2.str(),330,a*100 +65, 45,20);

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
    if(s_font != nullptr)
        al_destroy_font(s_font);

    for(int a = 0;a < (int)buttons.size();a++)
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

    if(zemak_bitmpa != nullptr)
        al_destroy_bitmap(zemak_bitmpa);
    if(zemaky != nullptr)
        delete [] zemaky;
}

void ScreenPlay::Input(ALLEGRO_EVENT &event, float &xscale, float &yscale)
{
    int hlp = 0;

    if(couldnot_load_savefile == true)
    {
        if(buttons[OK]->Input(event, xscale, yscale) == 2)
        {
            buttons[OK]->unclick();
            buttons[OK]->Active(false);
            buttons[OK]->Print_active(false);
            couldnot_load_savefile = false;
            scan_save_files();
        }
        return;
    }

    if(is_any_button_clicked() == false)
    {
        scba->Input(event, xscale, yscale);

        for(int a = 0;a < (int)buttons.size();a++)
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

        strftime(bff,20, "%S%M%H%e%m%Y",timeseed);
        std::string s2 = "saves/";
        s2 += bff;
        s2 += std::to_string(distribution(generator)) + ".sav";

        char bff2[20] = {0};
        strftime(bff2,20, "%D %X",timeseed);
        std::string s = bff2;

        global::save->Create( s2,"Save " + s );
        global::save->Save();
        but->unclick();
        global::play = true;
    }
    else if( (hlp = scba->What_button_is_clicked()) != 999)
    {
        if(global::save->Load(savefiles[hlp]) == false)
        {
            scba->buttons[hlp]->unclick();
            couldnot_load_savefile = true;
            buttons[OK]->Active(true);
            buttons[OK]->Print_active(true);

            return;
        }
        but->unclick();
        global::save->Set_global_HP_scale(atof(scba->inpfields[hlp*2]->ActualText().c_str()));
        global::save->Set_global_speed_scale(atof(scba->inpfields[hlp*2 +1]->ActualText().c_str()));
        global::play = true;
    }


    return;
}

void ScreenPlay::Print()
{
    al_clear_to_color(al_map_rgb(0,0,0));

    for(int a = 0;a < number_of_zemaky*4;a+=4)
    {

        zemaky[a] += zemaky[a+2];
        zemaky[a+1] += zemaky[a+3];

        if(zemaky[a] <= 0)
        {
            zemaky[a+2] = - zemaky[a+2];
        }
        else if(zemaky[a] + ZEMIAK_SIZE >= global::dWidth)
        {
            zemaky[a+2] = - zemaky[a+2];
        }

        if(zemaky[a+1] <= 0)
        {
            zemaky[a+3] = - zemaky[a+3];
        }
        else if(zemaky[a+1] + ZEMIAK_SIZE >= global::dHeight)
        {
            zemaky[a+3] = - zemaky[a+3];
        }

        al_draw_scaled_bitmap(zemak_bitmpa, 0, 0, al_get_bitmap_height(zemak_bitmpa), al_get_bitmap_width(zemak_bitmpa),
                                zemaky[a], zemaky[a+1], ZEMIAK_SIZE, ZEMIAK_SIZE, 0);

    }

    scba->Print();

    for(int a = 0;a < (int)buttons.size();a++)
    {
            buttons[a]->Print();
    }

    if(couldnot_load_savefile == true)
    {
        al_draw_filled_rectangle(0,0,global::dWidth, global::dHeight, al_map_rgba(0,0,0,150));
        al_draw_filled_rectangle(400, global::dHeight/2 - 100, global::dWidth - 400, global::dHeight/2 + 100, al_map_rgba(100, 100, 100, 230));
        al_draw_rectangle(400, global::dHeight/2 - 100, global::dWidth - 400, global::dHeight/2 + 100, al_map_rgb(0,0,150), 2);

        al_draw_text(n_font, al_map_rgb(255,255,255), 400 + (global::dWidth- 800 - al_get_text_width(n_font, "Could not load safe file"))/2 ,
                     global::dHeight/2 - 80, 0, "Could not load safe file");
        buttons[OK]->Print();
    }

    return;
}

bool ScreenPlay::is_any_button_clicked()
{
    for(int a = 0;a < (int)buttons.size();a++)
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


            std::stringstream sss1, sss2;
            scba->AddText(150, a*100 +65, "HP x", al_map_rgb(255,255,250), &s_font);
            sss1 << std::fixed << std::setprecision(3) << gms->Get_global_HP_scale();
            scba->AddInputField("resources/fonts/Calibri.ttf", sss1.str(),200,a*100 +65, 45,20);
            scba->AddText(250, a*100 +65, "Speed x", al_map_rgb(255,255,250), &s_font);
            sss2 << std::fixed << std::setprecision(3) << gms->Get_global_speed_scale();
            scba->AddInputField("resources/fonts/Calibri.ttf", sss2.str(),330,a*100 +65, 45,20);

            a++;
            gms->Save();
        }
        al_destroy_fs_entry(file);
    }
    al_destroy_fs_entry(dir);

    return true;
}
