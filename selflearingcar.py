import sensor, image, time, math
from pyb import UART
from pyb import LED

uart = UART(3, 19200)
LED(1).on()
LED(2).on()
LED(3).on()
sensor.reset()
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)
sensor.skip_frames(30)
sensor.set_auto_gain(False)
sensor.set_auto_whitebal(False)
clock = time.clock()
x = 0
angle = 100

while True:
    number = 0
    clock.tick()
    img = sensor.snapshot()
    for tag in img.find_apriltags(families =  image.TAG16H5):
        img.draw_rectangle(tag.rect(), color=(255, 0, 0))
        img.draw_cross(tag.cx(), tag.cy(), color=(0, 255, 0))
        degrees = 180 * tag.rotation() / math.pi
        angle = tag.cx() + 40
        print(tag.id(), degrees)
        print("tag.cx()", tag.cx())
        number = tag.id()

    if number == 4:
        uart.write(str('+') + str(50) + "," + str(angle) + "E\n")
    elif number == 6:
        uart.write(str('-') + str(50) + "," + str(200-angle) + "E\n")
    else:
        uart.write(str('+') + str(0) + "," + str(100) + "E\n")

    time.sleep_ms(20)
