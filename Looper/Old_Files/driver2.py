"""audio loop driver method"""
import asyncio
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

    
async def play_for_two_seconds(region_number):
    await asyncio.sleep(2*region_number)
    play_region(region_number)
    mixer.update_channel_volume(0, pot0.value)
    mixer.update_channel_volume(1, pot1.value)
    


async def main():
    task0 = asyncio.create_task(play_for_two_seconds(0))
    task1 = asyncio.create_task(play_for_two_seconds(1))
    task2 = asyncio.create_task(play_for_two_seconds(2))
    task3 = asyncio.create_task(play_for_two_seconds(3))
    task4 = asyncio.create_task(play_for_two_seconds(4))
    task5 = asyncio.create_task(play_for_two_seconds(5))
    task6 = asyncio.create_task(play_for_two_seconds(6))
    task7 = asyncio.create_task(play_for_two_seconds(7))
  
    

    
    await task0
    await task1
    await task2
    await task3
    await task4
    await task5
    await task6
    await task7
    
    
        #plays audio file in channel 0 and channel 2
        

asyncio.run(main())
       

            
    
        
        
        
    
