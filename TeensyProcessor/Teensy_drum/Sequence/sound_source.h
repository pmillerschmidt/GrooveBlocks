#ifndef __SOUND_SOURCE_H__
#define __SOUND_SOURCE_H__

#include <Audio.h>

class SoundSource {
  private:
    char *bank_name_;
    AudioMixer4         *p_mix_l_;
    AudioMixer4         *p_mix_r_;
    unsigned int         ch_l_;
    unsigned int         ch_r_;
    unsigned long        play_start_;
    unsigned long        duration_;


  public:

    SoundSource(AudioMixer4 *p_mix_l,
                AudioMixer4 *p_mix_r,
                unsigned int ch_l,
                unsigned int ch_r
    ) : p_mix_l_(p_mix_l), p_mix_r_(p_mix_r), ch_l_(ch_l), ch_r_(ch_r) {};

    
};

class PCMSoundSource : public SoundSource {
  public:
    PCMSoundSource( AudioPlaySdWav         *p_pcm,
                    AudioMixer4            *p_mix_l,
                    AudioMixer4            *p_mix_r,
                    unsigned int           ch_l,
                    unsigned int           ch_r
    ) : SoundSource(p_mix_l, p_mix_r, ch_l, ch_r), p_source_(p_pcm) {};

  private:
    AudioPlaySdWav  *p_source_;
};


#endif // __SOUND_SOURCE_H__
