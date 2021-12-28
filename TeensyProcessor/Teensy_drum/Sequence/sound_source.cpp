
#include "sound_source.h"


// GUItool: begin automatically generated code
AudioPlaySdWav           pcm1;     //xy=525.2500152587891,471.75001525878906
AudioPlaySdWav           pcm2;     //xy=525.2500152587891,520.7500152587891
AudioPlaySdWav           pcm3;     //xy=525.2500152587891,566.7500152587891
AudioPlaySdWav           pcm4;     //xy=524.5833511352539,617.0833683013916

AudioMixer4              mix_pcm_r;         //xy=748.5833511352539,569.3055782318115
AudioMixer4              mix_pcm_l;         //xy=749.8055381774902,495.0833568572998
AudioMixer4              mix_out_l;         //xy=1011.4443969726562,595.7777404785156
AudioMixer4              mix_out_r;         //xy=1012.888843536377,678.3333406448364
AudioOutputI2S           i2s1;           //xy=1190.0000076293945,691.2222490310669

AudioConnection          patchCord7(pcm1, 0, mix_pcm_l, 0);
AudioConnection          patchCord8(pcm1, 1, mix_pcm_r, 0);
AudioConnection          patchCord9(pcm2, 0, mix_pcm_l, 1);
AudioConnection          patchCord10(pcm2, 1, mix_pcm_r, 1);
AudioConnection          patchCord11(pcm3, 0, mix_pcm_l, 2);
AudioConnection          patchCord12(pcm3, 1, mix_pcm_r, 2);
AudioConnection          patchCord5(pcm4, 0, mix_pcm_l, 3);
AudioConnection          patchCord6(pcm4, 1, mix_pcm_r, 3);
AudioConnection          patchCord21(mix_pcm_r, 0, mix_out_r, 0);
AudioConnection          patchCord22(mix_pcm_l, 0, mix_out_l, 0);
AudioConnection          patchCord26(mix_out_l, 0, i2s1, 0);
AudioConnection          patchCord28(mix_out_r, 0, i2s1, 1);

PCMSoundSource pcm_sources[] = {PCMSoundSource(&pcm1, &mix_pcm_l, &mix_pcm_r, 0, 0),
                                PCMSoundSource(&pcm2, &mix_pcm_l, &mix_pcm_r, 1, 1),
                                PCMSoundSource(&pcm3, &mix_pcm_l, &mix_pcm_r, 2, 2),
                                PCMSoundSource(&pcm4, &mix_pcm_l, &mix_pcm_r, 3, 3)};



// void PCMSoundSource::playNote(uint8_t note, uint8_t octave, uint8_t vol, PCMInstrument *p_inst) {
//   p_mix_l_->gain(ch_l_, mix_l_gain_from_pan(p_inst->getPan()));
//   p_mix_r_->gain(ch_r_, mix_r_gain_from_pan(p_inst->getPan()));

//   if (p_inst->getPath(note)) {
//     // Stop any existing, already playing sound on this source
//     p_pcm_->stop();
//     play_start_ = millis();

//     p_pcm_->play(p_inst->getPath(note));
//     duration_ = p_pcm_->lengthMillis();      
//   }
// }

// boolean PCMSoundSource::isPlaying(void) {
//   return p_pcm_->isPlaying();
// }
