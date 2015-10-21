#include "AudioHandler.h"

AudioHandler::AudioHandler(int max_souds_at_same_time)
{
    al_reserve_samples(max_souds_at_same_time); //alredy creats mixer
    //mixer = al_get_default_mixer();
}

AudioHandler::~AudioHandler()
{
   /*if(mixer != nullptr)
   {
        al_detach_mixer(mixer);
        al_destroy_mixer(mixer);
   }*/
}
void AudioHandler::Stop_all_samples()
{
     al_stop_samples();
}

ALLEGRO_SAMPLE_ID AudioHandler::Play_sample(ALLEGRO_SAMPLE **smlp, ALLEGRO_PLAYMODE aplmod = ALLEGRO_PLAYMODE_ONCE)
{
    ALLEGRO_SAMPLE_ID ret_id;

    if(global::audio == false)
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
     al_stop_sample(&smlp_id);

     return;
}

void AudioHandler::Stop_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst)
{
    al_stop_sample_instance( *smlpinst);
    al_detach_sample_instance( *smlpinst);

    return;
}

void AudioHandler::Play_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst, ALLEGRO_PLAYMODE aplmod = ALLEGRO_PLAYMODE_ONCE)
{
    al_set_sample_instance_playmode(*smlpinst, aplmod);
    al_attach_sample_instance_to_mixer(*smlpinst, al_get_default_mixer());
    al_play_sample_instance(*smlpinst);

    return;
}

void AudioHandler::Mute_sample_instances(bool true_or_false)
{
    al_set_mixer_playing(al_get_default_mixer(), 1 - true_or_false);

    return;
}

bool AudioHandler::Stop_sample_instances()
{
    return al_restore_default_mixer();
}
