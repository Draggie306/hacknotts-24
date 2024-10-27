import serial
from serial import Serial
import requests
import time


def say_hello():
    print("Hello from Oliver's function.")

def serial_listen():
    # Set up the serial connection (adjust COM port and baud rate as needed)
    ser = Serial("/dev/ttyACM0", 9600)
    time.sleep(2)  # Allow time for the connection to establish

    while True:
        if ser.in_waiting > 0:
            # Read the command from Arduino
            command = ser.readline().decode('utf-8').strip()
            print(f"Arduino output: {command}")
            
            match command:
                case "CMD:DISTANCE_VERY_CLOSE":
                    print("[serial_listen] :: Handling case for very close distance")
                    response = requests.get('https://hacknotts24.draggie.workers.dev/distance/very_close')
                    
                    if response.status_code == 200:
                        ser.write("ok\n".encode('utf-8'))
                    else:
                        ser.write("data.err".encode('utf-8'))
                case "CMD:DISTANCE_CLOSE":
                    print("[serial_listen] :: Handling case for close distance")
                    response = requests.get('https://hacknotts24.draggie.workers.dev/distance/close')
                    
                    if response.status_code == 200:
                        ser.write("ok\n".encode('utf-8'))
                    else:
                        ser.write("data.err".encode('utf-8'))

                case "CMD:DISTANCE_FAR":
                    print("[serial_listen] :: Handling case for far distance")
                    response = requests.get('https://hacknotts24.draggie.workers.dev/distance/far')
                    
                    if response.status_code == 200:
                        ser.write("ok\n".encode('utf-8'))
                    else:
                        ser.write("data.err".encode('utf-8'))


                case "CMD:DISTANCE_VERY_FAR":
                    print("[serial_listen] :: Handling case for very far distance")
                    response = requests.get('https://hacknotts24.draggie.workers.dev/distance/very_far')
                    
                    if response.status_code == 200:
                        ser.write("ok\n".encode('utf-8'))
                    else:
                        ser.write("data.err".encode('utf-8'))


"""
        Serial.println("[process_distance] :: WARN: No object detected");
        shouldTrigger = 0;
        Serial.println("cmd:DISTANCE_ZERO");
    }
    else if (distance < 10)
    {
        Serial.println("[process_distance] :: Object is very close!");
        Serial.println("cmd:DISTANCE_VERY_CLOSE");
    }
    else if (distance < 100)
    {
        Serial.println("[process_distance] :: Object is close");
        Serial.println("cmd:DISTANCE_CLOSE");
    }
    else if (distance < 200)
    {
        Serial.println("[process_distance] :: Object is fairly far");
        Serial.println("cmd:DISTANCE_FAR");
    }
    else if (distance < 500)
    {
        Serial.println("[process_distance] :: Object is far");
        Serial.println("cmd:DISTANCE_VERY_FAR");
    }
    else if (distance < 1000)
    { // this is the limit for the sensor
        Serial.println("[process_distance] :: Object is out of range");
        shouldTrigger = 0;
        Serial.println("cmd:DISTANCE_OUT_OF_RANGE");
"""