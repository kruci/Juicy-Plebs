#include "global.h"

BigBitmap::BigBitmap(std::string bitmap_to_load, float sector_width, float sector_height) : region_size_w(sector_width), region_size_h(sector_height)
{
    ALLEGRO_BITMAP *restoreto =al_get_target_bitmap();

    orig_flags = al_get_new_bitmap_flags();
    al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MAG_LINEAR | ALLEGRO_MIN_LINEAR);
    big_bitmap = al_load_bitmap(bitmap_to_load.c_str());

    if(big_bitmap == nullptr)
    {
        al_show_native_message_box(NULL, "Error", "Failed to load Image", bitmap_to_load.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    orig_width = width = al_get_bitmap_width(big_bitmap);
    orig_height = height = al_get_bitmap_height(big_bitmap);
    w_regions = ceil(orig_width / region_size_w);
    h_regions = ceil(orig_height / region_size_h);

    float vector_size = w_regions+1 + h_regions+1;
    bitmaps.reserve(vector_size);

    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP | ALLEGRO_MAG_LINEAR | ALLEGRO_MIN_LINEAR);

    for(int h = 0; h < h_regions; h++)
    {
        for(int w = 0; w < w_regions; w++)
        {
            bitmaps.push_back(al_create_bitmap(region_size_w, region_size_h));
            al_set_target_bitmap(bitmaps[bitmaps.size()-1]);
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap_region(big_bitmap, w*region_size_w, h*region_size_h, region_size_w, region_size_h, 0, 0, 0);
            #ifdef _BBDEBUG
            std::string cont = "["+ std::to_string(h) +","+ std::to_string(w) +"]";
            al_draw_text(dgbf, al_map_rgb(255,0,0),region_size_w/2,region_size_h/2,ALLEGRO_ALIGN_CENTRE,cont.c_str());
            al_draw_rectangle(0,0,region_size_w, region_size_h, al_map_rgb(255,0,0),0);
            #endif // _BBDEBUG
        }
    }

    al_set_new_bitmap_flags(orig_flags);
    al_set_target_bitmap(restoreto);
}

BigBitmap::~BigBitmap()
{
    if(big_bitmap != nullptr)
        al_destroy_bitmap(big_bitmap);

    for(int a = 0; a < (int)bitmaps.size(); a++)
    {
        al_destroy_bitmap(bitmaps[a]);
    }
    bitmaps.clear();

    if(tmpbmp != nullptr)
        al_destroy_bitmap(tmpbmp);

    #ifdef _BBDEBUG
    if(dgbf != nullptr)
        al_destroy_font(dgbf);
    #endif // _BBDEBUG
}

bool BigBitmap::Draw_bitmap_region(float sx, float sy, float sw, float sh, float dx, float dy, int flags)
{

    int start_w = floor(sx / region_size_w);
    start_w = (start_w < 0 ? 0 : start_w);
    int start_h = floor(sy / region_size_h);
    start_h = (start_h < 0 ? 0 : start_h);
    int fin_w = ceil((sx + sw) / region_size_w);
    fin_w = ( fin_w > w_regions ? w_regions : fin_w);
    int fin_h = ceil((sy + sh) / region_size_h);
    fin_h = ( fin_h > h_regions ? h_regions : fin_h);
    int offset_w = sx - start_w*region_size_w,
    offset_h = sy - start_h*region_size_h;

    if(tmpbmp != nullptr)
        al_destroy_bitmap(tmpbmp);

    ALLEGRO_BITMAP *restoreto = al_get_target_bitmap();
    tmpbmp = al_create_bitmap(sw, sh);
    al_set_target_bitmap(tmpbmp);
    al_clear_to_color(al_map_rgb(0,0,0));

    for(int h = start_h; h < fin_h; h++)
    {
        for(int w = start_w; w < fin_w; w++)
        {
            al_draw_bitmap(bitmaps[h*w_regions + w], (w-start_w)*region_size_w - offset_w, (h-start_h)*region_size_h - offset_h, 0);

        }
    }

    al_set_target_bitmap(restoreto);
    al_draw_bitmap(tmpbmp, dx, dy, flags);
    return true;
}

