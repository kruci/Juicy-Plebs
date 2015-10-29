#include "CollisionHandler.h"

void CollisionHandler::BeginContact(b2Contact* contact)
{
    universal_data *dat1, *dat2;

    dat1 = (universal_data*)contact->GetFixtureA()->GetBody()->GetUserData();
    dat2 = (universal_data*)contact->GetFixtureB()->GetBody()->GetUserData();

    if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR  &&
         dat2->which_vector == ScreenGame::ENTITY_VECTOR) )
    {
        if( (refscreen->entities[dat1->vectro_poz]->type == ScreenGame::PLAYER ||
             refscreen->entities[dat2->vectro_poz]->type == ScreenGame::PLAYER) )
        {
            refscreen->dead = true;
            global::audio_player->Play_sample_instance(&refscreen->sounds[ScreenGame::sound_DEAD]->instance, ALLEGRO_PLAYMODE_ONCE);
        }
    }
    else if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR &&
              dat2->which_vector == ScreenGame::ITEMS_VECTOR) )
    {
        if(refscreen->entities[dat1->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->mItems[dat2->vectro_poz]->to_delete = true;
            refscreen->abilities[refscreen->mItems[dat2->vectro_poz]->type]->unlocked = true;
            global::save->Set_item(refscreen->mItems[dat2->vectro_poz]->type);
        }
    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR &&
             dat1->which_vector == ScreenGame::ITEMS_VECTOR)  )
    {
        if(refscreen->entities[dat2->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->mItems[dat1->vectro_poz]->to_delete = true;
            refscreen->abilities[refscreen->mItems[dat1->vectro_poz]->type]->unlocked = true;
            global::save->Set_item(refscreen->mItems[dat1->vectro_poz]->type);
        }
    }
    else if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR &&
              dat2->which_vector == ScreenGame::PROJECTILES_VECTOR) )
    {
        if(refscreen->entities[dat1->vectro_poz]->type != ScreenGame::PLAYER)
        {
            refscreen->projectiles[dat2->vectro_poz]->to_delete = true;
            refscreen->entities[dat1->vectro_poz]->hp -= refscreen->projectiles[dat2->vectro_poz]->damage;
        }
    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR &&
             dat1->which_vector == ScreenGame::PROJECTILES_VECTOR)  )
    {
        if(refscreen->entities[dat2->vectro_poz]->type != ScreenGame::PLAYER)
        {
            refscreen->projectiles[dat1->vectro_poz]->to_delete = true;
            refscreen->entities[dat2->vectro_poz]->hp -= refscreen->projectiles[dat1->vectro_poz]->damage;
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
    /*else if( (dat1->which_vector == ScreenGame::ENTITY_VECTOR  &&
              dat2->which_vector == ScreenGame::WALLS_VECTOR) && refscreen->just_tp == true)
    {
        if(refscreen->entities[dat1->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->tp_fail = true;
        }
    }
    else if( (dat2->which_vector == ScreenGame::ENTITY_VECTOR  &&
             dat1->which_vector == ScreenGame::WALLS_VECTOR) && refscreen->just_tp == true)
    {
        if(refscreen->entities[dat2->vectro_poz]->type == ScreenGame::PLAYER)
        {
            refscreen->tp_fail = true;
        }
    }*/

}

void CollisionHandler::EndContact(b2Contact* contact)
{
    universal_data *dat1, *dat2;
}
