//R.K.
#include "global.h"

ScrollableArea::ScrollableArea(int x, int y, int width, int height)
                              : x1(x), y1(y), width(width), height(height)
{
    x2 = x1 + width;
    y2 = y1 + height;

    print_area_height = height /*+ (float)height / 10.0f*/;
    print_area = al_create_bitmap(width, print_area_height);
    al_set_target_bitmap(print_area);
    al_clear_to_color(al_map_rgba(0,0,0,0));
    al_set_target_backbuffer(al_get_current_display());

    scbar = new ScroolBar(height, al_get_bitmap_height(print_area), x1, y1, width, height, x2 - 15, y1 , 15, height);
}

ScrollableArea::~ScrollableArea()
{
    for(int a = 0;a < (int)buttons.size();a++)
    {
        delete buttons[a];
    }
    buttons.clear();

    for(int a = 0;a < (int)inpfields.size();a++)
    {
        delete inpfields[a];
    }
    inpfields.clear();

    for(int a = 0;a < (int)texts.size();a++)
    {
        if(texts[a]->delete_font == true)
        {
            al_destroy_font(texts[a]->font);
        }
        delete texts[a];
    }
    texts.clear();

    for(int a = 0;a < (int)rectangles.size();a++)
    {
        delete rectangles[a];
    }
    rectangles.clear();

    al_destroy_bitmap(print_area);

    delete scbar;
}

bool ScrollableArea::AddButton(std::string font_to_load, int x, int y, int bwidth, int bheight, std::string text, ALLEGRO_COLOR color)
{
    buttons.push_back(new Button(font_to_load, x + x1, y + y1, x1 + x + bwidth, y1 + y + bheight, text, color));

    if( (bheight + y) > print_area_height)
    {
        print_area_height = bheight + y+1;
        //al_destroy_bitmap(print_area);
        //print_area = al_create_bitmap(width, print_area_height);

        delete scbar;
        scbar = new ScroolBar(height, print_area_height, x1, y1, width, height, x2 - 15, y1 , 15, height);
    }

    return true;
}

bool ScrollableArea::AddInputField(std::string font_to_load, std::string init_string, int x, int y, int iwidth, int iheight)
{
    inpfields.push_back(new InputField(font_to_load, init_string, x + x1, y + y1, iwidth, iheight));

    if( (iheight + y) > print_area_height)
    {
        print_area_height = iheight + y+1;
        //al_destroy_bitmap(print_area);
        //print_area = al_create_bitmap(width, print_area_height);

        delete scbar;
        scbar = new ScroolBar(height, print_area_height, x1, y1, width, height, x2 - 15, y1 , 15, height);
    }

    return true;
}

bool ScrollableArea::AddSingleKeyInputField(std::string font_to_load, int al_key_code, int x, int y, int iwidth, int iheight, bool center)
{
    inpfields.push_back(new SingleKeyInputField(font_to_load, al_key_code, x + x1, y + y1, iwidth, iheight));
    inpfields[inpfields.size()-1]->Centre(center);
    if( (iheight + y) > print_area_height)
    {
        print_area_height = iheight + y+1;
        //al_destroy_bitmap(print_area);
        //print_area = al_create_bitmap(width, print_area_height);

        delete scbar;
        scbar = new ScroolBar(height, print_area_height, x1, y1, width, height, x2 - 15, y1 , 15, height);
    }

    return true;
}

bool ScrollableArea::AddText(int x, int y, std::string text, ALLEGRO_COLOR color, ALLEGRO_FONT **fooont)
{
    texts.push_back(new TextStruct);
    texts[texts.size()-1]->x = x;
    texts[texts.size()-1]->y = y;
    texts[texts.size()-1]->text = text;
    texts[texts.size()-1]->font = *fooont;
    texts[texts.size()-1]->ascent = al_get_font_ascent(texts[texts.size()-1]->font);
    texts[texts.size()-1]->width = al_get_text_width(texts[texts.size()-1]->font, texts[texts.size()-1]->text.c_str());
    texts[texts.size()-1]->text_color = color;

    if( (texts[texts.size()-1]->ascent + y) > print_area_height)
    {
        print_area_height = texts[texts.size()-1]->ascent + y+1;
        //al_destroy_bitmap(print_area);
        //print_area = al_create_bitmap(width, print_area_height);

        delete scbar;
        scbar = new ScroolBar(height, print_area_height, x1, y1, width, height, x2 - 15, y1 , 15, height);
    }

    return true;
}

