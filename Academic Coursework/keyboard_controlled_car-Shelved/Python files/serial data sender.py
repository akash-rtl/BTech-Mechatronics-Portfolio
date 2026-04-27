import serial
import keyboard

ser = serial.Serial(port = "COM14", baudrate = 9600, bytesize = 8, timeout = 2, stopbits = serial.STOPBITS_ONE)

def up():
    ser.write("w".encode('Ascii'))
def down():
    ser.write("s".encode('Ascii'))
def left():
    ser.write("a".encode('Ascii'))
def right():
    ser.write("d".encode('Ascii'))
def stop():
    ser.write("x".encode('Ascii'))

while True:
    
    #to write in serial port
    
    if keyboard.is_pressed('w' or 'W'):
        ser.write("w".encode('Ascii'))
        
    if keyboard.is_pressed('s' or 'S'):
        down()
        
    if keyboard.is_pressed('a' or 'A'):
        left()
        
    if keyboard.is_pressed('d' or 'D'):
        right()
        
    print("hi")
    stop()



    #to recieve the data
    recieve = ser.read()
    if recieve == 'w' :
        print("Hello there")
    print(recieve.decode('Ascii'))
    print("Hello")