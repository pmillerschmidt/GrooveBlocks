"""Audio Looper driver method"""
import time
import serial
#lets switch all of this over to WIRE!

# from gpiozero import MCP3008, PWMLED
from looper import Looper
from sound_files import mix

# set up the serial line
port = '/dev/cu.usbmodem143401'
ser = serial.Serial(port, 9600, timeout=0.1)
time.sleep(2)

def check_serial(ser):
    # Read input from Arduino, 777 is the error code
    output = "777"
    
    data = ser.readline()         # read a byte string
    n = data.decode()  # decode byte string into Unicode
    string = n.rstrip() # remove \n and \r
    # if its an empty string 
    if string:
        #get the resistor value, make it an int, sort it and then 
        #turn it back into a string
        MIDI = str(sort(int(n.split(':')[0]), 10))
        effect = str(sort(int(n.split(':')[1]), 10))
        inst = str(sort(int(n.split(':')[2]), 10))
        #make 3-digit code
        output = MIDI+effect+inst   
        return output
    else:
        return None

##MIGHT NOT NEED WITH LOOPER METHOD
# # Set the channel and step clip 
# def set_clip(instr, channels, steps, clip):
#     for i in range(channels):
#         for j in range(steps):
#             instr.set_audio_num(i, j, clip)

    
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
        output = check_serial(ser)
        print(output)
        
        #if its a valid code, play the loops
        if (output == None):
            output = check_serial(ser)
            print(output)
        
        #if its '000' try again
        elif (output == '000'):
                    output = check_serial(ser)

        elif (len(output) == 3):
            instr.set_loop(instr.num_channels, output)
            play_region(instr, instr.num_channels - 1) 
        #get time

        curr_time = time.time()
        elapsed_time = curr_time - start_time
        found = False
        #wait until it is next time 
        while(elapsed_time < length):
            
            curr_time = time.time()
            elapsed_time = curr_time - start_time
            #when it is getting close refresh 
            if (elapsed_time > (length - 1)) and (found == False):
                output = check_serial(ser)
                if (output == None):
                    output = check_serial(ser)
                    found = True
            #print(output)


    
            # while (time.time() < end_time):
            #     if (output == '000' or output == '777'):
            #         continue
            
            #     #set the loop based on the arduino input
            #     else:
            #         instr.set_loop(instr.num_channels, output)
            #         play_region(instr, instr.num_channels - 1) 
            #         print("here")

           
def sort(input, threshold):
    #sort the serial data into specific channels 
    #if its around 40 its 1, 100 its 2, 180 its 3, it its 0, then be default
    if (abs(input - 0) < threshold):
        return 0
    elif (abs(input - 500) < threshold):
        return 1
    elif (abs(input - 100) < threshold):
        return 2
    elif (abs(input - 183) < threshold):
        return 3
    elif(abs(input - 20) < threshold):
        return 4
    else:
        return "error: can't identify node"




while True:
    #settig up channel data
    TEMPO = 5
    #how many instruments
    CHANNELS = 1
   
    looper = Looper(TEMPO, CHANNELS)#5 is the tempo, 2 channels, 8 steps
    # sequencer.scan_tracks#not implemented yet
    #output = '001'

    #setting up mixer
    mixer = mix()
    #start loop on sequencer
    start_loop(looper)
       

            
    
        
        
        
    

