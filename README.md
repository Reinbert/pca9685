PCA9685 README


	This software is a devLib extension to wiringPi <http://wiringpi.com/>
	and enables it to control the Adafruit PCA9685 16-Channel 12-bit
	PWM/Servo Driver <http://www.adafruit.com/products/815> via I2C interface.

	Copyright (c) 2014 Reinhard Sprung

	If you have questions or improvements email me at
	reinhard.sprung[at]gmail.com

	
	NOTE:	The software could run faster because some write function read the current 
			register value before they write to it, but it shouldn't matter in usual setups.
			If you need it super fast, you probably need to program your own write functions.

INSTALL

	pca9685 requires an installed version of wiringPi from git:git.drogon.net/wiringPi
	
	You can include pca9685.h and pca9685.c directly in your project
	or compile it and use as lib file instead.
	
	To compile, navigate into the src folder an run
	
		sudo make install

	This will install pca9685 in your /usr/lib, /usr/local/lib and /usr/local/include directories.
	
	To include the files add the line
	
		#include <pca9685.h>
		
	into your source code and include
	
		wiringPiPca9685
	
	in your linked files during compilation

FUNCTIONS

	Use	
		
		int pca9685Setup(const int pinBase, const int i2cAddress/* = 0x40*/, float freq/* = 50*/);
 
	to setup a single pca9685 device at the specified i2c address and PWM frequency.
	
	Parameters are:
	
		- pinBase: 		Use a pinBase > 64, eg. 300
		- i2cAddress:	The default address is 0x40
		- freq:			Frequency will be capped to range [40..1000] Hertz. Try 50 for servos
	
	When successful, this will reserve 17 pins in wiringPi and return a file descriptor with 
	which you can access advanced functions (view below).

	The pca9685 pins are as follows: 
	
		[0...15]: The 16 individual output pins as numbered on the driver
		[16]: All pins (Note that reading from this pin returns always 0)
	
	Use the following wiringPi functions to read and write PWM.
	NOTE: 	Don't forget to add the pin base!
	
	
	Set PWM

		void pwmWrite (int pin, int value)
			if value <= 0, set full-off
			else if value >= 4096, set full-on
			else set PWM

	Set full-on or full-off
	
		void digitalWrite (int pin, int value)
			if value != 0, set full-on
			else set full-off

	Read off-register
	
		int digitalRead (int pin)
			To get PWM: mask with 0xFFF
			To get full-off bit: mask with 0x1000
			Note: ALL_LED pin will always return 0

	Read on-register
	
		int analogRead (int pin)
			To get PWM: mask with 0xFFF
			To get full-on bit: mask with 0x1000
			Note: ALL_LED pin will always return 0
	
	
	
	NOTE: 	Unfortunately wiringPi doesn't offer suitable names for pca9685's functions,
			so we have to work with the provided ones. 
			
			Masking means to bitwise-AND (operator &) the return value with the mask.
			e.g. 
				int offValue = digitalRead(pinBase + 0) & 0xFFF;
			
			
	
ADVANCED		
	
	If you don't want to use the wiringPi functions or want to access the pca9685
	directly, you can use the file descriptor returned from the setup function to access 
	the following functions for each connected pca9685 individually.
	(View source code for more details)
	
	Set output frequency in a range between 40 and 1000 Hertz
	
		void pca9685PWMFreq(int fd, float freq);
		
	Reset all PWM output of this device to default state which is full-off
	
		void pca9685PWMReset(int fd);
	
	Write PWM on and off values to a specific pin. (View source code)
		void pca9685PWMWrite(int fd, int pin, int on, int off);
		void pca9685PWMRead(int fd, int pin, int *on, int *off);

	Write enable or disable full-on and full-off of a specific pin. (View source code)
		void pca9685FullOn(int fd, int pin, int tf);
		void pca9685FullOff(int fd, int pin, int tf);
			
			
			