/*************************************************************************
 * calibrate.c
 *
 * PCA9685 servo calibration
 * Use this to test out the min and max millisecond values of your servo
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
#include <stdio.h>
#include <stdlib.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50

/**
 * Calculate the number of ticks the signal should be high for the required amount of time
 */
int calcTicks(float impulseMs, int hertz)
{
	float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / cycleMs + 0.5f);
}


int main(void)
{
	printf("PCA9685 servo calibration\n");
	printf("Use this to test out the min and max millisecond values of your servo\n");

	int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);
	if (fd < 0)
	{
		printf("Error in setup\n");
		return fd;
	}

	pca9685PWMReset(fd);
	printf("Frequency is set to %d hertz\n", HERTZ);


	int i, j = 1;
	int pin;
	float millis;

	while (j)
	{
		printf("Enter servo pin [0-16]: ");
		scanf("%d", &pin);

		if (pin >= 0 && pin <= 16)
		{
			millis = 1.5f;
			i = 1;

			pwmWrite(PIN_BASE + pin, calcTicks(millis, HERTZ));
			printf("Servo %d is centered at %1.2f ms\n", pin, millis);

			while (i)
			{
				printf("Enter milliseconds: ");
				scanf("%f", &millis);

				if (millis > 0 && millis <= 3)
				{
					pwmWrite(PIN_BASE + pin, calcTicks(millis, HERTZ));
					delay(1000);
				}
				else
					i = 0;
			}
		}
		else
			j = 0;
	}



	return 0;
}
