#!/usr/bin/env python
# -*- coding: utf-8 -*-
import freenect
import numpy as np
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(7, GPIO.OUT) ## Setup GPIO Pin 7 to OUT
GPIO.setup(11, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)
#GPIO.setup(15, GPIO.IN) ## pin de override
pines = [29,31,33,35] #pines del driver
p = 12 #pwm1
pp = 11 #pwm2
stdby = 37 #enable
GPIO.setup(pines, GPIO.OUT)
GPIO.setup(p, GPIO.OUT)
GPIO.setup(pp, GPIO.OUT)
#pwm = GPIO.PWM(p, 10000)
GPIO.setup(stdby, GPIO.OUT)
threshold = 150
current_depth = 400

def PilotoAutomatico():
    checkD = 0b0
    checkC = 0b0
    checkI = 0b0
    global threshold
    global current_depth
    depth, timestamp = freenect.sync_get_depth()
    depth = 255 * np.logical_and(depth >= current_depth - threshold,
                                depth <= current_depth + threshold)
    depth = depth.astype(np.uint8)
    temp = depth
    avgD = temp[:,:179].mean()
    avgC = temp[:,180:359].mean()
    avgI = temp[:,360:479].mean()
    d = 'obstaculo derecha'
    c = 'obstaculo centro'
    i = 'obstaculo izquierda'
    t = 'dele sin miedo'
    GPIO.output(stdby,True) #
    GPIO.output(p,True)
    GPIO.output(pp,True)

    #obstaculo derecha
    if avgD > 35.0:
        #GPIO.output(7,True) 
        checkD = 0b1
        
    else:
        #GPIO.output(7,False) ##
        checkD = 0b0
        
    #obstaculo centro    
    if avgC > 35.0:
        #GPIO.output(11,True) 
        checkC = 0b1
        
    else:
        #GPIO.output(11,False) ##
        checkC = 0b0

    #opbstaculo izquierda    
    if avgI > 35.0:
        #GPIO.output(13,True) ## 
        checkI = 0b1
        
    else:
        #GPIO.output(13,False) ##
        checkI = 0b0
    
    
    if  (checkD & checkC & checkI): #avance hcia adelante
        print 'piloto automatico:pare'
        GPIO.output(29,False) #PARE
        GPIO.output(31,False)
        GPIO.output(33,False)
        GPIO.output(35,False)
        
    elif (checkC & checkD) : #obstaculo izquierda
        if ~checkI:
            print 'piloto automatico:doblar derechas'
            GPIO.output(29,True) #doble derecha
            GPIO.output(31,False)
            GPIO.output(33,True)
            GPIO.output(35,True)
            time.sleep(0.5)
            GPIO.output(29,False) #PARE un toque
            GPIO.output(31,False)
            GPIO.output(33,False)
            GPIO.output(35,False)
            time.sleep(0.5)
            
    elif (checkC & checkI) : #obstaculo derecha
        if ~checkD:
            print 'piloto automatico:doblar izquierdas'
            GPIO.output(29,True) #doble izquierda
            GPIO.output(31,True)
            GPIO.output(33,True)
            GPIO.output(35,False)
            time.sleep(0.5)
            GPIO.output(29,False) #PARE un toque
            GPIO.output(31,False)
            GPIO.output(33,False)
            GPIO.output(35,False)
            time.sleep(0.5)
        
    else:
        print 'piloto automatico:adelante'
        GPIO.output(29,True) #ir adelante
        GPIO.output(31,False)
        GPIO.output(33,True)
        GPIO.output(35,False)
    
    

def PilotoManual():
    GPIO.output(stdby,True) #
    GPIO.output(p,True)
    GPIO.output(pp,True)
    GPIO.output(7,False)
    #GPIO.output(11,False)
    GPIO.output(13,False)
    with open("accion.txt") as file:
        #file = open("accion.txt","r")
        data = file.read()
        print data
        ad = '1010' #adelante
        at = '0101' #atras
        fr = '0000' #freno
        de = '1011' #derecha
        iz = '1110' #izquierda
        if data == ad: #avance adelante
            print 'adelante'
            GPIO.output(29,True) #ir adelante
            GPIO.output(31,False)
            GPIO.output(33,True)
            GPIO.output(35,False) 
        elif data == at:
            print 'atras'
            GPIO.output(29,False) #ir atras
            GPIO.output(31,True)
            GPIO.output(33,False)
            GPIO.output(35,True)
        elif data == fr:
            print 'detenido'
            GPIO.output(29,False) #PARE
            GPIO.output(31,False)
            GPIO.output(33,False)
            GPIO.output(35,False)
        elif data == de:
            print 'derecha'
            GPIO.output(29,True) #doble derecha
            GPIO.output(31,False)
            GPIO.output(33,True)
            GPIO.output(35,True)
        elif data == iz:
            print 'izquierda'
            GPIO.output(29,True) #doble izquierda
            GPIO.output(31,True)
            GPIO.output(33,True)
            GPIO.output(35,False)
        #else:
           # print 'dato malo'
        
        


while (1):
    with open("override.txt") as file:  
        data = file.read()
        a = '1'
        if data == a: #automatico
            #print 'piloto automatico activado'
            PilotoAutomatico()
            #time.sleep(0.5)
        else: #manual
            #print 'piloto manual activado'
            PilotoManual()
            #print 'buena'
            #time.sleep(0.1)
    #file.close()
        


