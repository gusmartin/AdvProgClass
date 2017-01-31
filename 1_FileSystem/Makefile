###########################################################################
#
# File name:    Makefile
#
# Description:  Makefile for the File System examples
#
# History:
#
#          Tue Jan 31 11:27 2017-- file is created
#
###########################################################################
#
# Define the compiler optimization flags
COPT    = -O2
COPT2   = -Wall -pedantic -O2
CDBG    = -g -DDEBUG
CC      = gcc
#
# Define the target names, not efficient but illustrative
#
TARGET_1= buffered
TARGET_2= unbuffered
SRC_1=    copyBuffered.c
SRC_2=    copyUnbuffered.c

#
# Rule definitions for target builds, again not efficient
#
all: buffered unbuffered

buffered:
	$(CC) $(COPT2) -o $(TARGET_1) $(SRC_1)

unbuffered:
	$(CC) $(COPT2) -o $(TARGET_2) $(SRC_2)

debug:
	$(CC) $(CDBG) -o $(TARGET_1) $(SRC_1)
	$(CC) $(CDBG) -o $(TARGET_2) $(SRC_2)

clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_1) $(TARGET_2)
