"""audio loop driver method"""
import time
from gpiozero import MCP3008, PWMLED
from channel_structure import channels
from sound_files import mix

#setting up volume knobs
pot0 = MCP3008(0)#channel 0 of the MPC3008 pins
pot1 = MCP3008(1)#MCP3008 channel 1

#settig up channel data
sequencer = channels(5)#5 is the tempo
sequencer.scan_tracks#not implemented yet
print(sequencer.audio_file_struct[0])
print(sequencer.audio_file_struct[1])
tempo = sequencer.tempo

mixer = mix()

#Clock = pygame.time.Clock
#clock = Clock()

def play_region(region_number):
    mixer.play(sequencer.get_audio_num(0, region_number), 0)
    mixer.play(sequencer.get_audio_num(1, region_number), 1)

    
mixer.update_channel_volume(0, pot0.value)#setup the channel volumes before audio playback
mixer.update_channel_volume(1, pot1.value)
while True:
    counter = 0
    while counter < 8:#16 second loop
        play_region(counter)
        counter1 = 0
        while counter1 < 4:#2 second loop, 
            time.sleep(0.5)
            mixer.update_channel_volume(0, pot0.value)
            mixer.update_channel_volume(1, pot1.value)
            counter1+=1
        counter+=1
        #plays audio file in channel 0 and channel 2
        
       
       

    
        
        
        
    