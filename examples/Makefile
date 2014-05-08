##########################################################################
# Makefile examples
#
# This software is a devLib extension to wiringPi <http://wiringpi.com/>
# and enables it to control the Adafruit PCA9685 16-Channel 12-bit
# PWM/Servo Driver <http://www.adafruit.com/products/815> via I2C interface.
#
# Copyright (c) 2014 Reinhard Sprung
#
# If you have questions or improvements email me at
# reinhard.sprung[at]gmail.com
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# The given code is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You can view the contents of the licence at <http://www.gnu.org/licenses/>.
##########################################################################


#DEBUG	= -g -O0
DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS	= -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685

# Should not alter anything below this line
###############################################################################

SRC	=	servo.c reset.c calibrate.c leds.c piezo.c

OBJ	=	$(SRC:.c=.o)

BINS=	$(SRC:.c=)

all:	$(BINS)

servo:	servo.o
	@echo [link]
	@$(CC) -o $@ servo.o $(LDFLAGS) $(LDLIBS)
	
calibrate:	calibrate.o
	@echo [link]
	@$(CC) -o $@ calibrate.o $(LDFLAGS) $(LDLIBS)
	
leds:	leds.o
	@echo [link]
	@$(CC) -o $@ leds.o $(LDFLAGS) $(LDLIBS)
	
piezo:	piezo.o
	@echo [link]
	@$(CC) -o $@ piezo.o $(LDFLAGS) $(LDLIBS)
	
reset:	reset.o
	@echo [link]
	@$(CC) -o $@ reset.o $(LDFLAGS) $(LDLIBS)
	
.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "[Clean]"
	@rm -f $(OBJ) *~ core tags $(BINS)

tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)

depend:
	makedepend -Y $(SRC)

# DO NOT DELETE
