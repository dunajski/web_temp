# Simple python script to run two tasks:
#   - read data from serial in loop
#   - send data over ftp

# PySerial docs https://pyserial.readthedocs.io/en/latest/shortintro.html
import serial

serialString = ""


if __name__ == "__main__":
    # check port name with device manager (windows) or
    # dmesg | grep tty (linux)
    # port_name = "COM2"
    port_name = '/dev/ttyUSB0'
    serialPort = serial.Serial(port=port_name, baudrate=9600, bytesize=8,
                               parity='N', stopbits=1, timeout=2)
    print("Reading from serial"  + serialPort.name +  " started....")

    while(1):

        # Wait until there is data waiting in the serial buffer
        if(serialPort.in_waiting > 0):

            # Read data out of the buffer until a carraige return / new line is found
            serialString = serialPort.readline()

            # Print the contents of the serial data
            print(serialString.decode('Ascii'))
