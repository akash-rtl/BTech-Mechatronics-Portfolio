import machine
from time import sleep

potPin = 28
myPot = machine.ADC(potPin) #Analog to digital converter
while True:
    potVal = myPot.read_u16() #it's reading 16 bit number 
    print(potVal/19859)
    sleep(.5)