###########################################################################
#
# File name:    Makefile
#
# Description:  Makefile for the fork/exec examples
#
# History:
#
#          Tue Jan 31 12:40 2017 -- file is created
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
TARGET_1= addressDB
TARGET_2= lookup
TARGET_3= services
SRC_1=    addressDB.c
SRC_2=    lookup.c
SRC_3=    services.c


#
# Rule definitions for target builds, again not efficient
#
all: address lookup services

address:
	$(CC) $(COPT2) -o $(TARGET_1) $(SRC_1)

lookup:
	$(CC) $(COPT2) -o $(TARGET_2) $(SRC_2)

services:
	$(CC) $(COPT2) -o $(TARGET_3) $(SRC_3)

debug:
	$(CC) $(CDBG) -o $(TARGET_1) $(SRC_1)
	$(CC) $(CDBG) -o $(TARGET_2) $(SRC_2)
	$(CC) $(CDBG) -o $(TARGET_3) $(SRC_3)

clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_1) $(TARGET_2) $(TARGET_3)
