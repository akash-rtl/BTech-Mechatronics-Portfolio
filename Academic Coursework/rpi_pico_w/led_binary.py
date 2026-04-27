from machine import Pin
from time import sleep

led1 = Pin(15,Pin.OUT)
led2 = Pin(14,Pin.OUT)
led3 = Pin(13,Pin.OUT)
led4 = Pin(12,Pin.OUT)

#led.value(1)

dela = 5


while True:
    
    led1.value(0)
    led2.value(0)
    led3.value(0)
    led4.value(0)
    sleep(dela)
    
    led1.value(0)
    led2.value(0)
    led3.value(0)
    led4.value(1)
    sleep(dela)
    
    led1.value(0)
    led2.value(0)
    led3.value(1)
    led4.value(0)
    sleep(dela)
    
    led1.value(0)
    led2.value(0)
    led3.value(1)
    led4.value(1)
    sleep(dela)
    
    led1.value(0)
    led2.value(1)
    led3.value(0)
    led4.value(0)
    sleep(dela)
    
    led1.value(0)
    led2.value(1)
    led3.value(0)
    led4.value(1)
    sleep(dela)
    
    led1.value(0)
    led2.value(1)
    led3.value(1)
    led4.value(0)
    sleep(dela)
    
    led1.value(0)
    led2.value(1)
    led3.value(1)
    led4.value(1)
    sleep(dela)
    
    led1.value(1)
    led2.value(0)
    led3.value(0)
    led4.value(0)
    sleep(dela)
    
    led1.value(1)
    led2.value(0)
    led3.value(0)
    led4.value(1)
    sleep(dela)
    
    led1.value(1)
    led2.value(0)
    led3.value(1)
    led4.value(0)
    sleep(dela)
    
    led1.value(1)
    led2.value(0)
    led3.value(1)
    led4.value(1)
    sleep(dela)
    
    led1.value(1)
    led2.value(1)
    led3.value(0)
    led4.value(0)
    sleep(dela)
    
    led1.value(1)
    led2.value(1)
    led3.value(0)
    led4.value(1)
    sleep(dela)
    
    led1.value(1)
    led2.value(1)
    led3.value(1)
    led4.value(0)
    sleep(dela)
    
    led1.value(1)
    led2.value(1)
    led3.value(1)
    led4.value(1)
    sleep(dela)
  
