import serial

ser = serial.Serial(port="COM15", baudrate = 9600, bytesize = 8, timeout=2,stopbits = serial.STOPBITS_ONE)


ser.write("1".encode('Ascii'))