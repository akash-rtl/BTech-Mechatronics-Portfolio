import serial
import pyautogui as music
import time

a = 0

ser = serial.Serial(port = "COM14", baudrate = 9600, bytesize = 8, timeout = 2, stopbits = serial.STOPBITS_ONE)

def plapau():
    music.press("playpause")


while True:
    
    #to write in serial port
    #ser.write("A".encode('Ascii'))

    recieve = ser.read()
    data = recieve.decode('Ascii')
    
    
    
    
    
    if data == "1":
        if a == 0:
            music.press("playpause")
            a = 1
            
        if a == 1:
            time.sleep(15)
            a = 0
    print(data)
    

           