bool ScrollableArea::AddText(int x, int y, std::string text, ALLEGRO_COLOR color, std::string font_to_load, int font_height)
{
    texts.push_back(new TextStruct);
    texts[texts.size()-1]->x = x;
    texts[texts.size()-1]->y = y;
    texts[texts.size()-1]->text = text;
    texts[texts.size()-1]->font = al_load_ttf_font(font_to_load.c_str(), font_height, 0);
    texts[texts.size()-1]->delete_font = true;
    texts[texts.size()-1]->ascent = al_get_font_ascent(texts[texts.size()-1]->font);
    texts[texts.size()-1]->width = al_get_text_width(texts[texts.size()-1]->font, texts[texts.size()-1]->text.c_str());
    texts[texts.size()-1]->text_color = color;

    if( (texts[texts.size()-1]->ascent + y) > print_area_height)
    {
        print_area_height = texts[texts.size()-1]->ascent + y+1;
        //al_destroy_bitmap(print_area);
        //print_area = al_create_bitmap(width, print_area_height);

        delete scbar;
        scbar = new ScroolBar(height, print_area_height, x1, y1, width, height, x2 - 15, y1 , 15, height);
    }

    return true;
}

bool ScrollableArea::AddRectangle(int x, int y, int rwidth, int rheight, int outline_thickness, ALLEGRO_COLOR outline_color,
                      float roundx, float roundy, ALLEGRO_COLOR fill_color)
{

    rectangles.push_back(new RectangleStruct);
    rectangles[rectangles.size()-1]->x = x;
    rectangles[rectangles.size()-1]->y = y;
    rectangles[rectangles.size()-1]->width = rwidth;
    rectangles[rectangles.size()-1]->height = rheight;
    rectangles[rectangles.size()-1]->thickness = outline_thickness;
    rectangles[rectangles.size()-1]->roundx = roundx;
    rectangles[rectangles.size()-1]->roundy = roundy;
    rectangles[rectangles.size()-1]->outline_color = outline_color;
    rectangles[rectangles.size()-1]->fill_color = fill_color;

    if(outline_color.a > 0)
    {
        rectangles[rectangles.size()-1]->draw_outline = true;
    }
    if(fill_color.a > 0)
    {
        rectangles[rectangles.size()-1]->draw_fill = true;
    }

    if( (rheight + y + 0) > print_area_height)
    {
        print_area_height = rheight + y + 1;
        //al_destroy_bitmap(print_area);
        //print_area = nullptr;
        //print_area = al_create_bitmap(width, print_area_height);

        delete scbar;
        scbar = new ScroolBar(height, print_area_height, x1, y1, width, height, x2 - 15, y1 , 15, height);
    }

    return true;
}

bool ScrollableArea::AddRectangle_on_top(int x, int y, int width, int height, int outline_thickness, ALLEGRO_COLOR outline_color,
                      float roundx, float roundy, ALLEGRO_COLOR fill_color)
{
    AddRectangle(x,  y,  width,  height, outline_thickness,  outline_color, roundx,  roundy,  fill_color);
    rectangles[rectangles.size()-1]->top = true;

    return true;
}


bool ScrollableArea::Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley)
{
    int scbch1 = scbar->change;
    bool chancor = false;
    scbar->Input(ev, scalex, scaley);

    if(scbch1 != scbar->change)
        chancor = true;

    if(rguil::mouse_state->x >= x1*scalex && rguil::mouse_state->x <= x2*scalex &&
    rguil::mouse_state->y >= y1*scaley && rguil::mouse_state->y <= y2*scaley)
    {
        for(int a = 0; a < (int)buttons.size(); a++)
        {
            if(chancor == true)
                buttons[a]->change_coords(buttons[a]->origin_x1, buttons[a]->origin_y1 - scbar->change, buttons[a]->origin_x2, buttons[a]->origin_y2 - scbar->change);

            buttons[a]->Input(ev, scalex, scaley);
        }
    }

    for(int a = 0; a < (int)inpfields.size(); a++)
    {
        if((rguil::mouse_state->x >= x1*scalex && rguil::mouse_state->x <= x2*scalex &&
        rguil::mouse_state->y >= y1*scaley && rguil::mouse_state->y <= y2*scaley) )
        {
            if(chancor == true)
            {
                inpfields[a]->change_coords(inpfields[a]->origin_x1 + x1, inpfields[a]->origin_y1 + y1 - scbar->change, inpfields[a]->origin_x2 +x1,
                inpfields[a]->origin_y2 + y1 - scbar->change);
            }
            int t = inpfields[a]->al_key;
            inpfields[a]->Input(ev, scalex, scaley);
            inpfields[a]->Compute();
            last_editet_inpf = (inpfields[a]->al_key != t ? a : last_editet_inpf);
        }
    }

    return true;
}

