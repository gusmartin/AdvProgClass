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
TARGET_1= array
TARGET_2= memcopy
TARGET_3= pointers
TARGET_4= static
TARGET_5= typesizes
SRC_1=    array.c
SRC_2=    memcopy.c
SRC_3=    pointers.c
SRC_4=    static.c
SRC_5=    typesizes.c
#
# Rule definitions for target builds, again not efficient
#
all: array memcopy pointers static typesizes

array:
	$(CC) $(COPT2) -o $(TARGET_1) $(SRC_1)

memcopy:
	$(CC) $(COPT2) -o $(TARGET_2) $(SRC_2)

pointers:
	$(CC) $(COPT2) -o $(TARGET_3) $(SRC_3)

static:
	$(CC) $(COPT2) -o $(TARGET_4) $(SRC_4)

typesizes:
	$(CC) $(COPT2) -o $(TARGET_5) $(SRC_5)

debug:
	$(CC) $(CDBG) -o $(TARGET_1) $(SRC_1)
	$(CC) $(CDBG) -o $(TARGET_2) $(SRC_2)
	$(CC) $(CDBG) -o $(TARGET_3) $(SRC_3)
	$(CC) $(CDBG) -o $(TARGET_4) $(SRC_4)
	$(CC) $(CDBG) -o $(TARGET_5) $(SRC_5)

clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_1) $(TARGET_2) $(TARGET_3) $(TARGET_4) $(TARGET_5)
