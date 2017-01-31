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
TARGET_1= 1_Simple
TARGET_2= 2_Space
TARGET_3= 3_Mutex
TARGET_4= 4_ParallelSum
TARGET_5= 5_ParallelSumImproved
TARGET_6= 6_ParallelSumCLI
TARGET_7= 7_ProdCons
TARGET_8= 8_ProdConsComplex
SRC_1=    1_Simple.c
SRC_2=    2_Space.c
SRC_3=    3_Mutex.c
SRC_4=    4_ParallelSum.c
SRC_5=    5_ParallelSumImproved.c
SRC_6=    6_ParallelSumCLI.c
SRC_7=    7_ProdCons.c
SRC_8=    8_ProdConsComplex.c

#
# Rule definitions for target builds, again not efficient
#
all: simple space mutex parallel parImproved parCLI prodCons prodComplex

simple:
	$(CC) $(COPT2) -o $(TARGET_1) $(SRC_1)

space:
	$(CC) $(COPT2) -o $(TARGET_2) $(SRC_2)

mutex:
	$(CC) $(COPT2) -o $(TARGET_3) $(SRC_3)

parallel:
	$(CC) $(COPT2) -o $(TARGET_4) $(SRC_4)

parImproved:
	$(CC) $(COPT2) -o $(TARGET_5) $(SRC_5)

parCLI:
	$(CC) $(COPT2) -o $(TARGET_6) $(SRC_6)

prodCons:
	$(CC) $(COPT2) -o $(TARGET_7) $(SRC_7)

prodComplex:
	$(CC) $(COPT2) -o $(TARGET_8) $(SRC_8)

debug:
	$(CC) $(CDBG) -o $(TARGET_1) $(SRC_1)
	$(CC) $(CDBG) -o $(TARGET_2) $(SRC_2)
	$(CC) $(CDBG) -o $(TARGET_3) $(SRC_3)
	$(CC) $(CDBG) -o $(TARGET_4) $(SRC_4)
	$(CC) $(CDBG) -o $(TARGET_5) $(SRC_5)
	$(CC) $(CDBG) -o $(TARGET_6) $(SRC_6)
	$(CC) $(CDBG) -o $(TARGET_7) $(SRC_7)
	$(CC) $(CDBG) -o $(TARGET_8) $(SRC_8)

clean:
	rm -f *~ core

clobber: clean
	rm -f $(TARGET_1) $(TARGET_2) $(TARGET_3) $(TARGET_4) $(TARGET_5)
	rm -f $(TARGET_6) $(TARGET_7) $(TARGET_8)
