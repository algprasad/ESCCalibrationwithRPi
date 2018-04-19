# ESCCalibrationwithRPi
When you have your own controller (for any mobile vehicle) implemented in Raspberry pi, sending PWM values from the PX4 flight stack is cumbersome and using Raspberry pi GPIO pins for controlling motors is imperative. In order to achieve that, it is required to calibrate ESCs with Raspberry pi and test if you can send controls to GPIO PINS. This program does exactly that. See README for detailed instructions.

##Instructions
First you need to install pigpio library from http://abyz.me.uk/rpi/pigpio/download.html in your raspberry pi. 
Then compile the program by follwing these:

TO BUILD

g++ -o testRPi main.cpp  -lpigpio -lrt -lpthread

TO RUN

sudo ./testRPi
