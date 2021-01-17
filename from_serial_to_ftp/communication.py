# Simple python script to run two tasks:
#   - read data from serial in loop
#   - send data over ftp

# PySerial docs https://pyserial.readthedocs.io/en/latest/shortintro.html
import serial

def readfromserial():
    # check port name with device manager (windows) or
    # dmesg | grep tty (linux)
    # port_name = "COM2"
    # port_name = "tty/USB0"
    serialPort = serial.Serial(port=port_name, baudrate=9600, bytesize=8,
                               parity='N', stopbits=1, timeout=2)
    print("Reading from serial"  + serialPort.name +  " started....")
    # TODO reading from serial

if __name__ == "__main__":
    readfromserial()



