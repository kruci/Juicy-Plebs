#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include "global.h"

class AudioHandler
{
private:
public:
    ALLEGRO_MIXER *mixer = nullptr;

    std::vector<ALLEGRO_SAMPLE_INSTANCE*> global_sounds;

    AudioHandler(int max_souds_at_same_time);
    virtual ~AudioHandler();

    /**pass &var of pointer to functions with **arg  */
    /**use only _instance functions*/

    //function for samples
    void Stop_all_samples();
    ALLEGRO_SAMPLE_ID Play_sample(ALLEGRO_SAMPLE **smlp, ALLEGRO_PLAYMODE aplmod);
    void Stop_sample(ALLEGRO_SAMPLE_ID smlp_id);

    //functions for sample_instances
    void Stop_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst);
    void Mute_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst);
    void Play_sample_instance(ALLEGRO_SAMPLE_INSTANCE **smlpinst, ALLEGRO_PLAYMODE aplmod);
    void Mute_sample_instances(bool true_or_false);
    bool Stop_sample_instances();
};

#endif // AUDIOHANDLER_H
