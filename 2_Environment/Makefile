###########################################################################
#
# File name:    Makefile
#
# Description:  Makefile for the file manipulation example
#
# History:
#
#          Fri Jan 28 10:17:24 CST 2011 -- file is created
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
TARGET_NAME= environment
TARGET_NAME_2= limits
C_CSRC= environment.c
C_CSRC_2= limits.c
#
# Rule definitions for target builds
#
all:
	$(CC) $(COPT2) -o $(TARGET_NAME) $(C_CSRC)
	$(CC)  $(COPT2) -o $(TARGET_NAME_2) $(C_CSRC_2)
	"./"$(TARGET_NAME) "TERM"
	"./"$(TARGET_NAME_2)

debug:
	$(CC) $(CDBG) -o $(TARGET_NAME) $(C_CSRC)
	$(CC) $(CDBG) -o $(TARGET_NAME_2) $(C_CSRC_2)
	
clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_NAME)
	rm -fr $(TARGET_NAME).dSYM
	rm -f $(TARGET_NAME_2)
	rm -fr $(TARGET_NAME_2).dSYM
