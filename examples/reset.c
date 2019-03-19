/*************************************************************************
 * reset.c
 *
 * PCA9685 reset
 * Simply turns off all output.
 *
 *
 * This software is a devLib extension to wiringPi <http://wiringpi.com/>
 * and enables it to control the Adafruit PCA9685 16-Channel 12-bit
 * PWM/Servo Driver <http://www.adafruit.com/products/815> via I2C interface.
 *
 * Copyright (c) 2014 Reinhard Sprung
 *
 * If you have questions or improvements email me at
 * reinhard.sprung[at]gmail.com
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The given code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You can view the contents of the licence at <http://www.gnu.org/licenses/>.
 **************************************************************************
 */

#include "pca9685.h"
#include <wiringPi.h>


#define PIN_BASE 300


int main(void)
{
	// Calling wiringPi setup first.
	wiringPiSetup();

	int fd = pca9685Setup(PIN_BASE, 0x40, 0);

	// If valid, turn off
	if (fd >= 0)
		pca9685PWMReset(fd);

	return fd;
}
