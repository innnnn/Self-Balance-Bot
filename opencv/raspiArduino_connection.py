import serial

ser = serial.Serial("/dev/myarduino", 9600)
while True:
	read_serial = ser.readline()
	#s = str(int(ser.readline(), 10))
	
	#print(s)
	print read_serial
