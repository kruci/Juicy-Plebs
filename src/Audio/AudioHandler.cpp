//R.K.
#include "AudioHandler.h"

AudioHandler::AudioHandler(int max_souds_at_same_time)
{
    if(global::sound_card != false)
    {
        al_reserve_samples(max_souds_at_same_time); //alredy creats mixer
    }
    //mixer = al_get_default_mixer();
}

AudioHandler::~AudioHandler()
{
   /*if(mixer != nullptr)
   {
        al_detach_mixer(mixer);
        al_destroy_mixer(mixer);
   }*/

   /*for(int a = 0; a < global_sounds.size();a++)
   {
        al_stop_sample_instance( global_sounds[a]);
        al_detach_sample_instance( global_sounds[a]);
   }*/
   global_sounds.clear();
}
void AudioHandler::Stop_all_samples()
{
     if(global::sound_card != false)
     {
         al_stop_samples();
     }

}

ALLEGRO_SAMPLE_ID AudioHandler::Play_sample(ALLEGRO_SAMPLE **smlp, ALLEGRO_PLAYMODE aplmod)
{
    ALLEGRO_SAMPLE_ID ret_id;

    if(global::audio == false || global::sound_card == false)
    {
        ret_id._id = 999;
        ret_id._index = 999;
        return ret_id;
    }

    al_play_sample(*smlp, 1, ALLEGRO_AUDIO_PAN_NONE, 1, aplmod, &ret_id);

    return ret_id;
}

void AudioHandler::Stop_sample(ALLEGRO_SAMPLE_ID smlp_id)
{
     if(global::sound_card == false)
        return;

     al_stop_sample(&smlp_id);

     return;
}

void AudioHandler::Stop_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst)
{
     if(global::sound_card == false)
        return;

    al_stop_sample_instance( *smlpinst);
    al_detach_sample_instance( *smlpinst);

    return;
}

void AudioHandler::Mute_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst)
{
     if(global::sound_card == false)
        return;

    al_set_sample_instance_gain(*smlpinst, 0.0f);

    return;
}

void AudioHandler::Play_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst, ALLEGRO_PLAYMODE aplmod )
{
     if(global::sound_card == false)
        return;

    al_set_sample_instance_playmode(*smlpinst, aplmod);
    al_attach_sample_instance_to_mixer(*smlpinst, al_get_default_mixer());
    al_play_sample_instance(*smlpinst);

    return;
}

void AudioHandler::Play_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst, float gain , ALLEGRO_PLAYMODE aplmod )
{
    if(global::sound_card == false)
        return;

    al_set_sample_instance_playmode(*smlpinst, aplmod);
    al_attach_sample_instance_to_mixer(*smlpinst, al_get_default_mixer());
    al_set_sample_instance_gain(*smlpinst, gain);
    al_play_sample_instance(*smlpinst);

    return;
}

void AudioHandler::Mute_sample_instances(bool true_or_false)
{
     if(global::sound_card == false)
        return;

    //al_set_mixer_playing(al_get_default_mixer(), 1 - true_or_false);
    al_set_mixer_gain(al_get_default_mixer(), 1 - (int)true_or_false);

    return;
}

bool AudioHandler::Stop_sample_instances()
{
     if(global::sound_card == false)
        return true;

    return al_restore_default_mixer();
}
