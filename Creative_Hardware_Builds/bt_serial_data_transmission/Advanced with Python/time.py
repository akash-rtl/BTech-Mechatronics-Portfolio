#port
#baudrate
#bytesize
#timeout
#stopbits

import serial
import keyboard


ser = serial.Serial(port="COM15", baudrate = 9600, bytesize = 8, timeout=2,stopbits = serial.STOPBITS_ONE)

while True:
    if keyboard.is_pressed("n" or "N"):
        #print("LED ON")
        ser.write("1".encode('Ascii'))

    if keyboard.is_pressed("f" or "F"):
        #print("LED OFF")
        ser.write("0".encode('Ascii'))

    if keyboard.is_pressed("b" or "B"):
        ser.write("0".encode('Ascii'))
        print("LOOP OVER")
        break



ser.close()
input("BYE!!!")
