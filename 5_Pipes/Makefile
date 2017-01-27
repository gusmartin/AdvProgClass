###########################################################################
#
# File name:    Makefile
#
# Description:  Makefile for the fork/exec examples
#
# History:
#
#          Wed Jan 26 10:28 2017 -- file is created
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
TARGET_1= simple
TARGET_2= parentChild
TARGET_3= parallelAdd
TARGET_4= correctParallelAdd
TARGET_5= complex
SRC_1= 1_simplePipe.c
SRC_2= 2_parentChild.c
SRC_3= 3_parallelAdd.c
SRC_4= 4_reallyParallelAdd.c
SRC_5= 5_complexPipes.c
#
# Rule definitions for target builds, again not efficient
#
all:
	$(CC) $(COPT2) -o $(TARGET_1) $(SRC_1)
	$(CC) $(COPT2) -o $(TARGET_2) $(SRC_2)
	$(CC) $(COPT2) -o $(TARGET_3) $(SRC_3)
	$(CC) $(COPT2) -o $(TARGET_4) $(SRC_4)
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
