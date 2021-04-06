import serial
import time

if __name__ ==  '__main__':
    ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1) #change ACM number as found from ls /dev/tty/ACM*
    ser.flush()


    while True:
        test = input("Enter command: ") #d-down, u-up, 1-right, 2-left, 3-spin
        ser.write(test.encode())
        
        line = ser.readline().decode('utf-8').rstrip()
        while line != "Finished":
            print(line)
            line = ser.readline().decode('utf-8').rstrip()
        
        print(line)
        time.sleep(1)
        
