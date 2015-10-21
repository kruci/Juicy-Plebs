//shitty GUI for Allegro 5 by R.K.



#ifndef _RGUIL_H__
#define _RGUIL_H__

//Other
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

//ALLEGRO 5
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_memfile.h>

namespace rguil
{
    extern ALLEGRO_MOUSE_STATE *mouse_state;
}

//classes
class Button;
class ClickableText;
class InputField;
class ScrollableArea;
class ScroolBar;
class SingleKeyInputField;
class BigBitmap;

class Button
{
protected:
    //signed int x1, y1, x2, y2;
    float x1, y1, x2, y2;
    int centerx, centery;
    bool clicked = false;
    bool clicking = false;
    bool mouse_on_it = false;
    bool b_has_image = false;
    bool clicked_again = false;
    int width, height;
    int textx, texty;
    std::string text;
    ALLEGRO_FONT *font = nullptr;
    //ALLEGRO_BITMAP *bmp = nullptr;
    float image_scale_x;
    float image_scale_y;
    float texty_;
    int image_width;
    int image_height;
    bool active = true;
    bool print_active = true;

public:
    ALLEGRO_BITMAP *bmp = nullptr;
    ALLEGRO_COLOR color;
    signed int x,y;
    signed int origin_x1, origin_y1, origin_x2, origin_y2;

    ALLEGRO_BITMAP *as_bitmap = nullptr;

    Button();
    Button(std::string font_to_load, int x1, int y1, int x2, int y2, std::string text, ALLEGRO_COLOR color, std::string image = "0");
    Button(int x1, int y1, int x2, int y2);
    virtual ~Button();

    virtual bool Print();
    bool Bitmap();
    int Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);

    bool is_button_clicked();
    bool is_button_clicking();
    bool is_mouse_in_it();
    bool is_button_clicked_again();
    bool unclick();
    bool has_image();
    int Get_width();
    int Get_height();
    bool Active(bool true_or_false);
    bool Print_active(bool true_or_false);

    bool change_coords(int new_x1, int new_y1, int new_x2, int new_y2);
};

class ClickableText : public Button
{
private:
    std::string ct_normal_font;
    std::string ct_bold_font;
    ALLEGRO_FONT *ct_nfont = nullptr;
    ALLEGRO_FONT *ct_bfont = nullptr;
    int ct_bascent;
    int ct_bwidth;
    std::string ct_text;
    int ct_x1, ct_y1, ct_x2, ct_y2;

public:
    int ct_original_x, ct_original_y;
    int ct_width, ct_height;
    bool outline_if_clicked = true;
    ALLEGRO_COLOR ct_text_color;
    ALLEGRO_COLOR ct_outline_color = al_map_rgb(255,215,0);

    ClickableText(std::string normal_font, std::string bold_font, int x, int y, int font_height, ALLEGRO_COLOR text_color, std::string text_string);
    virtual ~ClickableText();
    bool Input(ALLEGRO_EVENT &event, float &xscale, float &yscale);
    bool Print();

    void Click();
};

class InputField
{
protected:
    signed int x1, y1, x2, y2;
    int width, height;
    ALLEGRO_FONT *font = nullptr;
    Button *detectingbutton = nullptr;
    int text_width, text_height;
    std::string text;
    ALLEGRO_BITMAP *bmp = nullptr;
    ALLEGRO_USTR *al_text = nullptr;
    bool center = false;

    int bling = 0;
    int max_lenght;
    bool lenght_limit = false;

public:
    ALLEGRO_COLOR outline_color;
    ALLEGRO_COLOR text_color;
    ALLEGRO_COLOR bckground_color;

    int al_key = 999;
    signed int x,y;
    signed int origin_x1, origin_y1, origin_x2, origin_y2;

    ALLEGRO_BITMAP* as_bitmap = nullptr;

    InputField();
    InputField(std::string font, std::string init_string, int x, int y, int width, int height, ALLEGRO_COLOR outline = al_map_rgb(0,0,0),
                   ALLEGRO_COLOR textcolor = al_map_rgb(255,255,255), ALLEGRO_COLOR backgroundcolor = al_map_rgba(0,0,0,0));

    virtual ~InputField();

    bool Print();
    bool Bitmap();
    virtual bool Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley);
    bool SetDefaultText(std::string default_text);
    bool AcceptingInput();
    bool StopAcceptingInput();
    bool change_coords(int new_x1, int new_y1, int new_x2, int new_y2);
    int Get_width();
    int Get_height();
    bool Setmaxlenght(int maxlenght);

    virtual bool Centre(bool tru_of_false);
    virtual bool Compute();

    std::string ActualText();
};

class ScrollableArea
{
private:
    ALLEGRO_BITMAP *print_area = nullptr;

    int x1, y1, x2, y2;
    int width, height;
    int print_area_height;

