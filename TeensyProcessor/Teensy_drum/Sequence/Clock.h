#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock {
    private: 
        int BPM;
        int Step;
        int duration;
        int total_time;
        int max_steps;
        int init_time;
        int elapsed_time;
        int step_interval;
        
    public: 
        Clock(int BPM, int max_steps, int note_duration);
        int Check();
        int getBPM();
        int getStep();
        void start_clock();
        void pause_clock();
        void stop_clock();
        bool change();
        

};
#endif 
