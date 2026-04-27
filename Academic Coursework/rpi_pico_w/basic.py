import machine
from time import sleep

potPin = 28
myPot = machine.ADC(potPin) #Analog to digital converter
while True:
    potVal = myPot.read_u16() #it's reading 16 bit number 
    print(int(potVal/655.35))
    sleep(.5)