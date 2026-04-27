#0-79 Green 80-94 Yellow  95-100 Red



from machine import Pin,ADC
from time import sleep

led1 = Pin(13, Pin.OUT)
led2 = Pin(14, Pin.OUT)
led3 = Pin(15, Pin.OUT)


potPin = 28
myPot = machine.ADC(potPin) #Analog to digital converter


while True:
    potVal = myPot.read_u16() #it's reading 16 bit number
    
    val = int(potVal/655.35)
    print(val)
    
    if val < 80:
        led1.value(1)
        led2.value(0)
        led3.value(0)
        
        
    elif (80 <= val <= 94):
        led1.value(0)
        led2.value(1)
        led3.value(0)
        
    elif (95 <= val <=100):
        led1.value(0)
        led2.value(0)
        led3.value(1)
        
    sleep(.1)
    
