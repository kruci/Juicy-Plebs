//R.K.
#include "global.h"

ScroolBar::ScroolBar(int vissible_area_height, int full_area_height, int event_area_x, int even_area_y, int event_area_width, int event_area_height,
                     int barw_x, int barw_y, int barw_widht, int barw_height, ALLEGRO_COLOR outline, ALLEGRO_COLOR bar) :
                    vissible_height(vissible_area_height), full_height(full_area_height), x1(barw_x), y1(barw_y), width(barw_widht),
                    height(barw_height), outline_color(outline), body_color(bar)
{
    x2 = x1 + width;
    y2 = y1 + height;
    scroolarea.x1 = event_area_x;
    scroolarea.y1 = even_area_y;
    scroolarea.width = event_area_width;
    scroolarea.height = event_area_height;
    scroolarea.x2 = scroolarea.x1 + scroolarea.width;
    scroolarea.y2 = scroolarea.y1 + scroolarea.height;
    bar_y = y1;

    v_to_f = (float)vissible_height / (float)full_height;
    vf_change = full_height - vissible_height;

    bar_lenght = (float)vissible_height/(float)full_height * (float)vissible_height;

    detectingbutton = new Button(x1, y1, x2, y1 + bar_lenght);

    scrool_shif = ((float)vf_change / 20 > 20 ? 20 : (float)vf_change / 20);
}

ScroolBar::~ScroolBar()
{
    delete detectingbutton;
}

bool ScroolBar::Print()
{
    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(230,230,230));
    al_draw_rectangle(x1, y1, x2, y2, outline_color, 0);

    al_draw_filled_rectangle(x1 + 2, bar_y, x2 - 2, bar_y + bar_lenght, body_color);
    al_draw_rectangle(x1 + 2, bar_y, x2 - 2, bar_y + bar_lenght, outline_color, 0);

    if(detectingbutton->is_mouse_in_it() == true)
    {
        al_draw_filled_rectangle(x1 + 2, bar_y, x2 - 2, bar_y + bar_lenght, al_map_rgba(0,0,0, 40));
    }
    if(detectingbutton->is_button_clicking() == true)
    {
        al_draw_filled_rectangle(x1 + 2, bar_y, x2 - 2, bar_y + bar_lenght, al_map_rgba(0,0,0, 80));
    }

    return true;
}

bool ScroolBar::Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley)
{
    if(detectingbutton->is_button_clicking() != true)
    {
            detectingbutton->change_coords(x1, bar_y, x2, bar_y + bar_lenght);
    }
    detectingbutton->Input(ev, scalex, scaley);

    if(detectingbutton->is_button_clicking() == true)
    {
        detectingbutton->change_coords(x1 - width * 2, bar_y - 2*bar_lenght, x2 + width * 2, bar_y + bar_lenght + 2*bar_lenght);
        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if(ev.mouse.dy != 0)
            {
                bar_y += ev.mouse.dy;
            }
        }
    }
    else if(rguil::mouse_state->x >= scroolarea.x1*scalex && rguil::mouse_state->x <= scroolarea.x2*scalex &&
            rguil::mouse_state->y >= scroolarea.y1*scaley && rguil::mouse_state->y <= scroolarea.y2*scaley)
    {
        if(ev.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            if(ev.mouse.dz > 0)
            {
                bar_y -= scrool_shif;
            }
            else if(ev.mouse.dz < 0)
            {
                bar_y += scrool_shif;
            }
        }
    }

    if(bar_y + bar_lenght > y2)
    {
        bar_y = y2 - bar_lenght;
    }
    else if(bar_y < y1)
    {
        bar_y = y1;
    }

    change = (float)(bar_y - y1) / v_to_f;

    return true;
}
