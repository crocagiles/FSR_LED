#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Apr 23 20:25:00 2018

@author: gholbrow
"""
import time
import wave 
import serial
from playsound import playsound

import pygame

ser = serial.Serial('/dev/tty.usbmodem1421', 9600)
while True:
    derp = ser.readline()
    derp2 = derp.decode('utf-8') 
    if 'tie' in derp2:
        print(derp2)
        
        pygame.mixer.init()
        pygame.mixer.music.load("/Users/gholbrow/Downloads/TIE-Fire.wav")
        pygame.mixer.music.play()   
              
    if 'Blaster' in derp2:
        print(derp2)
        
        pygame.mixer.init()
        pygame.mixer.music.load("/Users/gholbrow/Downloads/Blaster-Imperial.wav")
        pygame.mixer.music.play()     
        
    if 'cop' in derp2:
        print(derp2)
        
        pygame.mixer.init()
        pygame.mixer.music.load("/Users/gholbrow/Downloads/414208__jacksonacademyashmore__airhorn.wav")
        pygame.mixer.music.play()         
