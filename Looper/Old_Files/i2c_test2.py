import smbus2
import time
# for RPI version 1, use “bus = smbus.SMBus(0)”
bus = smbus2.SMBus(1)

# This is the addre3s we setup in the Arduino Program
address = 0x04


def readNumber():
    #number = bus.read_byte(address)
    number = bus.read_i2c_block_data(address, 0, 16)
    return number


print(readNumber())