#!/usr/bin/env python

import cv2
import serial
import time, sys
import grovepi
button = 3
buzzer = 8
patname = "Nobody"

# Loop the program until we escape
from grove_rgb_lcd import *

# Pill machine function

def pillmachine():
    print("Start of pillmachine")
    # set up camera object
    cap = cv2.VideoCapture(-1)

    # QR code detection object
    detector = cv2.QRCodeDetector()

    while True:
    # get the image
        _, img = cap.read()
    # get bounding box coords and data
        data1, bbox, _ = detector.detectAndDecode(img)
    
    # if there is a bounding box, draw one, along with the data
        if(bbox is not None):
            for i in range(len(bbox)):
                cv2.line(img, tuple(bbox[i][0]), tuple(bbox[(i+1) % len(bbox)][0]), color=(255,0, 255), thickness=2)
            cv2.putText(img, data1, (int(bbox[0][0][0]), int(bbox[0][0][1]) - 10), cv2.FONT_HERSHEY_SIMPLEX,0.5, (0, 255, 0), 2)
            if data1:
                print("data found: ", data1)
                break
    # display the image preview
        cv2.imshow("code detector", img)
        if(cv2.waitKey(1) == ord("q")):
            break
    # free camera object and exit
    cap.release()
    cv2.destroyAllWindows()

    #sending the data to arduino 
    if __name__ == '__main__':
        ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
        ser.reset_input_buffer()

    # while True:
        ser.write(str(data1).encode('utf-8'))
        print(data1)
        time.sleep(1)

# Check ID function

def checkid():
    global patname
    print("Start ID")
    # set up camera object
    cap = cv2.VideoCapture(-1)

    # QR code detection object
    detector = cv2.QRCodeDetector()

    while True:
    # get the image
        _, img = cap.read()
    # get bounding box coords and data
        data, bbox, _ = detector.detectAndDecode(img)
    
    # if there is a bounding box, draw one, along with the data
        if(bbox is not None):
            for i in range(len(bbox)):
                cv2.line(img, tuple(bbox[i][0]), tuple(bbox[(i+1) % len(bbox)][0]), color=(255,0, 255), thickness=2)
            cv2.putText(img, data, (int(bbox[0][0][0]), int(bbox[0][0][1]) - 10), cv2.FONT_HERSHEY_SIMPLEX,0.5, (0, 255, 0), 2)
            if data:
    # Add troubleshooting printout
    #            print("name found: ", data)
                patname = data
    #            print(patname)
                break
    # display the image preview
        cv2.imshow("code detector", img)
        if(cv2.waitKey(1) == ord("q")):
            break
    # free camera object and exit
    cap.release()
    cv2.destroyAllWindows()

# main function

while True:
    try:
#        from grove_rgb_lcd import *

  #      try:
        setRGB(0,255,0)
        setText("Press the button to start demo")
        time.sleep(2)

        grovepi.pinMode(button,"INPUT")
        while True:
            try:
#            print(grovepi.digitalRead(button))
                if grovepi.digitalRead(button) == 1:
                    setRGB(0,255,255)
                    setText("Alarm will sound in 5 seconds")
                    time.sleep(5)
                    grovepi.pinMode(buzzer,"OUTPUT")
#               if you don't wnat to sound alarm, comment the next line
#                    grovepi.digitalWrite(buzzer,1)
                    setRGB(51,255,255)
                    time.sleep(0.2)
                    grovepi.digitalWrite(buzzer,0)
                    setText("Show the patient ID card")
                    time.sleep(2)
                    checkid()
                    setRGB(255,204,229)
                    setText("Welcome! " + patname + " Please stand by!")
                    time.sleep(5)
                    setText("Please show your medication card")
                    pillmachine()
                    setText("Now we are giving out pills")
                    time.sleep(6)
                    setRGB(255,255,204)
                    setText("Thank you! Have a Good Day!")
                    time.sleep(5)
                    break

            except IOError:
                print ("Error w buzzer and button")

    except IOError:
        print ("Error w LCD display")

