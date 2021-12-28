"""FRAMING: 
    Few different functions for different mode. Play mode, record mode, idle mode. 
    Different objects for everyhting. 

"""
import time
import smbus2
# from gpiozero import MCP3008, PWMLED
from drum_files import mix 
from looper import Looper
import math


# set up the bus
bus = smbus2.SMBus(1)
address = 0x04

def readBus():
    data = bus.read_i2c_block_data(address, 0, 4)
    #if there is an error, return last 
    if (data == [255,255,255,255]):
        return [0,0,0,0]
    else:
        return data

def writeBus(value):
    bus.write_byte(address, value)
    # bus.write_byte_data(address, 0, value)
    return -1
        
def play_region(instr, channel_number):
    ##play loop from channel number 
    mixer.play(instr.get_loop(channel_number), channel_number)

def empty(arr):
    for x in range(len(arr)):
        arr[x] = 0

def play_loop(instr):
    #initial time
    start_time = time.time()
    length = 16   

    #set last time and hit time
    last = -1
    hit_time = 0

    #vartiables  for button and inst
    recording = 0
    play = 0
    #to measure how far from the loop starting we are
    #important for first instr hit and noise checking   
    play_time = time.time()
    inst_state = 0
    last_state = readBus()[1] - 1

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

            #reset array we are recording 
            if (recording == 1):              
                empty(instrument_dict[inst_state]) 
            # for x in range(len(snare)):
            #     print(snare[x])

        #read bus t
        output = readBus()

        # #set vars
        hit = output[0]
        inst_state = output[1] - 1 
        recording = output[2]
        play = output[3]
        #if play is off, stop and its been a lil, if its the first time and its been more
        #than a second or its not the first time and play is pressed, STOP the loop
        if (play == 1 and (raw_time - play_time > .5)):
            return time.time()
            break

        # #inst_state
        if (inst_state != last_state and (raw_time - play_time > .1)):
            last_state = inst_state
            play_region(instr, inst_state)

        #if its high, play snare, wait a little before checking again
        if (hit == 1 and (elapsed_time - hit_time) > 0.1):
            play_region(instr,inst_state)  
            hit_time = elapsed_time

            # #if we are recording, clear array and add to it 
              # if (recording == 1):                   
            #     if round(hit_time * 4) != length:
            #         instrument_dict[inst_state][round(hit_time * 4)] = 1
            


        #when you are at an interval, update which instruments are playing
        if (floor_time != last):
            last = floor_time
        #     for x in instruments:
        #         if(x[last] == 1):
        #             play_region(instr, instruments.index(x))
        #             print(instruments.index(x))
           

            if (kick[last] == 1):
                play_region(looper, 0)
            if (open_hat[last] == 1):
                play_region(looper, 1)  
            if (snare[last] == 1):
                 play_region(looper, 2)
            if (closed_hat[last] == 1):
                play_region(looper, 3)

def record_loop(instr):

    hit_time = -1

    #play metronome
    for x in range(4):
        play_region(instr, 4)
        time.sleep(0.5)

    #initial time
    start_time = time.time()
    length = 16   

    #set last time and hit time
    last = -1

    #vartiables  for button and inst
    recording = 0
    play = 0
    #to measure how far from the loop starting we are
    #important for first instr hit and noise checking   
    record_time = time.time()
    inst_state = 0



    #empty the array we are working with 
    empty(instrument_dict[readBus()[1] - 1]) 
    last_state = readBus()[1] - 1

    while True:
               

        #start really keeping track of time 
        raw_time = time.time()       
        elapsed_time = raw_time - start_time
        #*4 is to make floor_time 240 BPM instead of 60, give it 16 beats
        floor_time = math.floor(elapsed_time * 4)
        #roll over if it goes over time
        if (floor_time >= float(length)):

            #print(instrument_dict[inst_state])
            start_time = time.time()
            elapsed_time = raw_time - start_time
            floor_time = math.floor(elapsed_time)
            hit_time = -0.1


        #read bus t
        output = readBus()
        # #set vars
        hit = output[0]
        inst_state = output[1] - 1 
        recording = output[2]
        play = output[3]
        #if play is off, stop and its been a lil, if its the first time and its been more
        #than a second or its not the first time and play is pressed, STOP the loop
        
        if (hit == 1 and (elapsed_time - hit_time) > 0.08):
            play_region(instr,inst_state)  
            hit_time = elapsed_time

            # #if we are recording, clear array and add to it                  
            if round(hit_time * 4) != length:
                instrument_dict[inst_state][round(hit_time * 4)] = 1
            

        if (recording == 0 and (raw_time -record_time > .5)):
            return time.time()
            break

        # #inst_state
        if (inst_state != last_state and (raw_time - record_time > .1)):
            last_state = inst_state
            play_region(instr, inst_state)

        #if its high, play snare, wait a little before checking again
        

        #when you are at an interval, update which instruments are playing
        if (floor_time != last):           
            last = floor_time
            #play metro
            if (last % 2 == 0):
                play_region(instr, 4)
           
           #if any of the hits are true, hit em 
            if (kick[last] == 1):
                play_region(looper, 0)
            if (open_hat[last] == 1):
                play_region(looper, 1)  
            if (snare[last] == 1):
                 play_region(looper, 2)
            if (closed_hat[last] == 1):
                play_region(looper, 3)
                

def idle(instr):
    last = -1
    wait_time = time.time()
    hit_wait = time.time()
    hit_time = 0

    while True:

        
        elapse = time.time() - wait_time
        hit_elapse = time.time() - hit_wait
        #settig up channel data    
        #read bus t
        output = readBus()
        # #set vars
        hit = output[0]
        inst = output[1] - 1 
        recording = output[2]
        play = output[3]

        if (inst != last and (elapse > .1)):
                wait_time = time.time()
                last = inst              
                play_region(instr, inst)

        #if play is triggered start loop on sequencer
        if (play == 1 and elapse > 0.5):
            wait_time = play_loop(instr)
        
        if (recording == 1):
            record_loop(looper)    

        #if its high, play snare, wait a little before checking again
        if (hit == 1 and hit_elapse > 0.1):
            #print(last)
            play_region(instr,last) 
            hit_wait = time.time() 



    
# def record(instr):

#BOOT UP STUFF, THIS SHOULD BE IN ITS OWN FILE 
#set sequences

TEMPO = 5    #how many instruments
CHANNELS = 5
looper = Looper(TEMPO, CHANNELS)#5 is the tempo, 2 channels, 8 steps
mixer = mix()
mixer.update_channel_volume(0, 1.0)


# kick =       [1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0]
# open_hat =   [1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0]
# snare =      [0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0]
# closed_hat = [0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0]
# empty_arr =  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

kick =       [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
open_hat =   [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
snare =      [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
closed_hat = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
empty_arr =  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    
instrument_dict = {0 : kick, 
                    1 : open_hat,
                    2 : snare,
                    3 : closed_hat} 

#set loops, THIS IS FUCKING WEIRD 
looper.set_loop(0, '500')
looper.set_loop(1, '100')
looper.set_loop(2, '400')
looper.set_loop(3, '200')
looper.set_loop(4, '300')
#for inst check

idle(looper)
       
    

            
    
        
        
        
    

