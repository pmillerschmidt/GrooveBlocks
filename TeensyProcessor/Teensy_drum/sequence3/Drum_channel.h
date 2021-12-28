#include <Audio.h>
#include <SD.h>
#include "Arduino.h"
#include <Audio.h>

#ifndef Drum_channel_h
#define Drum_channel_h



class Drum_channel {
    private:
        const char *inst_name;
        int max_steps;
        int* steps;
        

    public:
        
        
        Drum_channel(const char *inst_name, int max_steps);
        void Create(const char *inst_name, int max_steps);
        Drum_channel();
        const char* getSound();
        int On(int index);
        void set(int index, int val);
        int get(int index);
        
        void set_full(int arr [32]) {
          for (int x = 0; x<32; x++) {
            this->steps[x] = arr[x];
          }
        }
};

#endif