    struct TextStruct{
        float x = 0;
        float y = 0;
        int ascent = 0;
        int width = 0;
        ALLEGRO_FONT *font = nullptr;
        ALLEGRO_COLOR text_color;
        bool delete_font = false;
        std::string text;
    };

    struct RectangleStruct{
        float x = 0;
        float y = 0;
        int width = 0;
        int height = 0;
        int thickness = 0;
        float roundx = 0.0f;
        float roundy = 0.0f;
        ALLEGRO_COLOR outline_color;
        ALLEGRO_COLOR fill_color;
        bool draw_outline = false;
        bool draw_fill = false;
        bool top = false;
    };

public:
    ALLEGRO_COLOR background_col = al_map_rgba(0,0,0,0);
    int last_editet_inpf = 0;

    ScroolBar *scbar = nullptr;
    std::vector<Button*> buttons;
    std::vector<InputField*> inpfields;
    std::vector<TextStruct*> texts;
    std::vector<RectangleStruct*> rectangles;

    ScrollableArea(int x, int y, int width, int height);
    virtual ~ScrollableArea();

    //Push coords as if this was display -> [0,0] top left corner of Scrollable area
    bool AddButton(std::string font_to_load, int x, int y, int bwidth, int bheight, std::string text, ALLEGRO_COLOR color);
    bool AddInputField(std::string font_to_load, std::string init_string, int x, int y, int iwidth, int iheight);

    bool AddSingleKeyInputField(std::string font_to_load, int al_key_code, int x, int y, int iwidth, int iheight, bool center = true);

    bool AddText(int x, int y, std::string text, ALLEGRO_COLOR color, ALLEGRO_FONT **fooont);
    bool AddText(int x, int y, std::string text, ALLEGRO_COLOR color, std::string font_to_load, int font_height);

    bool AddRectangle(int x, int y, int width, int height, int outline_thickness, ALLEGRO_COLOR outline_color,
                      float roundx = 0.0f, float roundy = 0.0f, ALLEGRO_COLOR fill_color = al_map_rgba(0,0,0,0));
    bool AddRectangle_on_top(int x, int y, int width, int height, int outline_thickness, ALLEGRO_COLOR outline_color,
                      float roundx = 0.0f, float roundy = 0.0f, ALLEGRO_COLOR fill_color = al_map_rgba(0,0,0,0));

    bool Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley);
    bool Compute();
    bool Print();
    int What_button_is_clicked();
};

class ScroolBar
{
private:
    int x1, y1, x2, y2;
    int width, height;

    int bar_lenght;
    int bar_y = 0;

    int vissible_height, full_height;
    int vf_change;
    float v_to_f;
    float scrool_shif;

    struct mouse_scrool_event_gather_area{
        int x1;
        int y1;
        int x2;
        int y2;
        int width;
        int height;
    }scroolarea;

    Button *detectingbutton = nullptr;

public:
    ALLEGRO_COLOR outline_color;
    ALLEGRO_COLOR body_color;
    int change = 0;

    ScroolBar(int vissible_area_height, int full_area_height, int event_area_x, int even_area_y, int event_area_width, int event_area_height,
              int barw_x, int barw_y, int barw_widht, int barw_height, ALLEGRO_COLOR outline = al_map_rgb(255, 255, 255), ALLEGRO_COLOR bar = al_map_rgb(202, 196, 191));
    virtual ~ScroolBar();

    bool Print();
    bool Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley);
};

class BigBitmap
{
private:
    std::string bitmap_name;
    ALLEGRO_BITMAP *big_bitmap = nullptr;
    ALLEGRO_BITMAP *tmpbmp = nullptr;
    float region_size_w = 128;
    float region_size_h = 128;
    float orig_width, orig_height;
    int w_regions, h_regions;
    int orig_flags;
    #ifdef _BBDEBUG
    ALLEGRO_FONT *dgbf = al_load_font(_BBDEBUG_FONT, 15, 0);
    #endif // _BBDEBUG

    std::vector<ALLEGRO_BITMAP*> bitmaps;
public:
    float width, height;

    BigBitmap(std::string bitmap_to_load, float sector_width, float sector_height);
    ~BigBitmap();
    bool Draw_bitmap_region(float sx, float sy, float sw, float sh, float dx, float dy, int flags);

};

class SingleKeyInputField: public InputField
{
public:
    SingleKeyInputField(std::string font, int al_key_code, int x, int y, int width, int height, ALLEGRO_COLOR outline = al_map_rgb(0,0,0),
                        ALLEGRO_COLOR textcolor = al_map_rgb(255,255,255), ALLEGRO_COLOR backgroundcolor = al_map_rgba(0,0,0,0));
    virtual ~SingleKeyInputField();

    bool Input(ALLEGRO_EVENT &ev, float &scalex, float &scaley);
    bool Compute();
    bool Centre(bool tru_of_false);
};


#endif // _RGUIL_H__
