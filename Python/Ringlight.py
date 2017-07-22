
# coding: utf-8

# In[75]:

import serial
import time
def sendpack(pack):
    ser = serial.Serial('COM3', timeout=0)  # open serial port
          # check which port was really used
    time.sleep(3)
    ser.read(12)
    ser.write(pack)     # write a string
    time.sleep(1)
    print ser.read(200)
    ser.close()   
    
    
from crccheck.crc import Crcc16Mcrf4xx as crc16
def frame(data):
    array=bytearray(data)
    crc = crc16.calcbytes(array)
    return ([0x7E]+ list(array)+ list(crc)[::-1]+[ 0x7E]) #building frame 


sendpack(list(frame('\x03\xfF')))


# In[64]:





# In[91]:

sendpack(list(frame('\x03\xfF')))


# In[37]:

print pack


# In[16]:

pack=[0x7e ,0x03, 0x1C, 0x3D ,0x7E]


# In[3]:

print w

