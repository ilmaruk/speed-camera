import serial
import time
import logging
import sys
import numpy
import cv2

from picamera import PiCamera
from picamera.array import PiRGBArray
from sense_hat import SenseHat


def main(arduino, camera, classifier, sense_hat):
    try:
        while True:
            line = arduino.readline()
            velocity = process_line(line, classifier, sense_hat)
    finally:
        arduino.close()


def process_line(line, classifier, sense_hat):
    if line.startswith(b'Speeding'):
        logging.info('Received speeding alert: {:s}'.format(str(line)))
        _, velocity = line.split(b',')
        image = take_photo(camera)
        analyse_photo(image, classifier)

    elif line.startswith(b'State'):
        logging.info('Received state update: {:s}'.format(str(line)))
        _, id, red, amber, green = line.split(b',')
        set_sense_hat(sense_hat, red, amber, green)


def take_photo(camera):
    raw_capture = PiRGBArray(camera)
    time.sleep(0.1)
    camera.capture(raw_capture, format='bgr')
    return raw_capture.array


def analyse_photo(image, classifier):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    regs = classifier.detectMultiScale(gray, 1.3, 5)
    for (x, y, w, h) in regs:
        cv2.rectangle(image, (x, y), (x+w, y+h), (0, 0, 255), 2)

    image_path = '../photos/speeding-{:d}.jpg'.format(int(time.time()))
    cv2.imwrite(image_path, image)
    logging.info('Store new image at {:s}'.format(image_path))


def set_sense_hat(sense_hat, red, amber, green):
    R = [255 * red, 0, 0]
    A = [0, 0, 0]
    G = [0, 0, 255 * green]

    shape = [
        R, R, R, R, R, R, R, R,
        R, R, R, R, R, R, R, R,
        R, R, R, R, R, R, R, R,
        A, A, A, A, A, A, A, A,
        A, A, A, A, A, A, A, A,
        G, G, G, G, G, G, G, G,
        G, G, G, G, G, G, G, G,
        G, G, G, G, G, G, G, G,
    ]

    sense_hat.set_pixels(shape)


if '__main__' == __name__:
    root = logging.getLogger()
    root.setLevel(logging.DEBUG)

    handler = logging.StreamHandler(sys.stdout)
    handler.setLevel(logging.DEBUG)
    formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    handler.setFormatter(formatter)
    root.addHandler(handler)

    camera = PiCamera()
    camera.rotation = 180
    main(serial.Serial('/dev/ttyACM0', 9600), camera,
         cv2.CascadeClassifier('/usr/local/share/opencv4/haarcascades/haarcascade_russian_plate_number.xml'),
         SenseHat())
