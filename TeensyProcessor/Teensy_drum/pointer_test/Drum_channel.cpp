#include "Drum_channel.h"
#include <Audio.h>

Drum_channel::Drum_channel(const char *inst_name, int max_steps) {
    this->inst_name = inst_name;
    this->max_steps = max_steps;


}

Drum_channel::Drum_channel() {
    this->inst_name = NULL;
    this->max_steps = 0;


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

int Drum_channel::get(int index) {
  return steps[index];
}

//AudioPlaySdWav Drum_channel::getSource() {
//  return *source_;
//}
