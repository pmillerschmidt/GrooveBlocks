import pygame
from pygame import mixer
from gpiozero import MCP3008

class mix:
    pygame.mixer.pre_init(22050, -16, 2, 256)#22050=default frequecy,-16=size(16 signed bits per audio sample
    pygame.mixer.init()                      #2-->stereo sound, 512=buffersize
    pygame.init()
    #set volume 
    pygame.mixer.music.set_volume(1.0)
    
    #initialize channels in the mixer
    channels = [pygame.mixer.Channel(0), pygame.mixer.Channel(1),
                pygame.mixer.Channel(2), pygame.mixer.Channel(3)]

    pots = [MCP3008(0), MCP3008(1), MCP3008(2), MCP3008(3)]

    
    #sounds dictionary
    # Accessing sounds: 
#     each combination will have a 3-digit code. That code comes from
#     the MIDI, effect and inst inputs. Each of those resistor values
#     will be sorted into a single digit value from 0-10 with the sort 
#     function. Then they will be concatanated into a 3-digit code. 
#     000 representing the default. There will be a dictionary with 
#     these codes that will inform the Raspi which .wav to play.

#       First digit is instrument, then pattern, then effect.

    sounds = {
        "100" : pygame.mixer.Sound("Audio_Files/grandPiano.wav"),
        "120" : pygame.mixer.Sound("Audio_Files/grandPiano_arp.wav"),
        "123" : pygame.mixer.Sound("Audio_Files/grandPiano_reverbArp.wav"),
        "213" : pygame.mixer.Sound("Audio_Files/juno.wav"),
        "210" : pygame.mixer.Sound("Audio_Files/juno_arp.wav"),
        "200" : pygame.mixer.Sound("Audio_Files/juno_arpReverb.wav"),
        "300" : pygame.mixer.Sound("Audio_Files/triumph.wav"),
        #"310" : pygame.mixer.Sound("Audio_Files/triumph_arp.wav"),
        "312" : pygame.mixer.Sound("Audio_Files/triumph_reverbArp.wav"),
        "000" : pygame.mixer.Sound("Audio_Files/Choir.wav"),
        "010" : pygame.mixer.Sound("Audio_Files/drums.wav")
        # "222" : pygame.mixer.Sound("Looper/Audio_Files/Track3.wav"),
        # "002" : pygame.mixer.Sound("Looper/Audio_Files/2_SECOND_PIANO.wav"),
        # "020" : pygame.mixer.Sound("Looper/Audio_Files/Track1.wav"),
        #"333" : pygame.mixer.Sound("Audio_Files/techno.wav"),
        #"555" : pygame.mixer.Sound("Audio_Files/keys.wav"),
        #"030" : pygame.mixer.Sound("Audio_Files/highs.wav"),
        #"666" : pygame.mixer.Sound("Audio_Files/sax.wav") 
        
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


    def update_channel_volume(self):
        """sets the volume of a all chanells to values of pots"""  
        for i in range(0,4):
            self.channels[i].set_volume(self.pots[i].value)
            
            
    def cleanup(self):#need to use an exception handler!!!!! in driver
        """called at end of driver"""
        pygame.quit()