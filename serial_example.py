import serial
import time

try:
    arduino = serial.Serial("/dev/cu.usbmodem101", 9600)
    file = open("my_sensor_data.csv", 'w')
    file.write("TimeStamp, Data\n")
    connection = True
except:
    connection = False

time.sleep(2)

while connection:
    try:
        data = arduino.readline().decode('ascii').rstrip()
        print(data)
        file.write(str(time.time()) + ',' + str(data) + '\n')
    except KeyboardInterrupt:
        break

arduino.close()
file.close()