bool ScrollableArea::Compute()
{

    return true;
}

bool ScrollableArea::Print()
{
    al_set_target_bitmap(print_area);
    al_clear_to_color(background_col);

    // print shit
    for(int a = 0; a < (int)rectangles.size();a++)
    {
        if( (rectangles[a]->y + rectangles[a]->height - scbar->change) >= 0 && (rectangles[a]->y - scbar->change) <= height )
        {
            if(rectangles[a]->draw_fill == true)
            {
                al_draw_filled_rounded_rectangle(rectangles[a]->x, rectangles[a]->y - scbar->change, rectangles[a]->x + rectangles[a]->width, rectangles[a]->y + rectangles[a]->height - scbar->change,
                rectangles[a]->roundx, rectangles[a]->roundy, rectangles[a]->fill_color);
            }
            if(rectangles[a]->draw_outline == true)
            {
                al_draw_rounded_rectangle(rectangles[a]->x, rectangles[a]->y - scbar->change, rectangles[a]->x + rectangles[a]->width, rectangles[a]->y + rectangles[a]->height - scbar->change,
                                          rectangles[a]->roundx, rectangles[a]->roundy, rectangles[a]->outline_color, rectangles[a]->thickness);
            }
        }
    }

    for(int a = 0; a < (int)buttons.size();a++)
    {
        if( (buttons[a]->origin_y1 + buttons[a]->Get_height() - scbar->change-y1) >= 0 && (buttons[a]->origin_y1 - scbar->change-y1) <= height )
        {
            buttons[a]->Bitmap();
            al_set_target_bitmap(print_area);
            al_draw_bitmap(buttons[a]->as_bitmap, buttons[a]->origin_x1 - x1, buttons[a]->origin_y1 - y1 - scbar->change, 0);
        }
    }

    for(int a = 0; a < (int)inpfields.size();a++)
    {
        if( (inpfields[a]->origin_y1 + inpfields[a]->Get_height() - scbar->change) >= 0 && (inpfields[a]->origin_y1 - scbar->change) <= height )
        {
            inpfields[a]->Bitmap();
            al_set_target_bitmap(print_area);
            al_draw_bitmap(inpfields[a]->as_bitmap, inpfields[a]->origin_x1 - x1, inpfields[a]->origin_y1 - y1 - scbar->change, 0);
        }
    }

    al_hold_bitmap_drawing(true);//text are printed faster
    for(int a = 0; a < (int)texts.size();a++)
    {
        if( (texts[a]->y + texts[a]->ascent - scbar->change) >= 0 && (texts[a]->y - scbar->change) <= height )
        {
            al_draw_text(texts[a]->font ,texts[a]->text_color, texts[a]->x, texts[a]->y - scbar->change, 0, texts[a]->text.c_str());
        }
    }
    al_hold_bitmap_drawing(false);

    for(int a = 0; a < (int)rectangles.size();a++)
    {
        if(rectangles[a]->top == true &&
           ( (rectangles[a]->y + rectangles[a]->height - scbar->change) >= 0 && (rectangles[a]->y - scbar->change) <= height ))
        {
            if(rectangles[a]->draw_fill == true)
            {
                al_draw_filled_rounded_rectangle(rectangles[a]->x, rectangles[a]->y - scbar->change, rectangles[a]->x + rectangles[a]->width, rectangles[a]->y + rectangles[a]->height - scbar->change   ,
                                             rectangles[a]->roundx, rectangles[a]->roundy, rectangles[a]->fill_color);
            }
            if(rectangles[a]->draw_outline == true)
            {
                al_draw_rounded_rectangle(rectangles[a]->x, rectangles[a]->y - scbar->change, rectangles[a]->x + rectangles[a]->width, rectangles[a]->y + rectangles[a]->height - scbar->change,
                                             rectangles[a]->roundx, rectangles[a]->roundy, rectangles[a]->outline_color, rectangles[a]->thickness);
            }
        }
    }

    al_set_target_backbuffer(al_get_current_display());
    al_draw_bitmap(print_area, x1,y1,0);
    //al_draw_bitmap_region(print_area, 0, scbar->change, width, height, x1, y1, 0);
    scbar->Print();

    //std::cout << "scba h = " << al_get_bitmap_height(print_area) << std::endl;

    return true;
}

int ScrollableArea::What_button_is_clicked()
{
    for(int a = 0; a < (int)buttons.size();a++)
    {
        if(buttons[a]->is_button_clicked() == true)
        {
            return a;
        }
    }

    return 999;
}

