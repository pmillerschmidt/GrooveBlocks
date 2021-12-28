#include "Sequencer.h"
#include "Drum_channel.h"
#include <math.h>

Sequencer::Sequencer(int BPM, int max_steps, int note_duration, int num_channels) {
    //BPM, loop length and note duration
    this->BPM = BPM;
    this->max_steps = max_steps;
    this->duration = note_duration;
    this->num_channels = num_channels;
    this->Step = -1;
    //time is is millis
    this->init_time = 0;
    this->step_interval = (60000 / BPM) / duration;
    this->total_time = step_interval * max_steps;
}

void Sequencer::start_clock() {
  init_time = 0;
  this->init_time = millis();
  this->elapsed_time = 0;
  
}

void Sequencer::stop_clock() {
  this->elapsed_time = 0;
  this->init_time = 0;
  this->Step = 0;
}


int Sequencer::getBPM() {
    return this->step_interval;
}

int Sequencer::getChannels() {
    return this->num_channels;
}

int Sequencer::getStep() {
    //get the time and check if 
    Step = floor(this->Check() / this->step_interval);
    if (Step >= max_steps) {
      Step = 0;
      stop_clock();
      start_clock();    
    }
    
    return Step;
}

int Sequencer::closest_step() {
  if (Step >= max_steps) {
      Step = 0;
      start_clock();
    }
  //find the closest step
  Step = this->Check() / this->step_interval;
  //if the diff between time and last is more than half of step interval, step is next step
  if ((Check() - (Step*step_interval)) > (step_interval / 2)) {
    Step++;
  }
  return Step;
  
}
int Sequencer::Check() {
  this->elapsed_time = millis() - this->init_time;
  
  return this->elapsed_time;
}

int Sequencer::Check_init() {
  return this->init_time;
}

bool Sequencer::change() {
  return (Step != getStep());

}

void Sequencer::add_instrument(Drum_channel* new_channel) {
  *channels[curr_channel] = *new_channel;
  curr_channel++;
}

Drum_channel* Sequencer::get_instrument(int index) {
  return channels[index];
}

//void Sequencer::set_instStep(int inst, int Step) {
//  channels[inst].set(Step, 1);
//}
bool Sequencer::inst_On(int inst) {
  Drum_channel drum = *get_instrument(inst);
  return (drum.On(getStep()) == 1);
  
}

const char* Sequencer::getSound(int inst) {
  Drum_channel drum = *get_instrument(inst);
  return drum.getSound();
}
