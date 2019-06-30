from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
import numpy as np
import serial

#serial = serial.Serial("/dev/myarduino", 9600)

# set font display on screen
font = cv2.FONT_HERSHEY_COMPLEX

# set py camera, resolution, framerate
camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size = (640, 480))

# set upper and lower range of RED, GREEN, BLUE
red_lower_range = np.array([150, 50, 50])
red_upper_range = np.array([190, 255, 255])
green_lower_range = np.array([60, 100, 100])
green_upper_range = np.array([80, 255, 255])
blue_lower_range = np.array([80, 100, 100])
blue_upper_range = np.array([150, 255, 255])

# initialize string send to Arduino nano
dataString = "~"
# initialize detect shape and color
shape = "unidentified"
color = "unidentified"

# set sleep time
time.sleep(0.1)

# image process of each frame captured from pi camera
for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):
	image = frame.array
	
	# blur image to decrease background errors
	blurred_image = cv2.GaussianBlur(image, (5, 5), 0)

	# convert origin image from RGB to HSV and then convert to R/G/B mask images(range set above) -> detect color
	hsv_image = cv2.cvtColor(blurred_image, cv2.COLOR_BGR2HSV)
	red_mask = cv2.inRange(hsv_image, red_lower_range, red_upper_range)
	green_mask = cv2.inRange(hsv_image, green_lower_range, green_upper_range)
	blue_mask = cv2.inRange(hsv_image, blue_lower_range, blue_upper_range)
	# merge three mask images
	mask = red_mask + green_mask + blue_mask
	# get image with colors wanted(R/G/B)
	result_image = cv2.bitwise_and(image, image, mask = mask)

	# convert origin image to gray scale -> find contours -> detect shape
	image_gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	
	# get threshold image
	_, threshold = cv2.threshold(image_gray, 100, 255, cv2.THRESH_BINARY)
	# get detected contours array from image
	contours, _ = cv2.findContours(threshold, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
	for cnt in contours:
		# get momemt from each contours(shape)
		m = cv2.moments(cnt)
		# find area of the detected shape, discard if it is too small
		area = cv2.contourArea(cnt)
		if area > 10000:
			# calculate center of detected shape
			cx = int(m['m10'] / m['m00'])
			cy = int(m['m01'] / m['m00'])
			approx = cv2.approxPolyDP(cnt, 0.03*cv2.arcLength(cnt, True), True)
			# define shapes
			if len(approx) == 3:
				shape = "Triangle"
			elif len(approx) == 4:
				shape = "Rectangle"
			else:
				shape = "Circle"

			# define colors
			c = image[cy][cx]
			if c[0] > c[1] and c[0] > c[2]:
				color = "B"
			elif c[1] > c[0] and c[1] > c[2]:
				color = "G"
			elif c[2] > c[0] and c[2] > c[1]:
				color = "R"

			#color_str = "(" + str(color[0]) + ", " + str(color[1]) + ", " + str(color[2]) + ")"
			#print("color: %s\n" % (color_str))
			#print("CX: %d, CY: %d" % (cx, cy))

			# draw detected shapes on the image and add text
			cv2.drawContours(image, cnt, -1, (0, 255, 0), 3)
			cv2.putText(image, shape, (cx, cy), font, 0.5, (255, 255, 255), 2)
	
	# set string send to Arduino nano then initialize it
	if(shape == "Circle"): dataString += "S"
	if(shape == "Triangle"): dataString += "L"
	if(shape == "Rectangle"): dataString += "R"
	if(color == "R"): dataString += "R"
	if(color == "G"): dataString += "G"
	if(color == "B"): dataString += "B"
	dataString += "#"
#	serial.write(dataString)
	print(dataString)
	dataString = "~"

	# show images(debug)
	cv2.imshow("Origin", image)
	#cv2.imshow("Gray", image_gray)
	#cv2.imshow("Red", red_mask)
	#cv2.imshow("Green", green_mask)
	#cv2.imshow("Blue", blue_mask)
	cv2.imshow("Mask", mask)
	#cv2.imshow("Result", result_image)
	#cv2.imshow("Threshold", threshold)
	# set wait time(1 millisecond), 0xFF(prevent bug)
	key = cv2.waitKey(1) & 0xFF

	# clear the stream in preparation for the next frame
	rawCapture.truncate(0)

	# set 'quit' hot key
	if key == ord("q"):
		break
