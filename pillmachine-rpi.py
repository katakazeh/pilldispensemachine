mport cv2
import serial
import time

# Loop the program until we escape

while True:

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
                print("data found: ", data)
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

#    while True:
        ser.write(str(data).encode('utf-8'))
        print(data)
        time.sleep(1)
