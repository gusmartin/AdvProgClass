###########################################################################
#
# File name:    Makefile
#
# Description:  Makefile for the fork/exec examples
#
# History:
#
#          Wed Jan 18 11:13:03 CST 2017 -- file is created
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
TARGET_1= alarm
TARGET_2= sig_purge
SRC_1=    alarm.c
SRC_2=    sig_purgechilds.c
#
# Rule definitions for target builds, again not efficient
#
all:
	$(CC) $(COPT2) -o $(TARGET_1) $(SRC_1)
	$(CC) $(COPT2) -o $(TARGET_2) $(SRC_2)

debug:
	$(CC) $(CDBG) -o $(TARGET_1) $(SRC_1)
	$(CC) $(CDBG) -o $(TARGET_2) $(SRC_2)

clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_1) $(TARGET_2)
	rm -fr $(TARGET_1).dSYM $(TARGET_2).dSYM
