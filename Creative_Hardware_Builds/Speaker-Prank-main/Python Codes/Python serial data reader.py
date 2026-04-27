#https://www.youtube.com/watch?v=VQCiEQockwE&t=598s
#there is one video which allows you to select the com port also

import serial

ser = serial.Serial(port = "COM14", baudrate = 9600, bytesize = 8, timeout = 2, stopbits = serial.STOPBITS_ONE)

while True:
    
    #to write in serial port
    #ser.write("A".encode('Ascii'))

    recieve = ser.read()
    print(recieve.decode('Ascii'))