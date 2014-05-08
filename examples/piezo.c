/*************************************************************************
 * piezo.c
 *
 * PCA9685 piezoelectric plate example
 * Make some noize!
 *
 * For this to work, you need to wire a piezoelectric plate, piezo ceramic
 * disk, buzzer, etc... and a ~1K resistor in series between any PWM pin
 * and ground.
 * (http://en.wikipedia.org/wiki/File:2007-07-24_Piezoelectric_buzzer.jpg)
 * The sound volume is greatly increased if you mount it to some sort of
 * self-built resonating body or empty soda can.
 *
 * Side note: The PCA9685 is very limited in which frequencies can be played
 * since this is not the intended way to use it. However, it it is quite
 * capable of playing several usable frequencies between 40 and 260 hertz.
 *
 *
 * ***********************************************************************
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

#include <math.h>
#include <stdio.h>

#define PIN_BASE 300
#define SCALE_SIZE 35
#define MEASURE_TIME 2000
#define A4 440

// The length of a beat
#define _4_4 1.0f
#define _3_4 0.75f
#define _1_2 0.5f
#define _3_8 0.375f
#define _1_4 0.25f
#define _1_8 0.125f
#define _1_16 0.0625f
#define _0 0.01f

/**
 * The notes of the scale
 * (This is the german type annotation)
 */

typedef enum
{
	_ = -1, D1, Dis1, E1, F1, Fis1, G1, Gis1, A1, B1, H1,
	C, Cis,	D, Dis, E, F, Fis, G, Gis, A, B, H,
	c, cis,	d, dis, e, f, fis, g, gis, a, b, h,
	c1
} Note;


float scale[SCALE_SIZE];
int fd;
int playing = 0;


/**
 * http://en.wikipedia.org/wiki/Piano_key_frequencies
 */
float getFrequency(float a4, int key)
{
	float freq = a4 * pow(2, (key - 49.0f) / 12.0f);
	return freq;
}

/**
 * Generate frequencies and start at piano key 6
*/
void generateScale(float a4)
{
	int i;
	for (i = 0; i < SCALE_SIZE; i++)
	{
		scale[i] = getFrequency(a4, i + 6);
//		printPrescale(scale[i]);
	}
}

/**
 * Plays a note.
 * Turns off PWM if note is silent or
 * plays a rectangular wave when there is a note
 */
void playNote(Note note, float beat)
{
	if (note == _)
	{
		if (playing)
		{
			pca9685FullOff(fd, 16, 1);
			playing = 0;
		}
	}
	else
	{
		if (!playing)
		{
			pca9685PWMWrite(fd, 16, 0, 2048);
			playing = 1;
		}

		pca9685PWMFreq(fd, scale[note]);
	}

	delay(MEASURE_TIME * beat);
}

/**
 * Play the musical scale from bottom to top
 */
void playScale()
{
	pca9685PWMWrite(fd, 16, 0, 2048);

	int i;
	for (i = 0; i < SCALE_SIZE; i++)
	{
		pca9685PWMFreq(fd, scale[i]);
		delay(500);
	}

	pca9685FullOff(fd, 16, 1);
}

/**
 * Plays a tune. Who can guess which one?
 */
void playTune()
{
	playNote(G, _3_8);	playNote(D, _1_8);	playNote(G, _3_8);	playNote(D, _1_8);
	playNote(G, _1_8);	playNote(D, _1_8);	playNote(G, _1_8);	playNote(H, _1_8);	playNote(d, _1_2);	playNote(_, _0);
	playNote(c, _3_8);	playNote(A, _1_8);	playNote(c, _3_8);	playNote(A, _1_8);
	playNote(c, _1_8);	playNote(A, _1_8);	playNote(Fis, _1_8);	playNote(A, _1_8);	playNote(D, _1_2);	playNote(_, _0);

	playNote(G, _1_4);	playNote(G, _3_8);	playNote(H, _1_8);	playNote(A, _1_8);	playNote(G, _1_8);
	playNote(G, _1_8);	playNote(Fis, _1_8);	playNote(Fis, _3_8);	playNote(A, _1_8);	playNote(c, _1_8);	playNote(Fis, _1_8);
	playNote(A, _1_8);	playNote(G, _1_8);	playNote(G, _3_8);	playNote(H, _1_8);	playNote(A, _1_8);	playNote(G, _1_8);
	playNote(G, _1_8);	playNote(Fis, _1_8);	playNote(Fis, _3_8);	playNote(A, _1_8);	playNote(c, _1_8);	playNote(Fis, _1_8);
	playNote(G, _1_8);	playNote(G, _1_8);	playNote(G, _1_16);	playNote(Fis, _1_16);	playNote(E, _1_16);	playNote(Fis, _1_16);
	playNote(G, _1_8);	playNote(G, _1_8);	playNote(H, _1_16);	playNote(A, _1_16);	playNote(G, _1_16);	playNote(A, _1_16);
	playNote(H, _1_8);	playNote(H, _1_8);	playNote(d, _1_16);	playNote(c, _1_16);	playNote(H, _1_16);	playNote(c, _1_16);		playNote(d, _1_2);	playNote(_, _0);

	playNote(d, _1_2);	playNote(e, _1_2);
	playNote(d, _1_8);	playNote(c, _1_8);	playNote(c, _1_8);	playNote(c, _1_8);	playNote(c, _1_8);	playNote(H, _1_8);	playNote(H, _1_8);	playNote(H, _1_8);
	playNote(H, _1_8);	playNote(A, _1_8);	playNote(A, _1_8);	playNote(A, _1_8);	playNote(G, _1_8);	playNote(Fis, _1_8);	playNote(E, _1_8);	playNote(Fis, _1_8);
	playNote(G, _1_4);	playNote(A, _1_4);	playNote(H, _1_2);	playNote(_, _0);

	playNote(d, _1_2);	playNote(e, _1_2);
	playNote(d, _1_8);	playNote(c, _1_8);	playNote(c, _1_8);	playNote(c, _1_8);	playNote(c, _1_8);	playNote(H, _1_8);	playNote(H, _1_8);	playNote(H, _1_8);
	playNote(H, _1_8);	playNote(A, _1_8);	playNote(A, _1_8);	playNote(A, _1_8);	playNote(G, _1_8);	playNote(Fis, _1_8);	playNote(E, _1_8);	playNote(Fis, _1_8);
	playNote(G, _1_4);	playNote(H, _1_4);	playNote(G, _1_4);	playNote(_, _0);
}

int main(void)
{
	printf("PCA9685 piezo ceramic disk example.\nThis example plays a tune on a piezo ceramic disk if wired to one of the PWM pins.\nView info on top of file for more info.\n");

	fd = pca9685Setup(PIN_BASE, 0x40, 0);
	if (fd < 0)
	{
		printf(" Error in setup\n");
		return fd;
	}
	pca9685PWMReset(fd);

	generateScale(A4);
//	playScale();
	playTune();

	return 0;
}
