#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 23 20:25:00 2018

@author: gholbrow
"""
import time
import wave 
import serial

import simpleaudio as sa
wave_obj = sa.WaveObject.from_wave_file("/home/pi/CODE/NeoPixelStuff/TIE-Fire.wav")
play_obj = wave_obj.play()
play_obj.wait_done()

#pygame.mixer.init(48000, -16, 1, 1024)
#pygame.mixer.music.load("/Users/gholbrow/Downloads/TIE-Fire.wav")
#pygame.mixer.music.load("/home/pi/CODE/NeoPixelStuff/TIE-Fire.wav")
#pygame.mixer.music.play()   



ser = serial.Serial('/dev/ttyACM0', 9600)
while True:
    derp = ser.readline()
    derp2 = derp.decode('utf-8')
    
    if 'tie' in derp2:
        print(derp2)
        wave_obj = sa.WaveObject.from_wave_file("/home/pi/CODE/NeoPixelStuff/TIE-Fire.wav")
        play_obj = wave_obj.play()
        play_obj.wait_done()
              
    if 'Blaster' in derp2:
        print(derp2)

        wave_obj = sa.WaveObject.from_wave_file("/home/pi/CODE/NeoPixelStuff/Blaster-Imperial.wav")
        play_obj = wave_obj.play()
        play_obj.wait_done()        
        
    if 'cop' in derp2:
        print(derp2)

        wave_obj = sa.WaveObject.from_wave_file("/home/pi/CODE/NeoPixelStuff/414208__jacksonacademyashmore__airhorn.wav")
        play_obj = wave_obj.play()
        play_obj.wait_done()         
