/*************************************************************************
 * leds.c
 *
 * PCA9685 LED example
 * Drive some LEDs with the PCA9685
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
#include <wiringPiI2C.h>

#include <stdio.h>
#include <stdlib.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50



int main(void)
{
	printf("PCA9685 LED example\n");

	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		printf("Error in setup\n");
		return fd;
	}

	pca9685PWMReset(fd);

	int i, j;
	int active = 1;

	while (active)
	{
		for (j = 0; j < 5; j++)
		{
			for (i = 0; i < MAX_PWM; i += 32)
			{
				pwmWrite(PIN_BASE + 16, i);
				delay(4);
			}

			for (i = 0; i < MAX_PWM; i += 32)
			{
				pwmWrite(PIN_BASE + 16, MAX_PWM - i);
				delay(4);
			}
		}

		pwmWrite(PIN_BASE + 16, 0);
		delay(500);

		for (j = 0; j < 5; j++)
		{
			for (i = 0; i < 16; i++)
			{
				pwmWrite(PIN_BASE + i, MAX_PWM);
				delay(20);
			}

			for (i = 0; i < 16; i++)
			{
				pwmWrite(PIN_BASE + i, 0);
				delay(20);
			}
		}

		pwmWrite(PIN_BASE + 16, 0);
		delay(500);
	}


	return 0;
}
