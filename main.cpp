//R.K.
#include "global.h"
#include "include/Screens/ScreenMain.h"
#include "include/Audio/AudioHandler.h"

//#define _SOUND_TEST
#define _FPS

#define MusicON "resources/graphics/m_on.png"
#define MusicOFF "resources/graphics/m_off.png"

namespace global
{
    float FPS = 30.0f;
    int dHeight = 810;// d means display - size of drawing board
    int dWidth = 1440;
    int sHeight = 1;// s means screen - after resise
    int sWidth = 1;
    float xscale = 1.0;
    float yscale = 1.0;
    float aspectratio = 1.78f;
    int xratio = 16; //monitor ration
    int yratio = 9;
    ALLEGRO_TRANSFORM trans;
    ALLEGRO_MOUSE_STATE mouse_state;

    bool loop = true;
    bool audio = true;
    bool sound_card = true;
    bool play = false;

    GameSave *save = nullptr;
    AudioHandler *audio_player = nullptr;
    Button *audio_b = nullptr;
}

inline int error_message(std::string error_string)
{
    return al_show_native_message_box(al_get_current_display(), "ERROR", "", error_string.c_str(), nullptr, ALLEGRO_MESSAGEBOX_ERROR);
}

inline int fatal_error_message(std::string error_string)
{
    int a = al_show_native_message_box(al_get_current_display(), "ERROR", "", error_string.c_str(), nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    global::loop = false;
    return a;
}

// error codes: 33 - initialization of Allegro failed
//              44 - allegro is loaded, something fucked up while using Allegro

int main(int argc, char *argv[])
{
    bool windowed = false;
    float rescale = 1.0f;
    std::string arg;
    if(argc > 1)
    {
        arg = argv[1];
        if(arg == "--help")
        {
            std::cout << "-s {scale} for running in windowed mode and scaled (standart size is 1440*810)" << std::endl;
            return 0;
        }
        else if(arg == "-s")
        {
            if( argc > 2)
            {
                arg = argv[2];
                rescale = atof(argv[2]);
            }
            windowed = true;
        }
    }


    /**initialize allegro*/
    if(!al_init()){error_message("al_init()");return 33;}
    if(!al_init_primitives_addon()){error_message("al_init_primitives_addon()");return 33;}
    //if(!al_install_keyboard()){error_message("al_install_keyboard()");return 33;} //no use for keyboard in this game
    if(!al_install_mouse()){error_message("al_install_mouse()");return 33;}
    if(!al_install_keyboard()){error_message("al_install_keyboard()");return 33;}
    if(!al_init_image_addon()){error_message("al_init_image_addon()");return 33;}
    al_init_font_addon(); // returns void
    if(!al_init_ttf_addon()){error_message("al_init_ttf_addon()");return 33;}
    //audio
    if(al_install_audio() == true)
    {
        if(al_init_acodec_addon() == true){}
        else
        {
            error_message("al_init_acodec_addon() - cant initialize audio codec");
            global::audio = false;
            global::sound_card = false;
        }
    }
    else
    {
        error_message("al_install_audio() - cant found sound device");
        global::audio = false;
        global::sound_card = false;
    }

    /**Some allegro variables*/
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    ALLEGRO_BITMAP *logo = nullptr;

    /**Display preparation*/
    bool supported_ratio = true;
    ALLEGRO_MONITOR_INFO mon_info;
    al_get_monitor_info(0, &mon_info);
    global::sHeight = mon_info.y2 - mon_info.y1; //gets monitor size in pixels
    global::sWidth = mon_info.x2 - mon_info.x1;
    global::aspectratio = round( ((float)global::sWidth / (float)global::sHeight) * 100.0f) / 100.0f; //gets aspectratio
    if(global::aspectratio == 1.78f){global::xratio = 16; global::yratio = 9;}      // 16:9 screen ration
    else if(global::aspectratio == 1.6f){global::xratio = 16; global::yratio = 10;} // 16:10
    else if(global::aspectratio == 1.33f){global::xratio = 4; global::yratio = 3;}  // 4:3
    else{supported_ratio = false;}
    global::dHeight = global::dWidth  / global::xratio * global::yratio;
    global::xscale = (float)global::sWidth / (float)global::dWidth;
    global::yscale = (float)global::sHeight / (float)global::dHeight;

    /**display creation*/
    al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR | ALLEGRO_MIN_LINEAR); // Thanks to this, magnified fonts dont look retarted, and game is fast (hopefully) :D
    if(windowed == true || supported_ratio == false)
    {
        supported_ratio = true;
        al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
        global::xscale = rescale;
        global::yscale = rescale;
        global::dWidth = 1440;
        global::dHeight = 810;
        display = al_create_display(global::dWidth*rescale, global::dHeight*rescale);
    }
    else
    {
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_OPENGL);
        display = al_create_display(global::dWidth, global::dHeight);
    }
    if(display == nullptr){error_message("al_create_display()"); return 1;}
    al_set_window_title(display, "Este neviem meno, ale asi neco so zemiakom");

    /**logo*/
    logo = al_load_bitmap("resources/graphics/logo.png");
    if(logo == nullptr){error_message("resources/graphics/logo.png not found");}
    else{ al_set_display_icon(display, logo);}


    /**Transformation*/
    al_identity_transform(&global::trans);
    if(supported_ratio == true)
    {
        al_scale_transform(&global::trans, global::xscale, global::yscale);
    }
    else
    {
        error_message("Unsupported monitor type - upgrade you monitor pls");
        float scale_backup_plan = (global::xscale > global::yscale ? global::yscale : global::xscale);
        global::xscale = scale_backup_plan;
        global::yscale = scale_backup_plan;
        al_scale_transform(&global::trans, global::xscale, global::yscale);
    }
    al_use_transform(&global::trans);

    /**timer*/
    timer = al_create_timer(1.0f/global::FPS);
    if(timer == nullptr){error_message("al_create_timer()"); return 44;}
    bool redraw = true;

    /**even que*/
    event_queue = al_create_event_queue();
    if(event_queue == nullptr){error_message("al_create_event_queue()"); return 44;}

    /**registering event sources*/
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    rguil::mouse_state = &global::mouse_state;

    global::audio_player = new AudioHandler(10);

    #ifdef _SOUND_TEST
    ALLEGRO_SAMPLE *s = al_load_sample("resources/music/Fuck_This_Shit_Im_Out.wav");
    ALLEGRO_SAMPLE_INSTANCE *si = al_create_sample_instance(s);
    global::audio_player->global_sounds.push_back(si);
    global::audio_player->Play_sample_instance(&si, ALLEGRO_PLAYMODE_LOOP);
    #endif // _SOUND_TEST

    #ifdef _FPS
    ALLEGRO_FONT *fps_font = nullptr;
    fps_font = al_load_font("resources/fonts/Asimov.otf", 12,0);
    int counter = 0;
    time_t tsttme2 = time(nullptr), tsttme = time(nullptr);
    int fps = 0;
    #endif // FPS

    global::save = new GameSave();
    ScreenMain *SCMain = new ScreenMain();
    global::audio_b = new Button("resources/fonts/Calibri.ttf", 1240, global::dHeight -65, 1240 + 40, global::dHeight - 25,
                                 "", al_map_rgba(0,0,0,0),
                                 ( global::audio == true ? MusicON : MusicOFF));

    /**Main loop*/ //forced 30 FPS, drawing and computing in same thread
    while(global::loop == true)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        al_get_mouse_state(&global::mouse_state);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        /**Take event input here*/
        if(global::audio_b->Input(ev, global::xscale, global::yscale) == 2)
        {
            global::audio_b->unclick();
            global::audio = (global::audio == true ? false : true);

            if(global::audio == true)
            {
                al_destroy_bitmap(global::audio_b->bmp);
                global::audio_b->bmp = al_load_bitmap(MusicON);
                global::audio_player->Mute_sample_instances(false);
            }
            else
            {
                al_destroy_bitmap(global::audio_b->bmp);
                global::audio_b->bmp = al_load_bitmap(MusicOFF);
                global::audio_player->Mute_sample_instances(true);
            }
        }

        SCMain->Input(ev, global::xscale, global::yscale);
        /**---------------------*/

        #ifdef _FPS
        tsttme2 = time(&tsttme2);
        if(difftime(tsttme2,tsttme) >= 1.0f)
        {
            tsttme = time(&tsttme);
            fps = counter;
            counter = 0;
        }
        #endif // FPS


        if(redraw == true && al_is_event_queue_empty(event_queue))
        {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));


            /**Draw and compute here*/
            SCMain->Print();
            global::audio_b->Print();
            /**---------------------*/

            #ifdef _FPS
            counter++;
            al_draw_text(fps_font, al_map_rgb(255,0,0), 0.0f,0.0f, 0, std::to_string(fps).c_str());
            #endif // FPS
            al_flip_display();
        }
    }
    #ifdef _SOUND_TEST
    global::audio_player->Stop_sample_instances();
    global::audio_player->global_sounds.erase(global::audio_player->global_sounds.begin());
    al_destroy_sample_instance(si);
    al_destroy_sample(s);
    #endif // _SOUND_TEST

    delete global::audio_b;
    delete SCMain;
    delete global::save;
    delete global::audio_player;

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    if(logo != nullptr)
        al_destroy_bitmap(logo);
    #ifdef _FPS
    al_destroy_font(fps_font);
    #endif // FPS

    return 0;
}
// there will be lags
