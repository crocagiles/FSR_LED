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
    
    print(derp2)

    if 'blue' in derp2:
        print(derp2)
        wave_obj = sa.WaveObject.from_wave_file("/home/pi/CODE/NeoPixelStuff/173000__keykrusher__bicycle-bell-2.wav")
        play_obj = wave_obj.play()
        continue
        #play_obj.wait_done()
              
    elif 'white' in derp2:
        print(derp2)

        wave_obj = sa.WaveObject.from_wave_file("/home/pi/CODE/NeoPixelStuff/boat_horn.wav")
        play_obj = wave_obj.play()
        continue
        #play_obj.wait_done()        
        
    elif 'green' in derp2:
        print(derp2)
        play_obj.stop()
        wave_obj = sa.WaveObject.from_wave_file("/home/pi/CODE/NeoPixelStuff/414208__jacksonacademyashmore__airhorn.wav")
        play_obj = wave_obj.play()
        #play_obj.wait_done()         
