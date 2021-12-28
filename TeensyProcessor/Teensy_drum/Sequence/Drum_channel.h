#include <Audio.h>
#include <SD.h>
#include "Arduino.h"

#ifndef Drum_channel_h
#define Drum_channel_h



class Drum_channel {
    private:
        const char *inst_name;
        int max_steps;
        int steps [32];
        AudioPlaySdWav *source_;
        

    public:
        Drum_channel(const char *inst_name, int max_steps, AudioPlaySdWav *_source_);
        const char* getSound();
        int On(int index);
        void set(int index, int val);
        void Trigger();
        AudioPlaySdWav getPath();
};

#endif
