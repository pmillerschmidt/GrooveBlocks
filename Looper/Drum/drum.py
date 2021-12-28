"""Audio Looper driver method"""
import time
# from gpiozero import MCP3008, PWMLED
from drum_files import mix 
from looper import Looper
import math

        
def play_region(instr, channel_number):
    ##play loop from channel number 
    mixer.play(instr.get_loop(channel_number), channel_number)


def start_loop(instr):
    #initial time
    start_time = time.time()
    length = 16
    #set sequences
    kick = [1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0]
    open_hat = [1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0]
    snare = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    snare_hits = []
    instruments = [kick, open_hat, snare]

    #set loops, THIS IS FUCKING WEIRD 
    instr.set_loop(0, '100')
    instr.set_loop(1, '200')
    instr.set_loop(2, '300')
    instr.set_loop(3, '400')

    #set last time and hit time
    last = -1
    hit_time = 0

    #vartiables  for button and inst
    recording = 0
    inst_state = 0
    last_state = -3

    while True:
        
        #start really keeping track of time 
        raw_time = time.time()       
        elapsed_time = raw_time - start_time
        #*4 is to make floor_time 240 BPM instead of 60, give it 16 beats
        floor_time = math.floor(elapsed_time * 4)
        #roll over if it goes over time
        if (floor_time >= float(length)):
            start_time = time.time()
            elapsed_time = raw_time - start_time
            floor_time = math.floor(elapsed_time)
            hit_time = 0
            # for x in range(len(snare)):
            #     print(snare[x])

        #when you are at an interval, update which instruments are playing
        if (floor_time != last):
            last = floor_time
            # for x in instruments:
            #     if(x[last] == 1):
            #         play_region(instr, instruments.index(x))
            #         print(instruments.index(x))
           
            print(kick[last] == 1)
            
            if (kick[last] == 1):
                play_region(instr, 2)
            if (snare[last] == 1):
                 play_region(instr, 1)
            if (open_hat[last] == 1):
                play_region(instr, 0)
            


        


        


#settig up channel data
TEMPO = 5    #how many instruments
CHANNELS = 4
looper = Looper(TEMPO, CHANNELS)#5 is the tempo, 2 channels, 8 steps
mixer = mix()
mixer.update_channel_volume(0, 1.0)
#start loop on sequencer

start_loop(looper)

       

            
    
        
        
        
    

