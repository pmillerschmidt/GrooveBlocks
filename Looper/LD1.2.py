"""Audio Looper driver method"""
import time

import smbus2
# from gpiozero import MCP3008, PWMLED
from looper import Looper
from sound_files import mix

# set up the bus
bus = smbus2.SMBus(1)
address = 0x04

def readBus():
    data = bus.read_i2c_block_data(address, 0, 3)
    return data

def parse(data):
    MIDI = sort(data[0], 10)
    effect = sort(data[1], 10)
    inst = sort(data[2], 10)
    output = str(effect) + str(inst) + str(MIDI) 
    return output
    
def play_region(instr, channel_number):
    ##play loop from channel number 
    mixer.play(instr.get_loop(channel_number), channel_number)

def start_loop(instr):
    """Executable loop. It updates channel volumes on 0.1 second intervals, and plays
    the next step in the sequence every 2 seconds. Loops after 8 steps"""    
    ##get number of channels
    #num_ch = instr.num_channel
    step = -1
    
    # mixer.update_channel_volume(0, pot0.value)#setup the channel volumes before audio playback
    # mixer.update_channel_volume(1, pot1.value)
    
    
    while True:#audio loop
        #start the timer
        #OPTIMIZE THIS, THIS IS STARTING THE LOOP SLIGHTLY EARLY
        BUFFER = 0.1
        length = 8
        start_time = time.time()
        #check for new information    
        output = parse(readBus())
        #print(output)
        
        #if its '000' try again
        while (output == '000'):
            output = parse(readBus())
            #print(output)
        #if its non-identifiable, try again
        while (output[0] == '8' or output[1] == '8' or output[2] == '8'):
            output = parse(readBus())
            #print(output)

        if (len(output) == 3):
            instr.set_loop(instr.num_channels, output)
            play_region(instr, instr.num_channels - 1) 
        #get time

        curr_time = time.time()
        elapsed_time = curr_time - start_time
        #wait until it is next time 
        while(elapsed_time < length):
            
            curr_time = time.time()
            elapsed_time = curr_time - start_time
           
def sort(input, threshold):
    #sort the serial data into specific channels 
    #if its around 40 its 1, 100 its 2, 180 its 3, it its 0, then be default
    if (abs(input - 0) < threshold):
        return 0
    elif (abs(input - 255) < threshold):
        return 1
    elif (abs(input - 100) < threshold):
        return 2
    elif (abs(input - 153) < threshold):
        return 3
    elif(abs(input - 20) < threshold):
        return 4
    else:
        ##error code
        return 8


while True:
    #settig up channel data
    TEMPO = 5
    #how many instruments
    CHANNELS = 1
   
    looper = Looper(TEMPO, CHANNELS)#5 is the tempo, 2 channels, 8 steps
    # sequencer.scan_tracks#not implemented yet
    #output = '001'
    #pause/unpause - pygame.mixer.pause() 
    #pygame.mixer.stop()
    #setting up mixer
    mixer = mix()
    mixer.update_channel_volume(0, 1.0)
    #start loop on sequencer
    start_loop(looper)
       
       

            
    
        
        
        
    

