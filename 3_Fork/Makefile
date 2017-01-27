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
TARGET_1= fork
TARGET_2= fork_exec_1
TARGET_3= fork_exec_2
TARGET_4= multiple
SRC_1=    1_fork.c
SRC_2=    2_fork_exec.c
SRC_3=    3_fork_exec.c
SRC_4=    4_multiple.c
#
# Rule definitions for target builds, again not efficient
#
all:
	$(CC) $(COPT2) -o $(TARGET_1) $(SRC_1)
	$(CC) $(COPT2) -o $(TARGET_2) $(SRC_2)
	$(CC) $(COPT2) -o $(TARGET_3) $(SRC_3)
	$(CC) $(COPT2) -o $(TARGET_4) $(SRC_4)

debug:
	$(CC) $(CDBG) -o $(TARGET_1) $(SRC_1)
	$(CC) $(CDBG) -o $(TARGET_2) $(SRC_2)
	$(CC) $(CDBG) -o $(TARGET_3) $(SRC_3)
	$(CC) $(CDBG) -o $(TARGET_4) $(SRC_4)

clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_1) $(TARGET_2) $(TARGET_3) $(TARGET_4)
	rm -fr $(TARGET_1).dSYM $(TARGET_2).dSYM
	rm -fr $(TARGET_3).dSYM $(TARGET_4).dSYM
