import time
import pygame
from pygame import mixer
from gpiozero import MCP3008, PWMLED


pot0 = MCP3008(0)#channel 0 of the MPC3008 pins
pot1 = MCP3008(1)#MCP3008 channel 1
resistor0 = MCP3008(2)
resistor1 = MCP3008(7)

pygame.init()
pygame.mixer.pre_init()
pygame.mixer.init()

channel1 = pygame.mixer.Channel(0)
channel2 = pygame.mixer.Channel(1)


sound1 = pygame.mixer.Sound("Track2.wav")
sound2 = pygame.mixer.Sound("output.wav")


while True:
    #channel1.play(sound0)#start the sounds
   # channel2.play(sound1)
    #time.sleep(8)
    
    count = 0
    while count < 80:#waits 80 ticks of 0.1 seconds
        channel1.set_volume(pot0.value)#updating volumes every 0.1 second
        channel2.set_volume(pot1.value)
        print("pot0 value: ", pot0.value)
        print("pot1 value: ", pot1.value)
        print("resistor0 value: ", resistor0.value)
        print("resistor1 value: ", resistor1.value)

        count += 1
        time.sleep(0.1)

