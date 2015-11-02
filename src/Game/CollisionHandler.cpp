#include "CollisionHandler.h"

void CollisionHandler::BeginContact(b2Contact* contact)
{
    universal_data *dat1, *dat2;

    dat1 = (universal_data*)contact->GetFixtureA()->GetBody()->GetUserData();
    dat2 = (universal_data*)contact->GetFixtureB()->GetBody()->GetUserData();

    //std::cout << dat1->which_vector << " " << dat2->which_vector << std::endl;

    if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR  &&
         dat2->which_vector == ScreenGame::ENTITY_VECTOR) )
    {
        if(refscreen->entities[dat2->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->dead = true;
            global::audio_player->Play_sample_instance(&refscreen->sounds[ScreenGame::sound_DEAD]->instance, ALLEGRO_PLAYMODE_ONCE);
            if(refscreen->entities[dat1->vectro_poz]->type == ScreenGame::C4KACK)
            {
                refscreen->entities[dat1->vectro_poz]->to_delete = true;
            }
        }
        else if(refscreen->entities[dat1->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->dead = true;
            global::audio_player->Play_sample_instance(&refscreen->sounds[ScreenGame::sound_DEAD]->instance, ALLEGRO_PLAYMODE_ONCE);
            if(refscreen->entities[dat2->vectro_poz]->type == ScreenGame::C4KACK)
            {
                refscreen->entities[dat2->vectro_poz]->to_delete = true;
            }
        }
    }
    else if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR &&
              dat2->which_vector == ScreenGame::ITEMS_VECTOR) )
    {
        if(refscreen->entities[dat1->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->mItems[dat2->vectro_poz]->to_delete = true;


            if(refscreen->abilities[refscreen->mItems[dat2->vectro_poz]->type]->unlocked == true)
                return;

            refscreen->abilities[refscreen->mItems[dat2->vectro_poz]->type]->unlocked = true;

            if(refscreen->abilities[refscreen->mItems[dat2->vectro_poz]->type]->usable == true)
            {
                refscreen->abilities[refscreen->mItems[dat2->vectro_poz]->type]->ab_but =
                new Button( refscreen->ab_button_coord_x + refscreen->gui_ab_x_mult*(AB_IMAGE_SIZE+10) , refscreen->ab_button_coord_y,
                refscreen->ab_button_coord_x + refscreen->gui_ab_x_mult*(AB_IMAGE_SIZE+10) + AB_IMAGE_SIZE, refscreen->ab_button_coord_y + AB_IMAGE_SIZE);

                refscreen->gui_ab_x_mult++;

                refscreen->scrollable_ab_index.push_back(refscreen->mItems[dat2->vectro_poz]->type);
                if(refscreen->scrollable_ab_index.size()==2){refscreen->selected_ab_for_midle_b = 1;}
            }


            //global::save->Set_item(refscreen->mItems[dat2->vectro_poz]->type);
        }
    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR &&
             dat1->which_vector == ScreenGame::ITEMS_VECTOR)  )
    {
        if(refscreen->entities[dat2->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->mItems[dat1->vectro_poz]->to_delete = true;

            if(refscreen->abilities[refscreen->mItems[dat1->vectro_poz]->type]->unlocked == true)
                return;

            refscreen->abilities[refscreen->mItems[dat1->vectro_poz]->type]->unlocked = true;

            if(refscreen->abilities[refscreen->mItems[dat1->vectro_poz]->type]->usable == true)
            {
                refscreen->abilities[refscreen->mItems[dat1->vectro_poz]->type]->ab_but =
                new Button( refscreen->ab_button_coord_x + refscreen->gui_ab_x_mult*(AB_IMAGE_SIZE+10) , refscreen->ab_button_coord_y,
                refscreen->ab_button_coord_x + refscreen->gui_ab_x_mult*(AB_IMAGE_SIZE+10) + AB_IMAGE_SIZE, refscreen->ab_button_coord_y + AB_IMAGE_SIZE);

                refscreen->gui_ab_x_mult++;

                refscreen->scrollable_ab_index.push_back(refscreen->mItems[dat1->vectro_poz]->type);
                if(refscreen->scrollable_ab_index.size()==2){refscreen->selected_ab_for_midle_b = 1;}
            }
            //global::save->Set_item(refscreen->mItems[dat1->vectro_poz]->type);
        }
    }
    else if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR &&
              dat2->which_vector == ScreenGame::PROJECTILES_VECTOR) )
    {
        if(refscreen->entities[dat1->vectro_poz]->type != ScreenGame::PLAYER)
        {
            if(refscreen->projectiles[dat2->vectro_poz]->type == ScreenGame::pr_KYCH)
            {
                refscreen->entities[dat1->vectro_poz]->hp -= refscreen->projectiles[dat2->vectro_poz]->damage;
                return;
            }
            refscreen->projectiles[dat2->vectro_poz]->to_delete = true;
            refscreen->entities[dat1->vectro_poz]->hp -= refscreen->projectiles[dat2->vectro_poz]->damage;
            refscreen->entities[dat1->vectro_poz]->stunted_for += refscreen->projectiles[dat2->vectro_poz]->stun_time;
        }
    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR &&
             dat1->which_vector == ScreenGame::PROJECTILES_VECTOR)  )
    {
        if(refscreen->entities[dat2->vectro_poz]->type != ScreenGame::PLAYER)
        {
            if(refscreen->projectiles[dat1->vectro_poz]->type == ScreenGame::pr_KYCH)
            {
                refscreen->entities[dat2->vectro_poz]->hp -= refscreen->projectiles[dat1->vectro_poz]->damage;
                return;
            }

            refscreen->projectiles[dat1->vectro_poz]->to_delete = true;
            refscreen->entities[dat2->vectro_poz]->hp -= refscreen->projectiles[dat1->vectro_poz]->damage;
            refscreen->entities[dat2->vectro_poz]->stunted_for += refscreen->projectiles[dat1->vectro_poz]->stun_time;
        }
    }
    else if( (dat1->which_vector == ScreenGame::WALLS_VECTOR &&
              dat2->which_vector == ScreenGame::PROJECTILES_VECTOR) )
    {
            refscreen->projectiles[dat2->vectro_poz]->to_delete = true;
    }
    else if( (dat2->which_vector == ScreenGame::WALLS_VECTOR &&
             dat1->which_vector == ScreenGame::PROJECTILES_VECTOR)  )
    {
            refscreen->projectiles[dat1->vectro_poz]->to_delete = true;
    }
    else if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR &&
              dat2->which_vector == ScreenGame::DETECTOR_VECTOR) )
    {
            refscreen->entities[dat1->vectro_poz]->hp -= refscreen->detectors[dat2->vectro_poz]->hp_change;
            refscreen->entities[dat1->vectro_poz]->speed_change = refscreen->detectors[dat2->vectro_poz]->speed_change;

    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR &&
             dat1->which_vector == ScreenGame::DETECTOR_VECTOR)  )
    {
            refscreen->entities[dat2->vectro_poz]->hp -= refscreen->detectors[dat1->vectro_poz]->hp_change;
            refscreen->entities[dat2->vectro_poz]->speed_change = refscreen->detectors[dat1->vectro_poz]->speed_change;
    }
    /*else if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR  &&
              dat2->which_vector == ScreenGame::WALLS_VECTOR))
    {
        if(refscreen->entities[dat1->vectro_poz]->type != ScreenGame::PLAYER)
        {
            refscreen->entities[dat1->vectro_poz]->body->SetLinearVelocity(b2Vec2(0, 0));
        }
    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR  &&
             dat1->which_vector == ScreenGame::WALLS_VECTOR))
    {
        if(refscreen->entities[dat2->vectro_poz]->type != ScreenGame::PLAYER)
        {
            refscreen->entities[dat2->vectro_poz]->body->SetLinearVelocity(b2Vec2(0, 0));
        }
    }*/

}

void CollisionHandler::EndContact(b2Contact* contact)
{
    universal_data *dat1, *dat2;

    dat1 = (universal_data*)contact->GetFixtureA()->GetBody()->GetUserData();
    dat2 = (universal_data*)contact->GetFixtureB()->GetBody()->GetUserData();

    if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR &&
        dat2->which_vector == ScreenGame::DETECTOR_VECTOR) )
    {
            refscreen->entities[dat1->vectro_poz]->speed_change = 1.0;

    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR &&
             dat1->which_vector == ScreenGame::DETECTOR_VECTOR)  )
    {
            refscreen->entities[dat2->vectro_poz]->speed_change = 1.0;
    }
}


float32 RayCastCallBack::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
    universal_data *dat1;
    dat1 = (universal_data*)fixture->GetBody()->GetUserData();

    if(dat1->which_vector == ScreenGame::WALLS_VECTOR && fraction <= 1 )
    {
        refscreen->dont_move = true;
    }
    return 1;
}
