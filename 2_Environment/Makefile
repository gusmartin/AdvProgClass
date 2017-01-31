###########################################################################
#
# File name:    Makefile
#
# Description:  Makefile for the environment example
#
# History:
#
#          Tue Jan 31 11:32 2017-- file is created
#
###########################################################################
#
# Define the compiler optimization flags
COPT    = -O2
COPT2   = -Wall -pedantic -O2
CDBG    = -g -DDEBUG
CC      = gcc
#
# Define the target names
#
TARGET_NAME=   environment
TARGET_NAME_2= limits
C_CSRC=        environment.c
C_CSRC_2=      limits.c

#
# Rule definitions for target builds
#
all: env limits

env:
	$(CC) $(COPT2) -o $(TARGET_NAME) $(C_CSRC)
	"./"$(TARGET_NAME) "TERM"

limits:
	$(CC) $(COPT2) -o $(TARGET_NAME_2) $(C_CSRC_2)
	"./"$(TARGET_NAME_2)

debug:
	$(CC) $(CDBG) -o $(TARGET_NAME) $(C_CSRC)
	$(CC) $(CDBG) -o $(TARGET_NAME_2) $(C_CSRC_2)

clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_NAME)
	rm -f $(TARGET_NAME_2)
