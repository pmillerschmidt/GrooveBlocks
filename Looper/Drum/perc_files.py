import pygame
from pygame import mixer

class mix:
    pygame.mixer.pre_init(22050, -16, 2, 256)#22050=default frequecy,-16=size(16 signed bits per audio sample
    pygame.mixer.init()                      #2-->stereo sound, 512=buffersize
    pygame.init()
    #set volume 
    pygame.mixer.music.set_volume(1.0)
    
    #initialize channels in the mixer
    channels = [pygame.mixer.Channel(0), pygame.mixer.Channel(1),
                pygame.mixer.Channel(2), pygame.mixer.Channel(3), 
                pygame.mixer.Channel(4)]

    
    #sounds dictionary
    # Accessing sounds: 
#     each combination will have a 3-digit code. That code comes from
#     the MIDI, effect and inst inputs. Each of those resistor values
#     will be sorted into a single digit value from 0-10 with the sort 
#     function. Then they will be concatanated into a 3-digit code. 
#     000 representing the default. There will be a dictionary with 
#     these codes that will inform the Raspi which .wav to play.

#       First digit is instrument, then pattern, then effect.
    #FOR MAC
    # sounds = {
    #     "100" : pygame.mixer.Sound("/Users/paulmiller-schmidt/Documents/GitHub/Boom-Blox/Looper/Drum/drum_audio/kick.ogg"),
    #     "200" : pygame.mixer.Sound("/Users/paulmiller-schmidt/Documents/GitHub/Boom-Blox/Looper/Drum/drum_audio/open_hat.wav"),
    #     "300" : pygame.mixer.Sound("/Users/paulmiller-schmidt/Documents/GitHub/Boom-Blox/Looper/Drum/drum_audio/Snare_Hollow.ogg")

    # }

    sounds = {
        "100" : pygame.mixer.Sound("drum_audio/low_perc.ogg"),
        "200" : pygame.mixer.Sound("drum_audio/mid_perc.ogg"),
        "300" : pygame.mixer.Sound("drum_audio/shaker.ogg"),
        "400" : pygame.mixer.Sound("drum_audio/high_perc.ogg"), 
        "500" : pygame.mixer.Sound("drum_audio/high_metro.ogg"),  
        #"600" : pygame.mixer.Sound("drum_audio/low_metro.ogg")

    }



    #this play should be used in looper lounge
    def play(self, sound_code, channel_number): 
            """Play arg1 sound in arg2 channel           
            ex) mix.play(1, 0) will play sound 1 in channel 0"""
            #make code readable by dict
            
            code = "'" + sound_code + "'"
            if (code in self.sounds):#there is no audio file in this position, so do nothing
                print("sound not in dictionary")
            else:#play specified sound in specified channel
                # print(type(code))
                # print(self.sounds.get(code))
                self.channels[channel_number].play(self.sounds[sound_code])

    #this play method should used in the step sequencer
    def play_step(self, sound_code, channel_number): 
            """Play sound_code sound in channel_number channel           
            ex) mix.play(1, 0) will play sound 1 in channel 0"""
            #make code readable by dict
            
            code = "'" + sound_code + "'"
            if sound_code == '000':
                return
            else:#play specified sound in specified channel
                # print(type(code))
                # print(self.sounds.get(code))
                self.channels[channel_number].play(self.sounds[sound_code])            


    def update_channel_volume(self, channel_number, volume):
        """sets the volume of a specific chanel"""     
        self.channels[channel_number].set_volume(volume)
            
            
    def cleanup(self):#need to use an exception handler!!!!! in driver
        """called at end of driver"""
        pygame.quit()