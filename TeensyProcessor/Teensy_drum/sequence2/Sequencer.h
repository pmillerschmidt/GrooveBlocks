#ifndef Sequencer_h
#define Sequencer_h

#include "Arduino.h"
#include "Drum_channel.h"
#include <Audio.h>

class Sequencer {
    private: 
        //Timing 
        int total_time;       
        int init_time;
        int elapsed_time;      
        int duration; 
        bool first;
        
        //BPM, steps
        int BPM;
        int Step; 
        int max_steps;       
        int step_interval;

        //Channels
        int num_channels;
        Drum_channel *channels;   
        int curr_channel;
        
    public: 
        Sequencer(int BPM, int max_steps, int note_duration, int num_channels);
        int Check();
        int Check_init();
        int getBPM();
        int getChannels();
        int getStep();    
        int getStep_interval() {return step_interval;}
        int closest_step();
        void start_clock();
        void pause_clock();
        void stop_clock();
        bool change();
        
        bool inst_On(int inst);
        const char* getSound(int inst);
        void add_instrument(Drum_channel* new_channel);
        Drum_channel get_instrument(int index);
        void set_instStep(int inst, int Step);
        

};
#endif 
