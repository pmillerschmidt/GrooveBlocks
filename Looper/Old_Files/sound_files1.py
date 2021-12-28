import pygame
import subprocess
from pygame import mixer

class mix:
    pygame.init()
    pygame.mixer.pre_init(44100, -16, 2, 512)
    pygame.mixer.init()

    channels = [pygame.mixer.Channel(0), pygame.mixer.Channel(1)]
    sounds = ["Track1.wav", "Track2.wav", "drums.wav", "Track3.wav","2_SECOND_PIANO.wav"]
    
    
    def play(self, sound_number, channel_number):
        """Play arg1 sound in arg2 channel           
        ex) mix.play(1, 0) will play sound 1 in channel 0"""
        
        if sound_number == 0:#there is no audio file in this position
            print("no sound at this position")
            return
        else:
            #self.channels[channel_number].play(self.sounds[sound_number - 1])
            subprocess.call('aplay -fdat ' + self.sounds[sound_number - 1], shell=True)
    
    
    def update_channel_volume(self, channel_number, volume):
        """sets the volume of a specific channel"""
        
        self.channels[channel_number].set_volume(volume)
        
        
    def set_silent_loop(self):
        """this method will create a loop with nothing but silent noise, this
        loop should be foregrounded so that it creates the tempo of the loop"""
        
        return
