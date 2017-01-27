/**
 * @copyright (c) 2017 Abelardo López Lagunas
 *
 * @file    1_simplePipe.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 19, 2017 09:35
 *
 * @brief   Shows how a simple pipe is created and used
 *
 * References:
 *          Based on the UNIX network programming book by
 *          W. Richard Stevens
 *
 * Restrictions:
 *          If an error is found the program is aborted
 *
 * Revision history:
 *          Jan 19, 2017 09:35 -- File created
 *
 * @note    Meant as an example for the TC2025 students
 *
 */

#include <stdio.h>                 // For printf(), exit(), exit values
#include <stdlib.h>                // For exit conditions
#include <unistd.h>                // For pipe constants

const int STDOUT = 1;              // Standard output

int main (void){

	int  pipefd[2], n;            // One pipe, two directions
	char buffer[50];              // Small character buffer

	for (int i = 0; i < 50 ; i++)
	  buffer[i] = 'j';

	/* Create a simple pipe */
	if (pipe (pipefd) < 0){
	  printf("Error creating the pipe");
	  exit(EXIT_FAILURE);
	}
	/*
	 * Show the file descriptor numbers for the read and write
	 * ports of the pipe
	 */
	printf ("read fd: %d. write fd: %d\n", pipefd[0], pipefd[1]);
	if (write (pipefd[1], "hello, this is a string\n", 24) != 24){
	  printf("Error writing to the pipe");
	  exit(EXIT_FAILURE);
	}

	/* Now read n*4 bytes from the pipe, note the use of sizeof */
	n = read (pipefd[0], buffer, sizeof(buffer));
	printf ("N is %d\n",n);

	if (n <= 0){
	  printf("Error reading from the pipe");
	  exit(EXIT_FAILURE);
	}

	/* Now print the buffer to the console, i.e. stdout */
	write (STDOUT, buffer, n);

	return EXIT_SUCCESS;
}

