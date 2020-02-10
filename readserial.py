import time
import serial

ser = serial.Serial(
    port='COM3',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)
counter = 0

while 1 :
    #On lit la ligne
    x = ser.readline()
    x = x.rstrip()
    x = x.decode("utf-8")
    print ("Valeur : {}".format(x))

    #On écrit
    #ser.write('1')
    #set.flush()