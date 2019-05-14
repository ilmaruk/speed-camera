import serial
import time
import logging
import sys


from picamera import PiCamera


def main(arduino, camera):
    try:
        while True:
            line = arduino.readline()
            velocity = process_line(line)
            if velocity is None:
                continue

            photo_path = take_photo(camera, velocity)
            analyse_photo(photo_path)
    finally:
        arduino.close()


def process_line(line):
    if not line.startswith(b'Speeding'):
        return None

    logging.info('Received speeding alert: {:s}'.format(str(line)))

    _, velocity = line.split(b',')
    return velocity


def take_photo(camera, velocity):
    destination = '../photos/speeding-{:d}.jpg'.format(int(time.time()))
    camera.capture(destination)
    logging.info('Taken speeding image: {:s}'.format(destination))

    return destination


def analyse_photo(path):
    pass

if '__main__' == __name__:
    root = logging.getLogger()
    root.setLevel(logging.DEBUG)

    handler = logging.StreamHandler(sys.stdout)
    handler.setLevel(logging.DEBUG)
    formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    handler.setFormatter(formatter)
    root.addHandler(handler)

    main(serial.Serial('/dev/ttyACM0', 9600), PiCamera())
