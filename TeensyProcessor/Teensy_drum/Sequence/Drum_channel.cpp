#include "Drum_channel.h"
#include <Audio.h>

Drum_channel::Drum_channel(const char *inst_name, int max_steps, AudioPlaySdWav *_source_) {
    this->inst_name = inst_name;
    this->max_steps = max_steps;
    *source_ = *_source_;


}

const char* Drum_channel::getSound() {
    return this->inst_name;
}

int Drum_channel::On(int index) {
    return this->steps[index];
}


void Drum_channel::set(int index, int val) {
  this->steps[index] = val;
}

AudioPlaySdWav Drum_channel::getPath() {
  return *source_;
}

void Drum_channel::Trigger() {
  getPath().play(getSound());

}
