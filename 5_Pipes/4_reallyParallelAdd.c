/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    4_reallyParallelAdd.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 26, 2017 10:25
 *
 * @brief   Shows how to use pipes with multiple processes
 *
 * References:
 *          Based on "A book on C" by Al Kelley & Ira Pohl
 *
 * Restrictions:
 *          If an error is found the program is aborted
 *
 * Revision history:
 *          Jan 26, 2017 10:25 -- File created
 *
 * @warning If the program detects an error or does not handle
 *          some condition explain what happens.
 *
 * @note    Used as an example for the TC2025 class
 *
 */

#include <stdio.h>                     // For printf(), exit() & exit values
#include <stdlib.h>                    // For exit conditions
#include <unistd.h>                    // For pipe constants

/* Controls the concurrency of the program*/
#define N 3         // Use this instead of a const to avoid a warning

/* Declares the function prototypes */
int  addVector(int v[], int length);
void errorExit(char *s);

int main (void){
  
  int   array[N][N] = {{1, 1, 1},
					   {2, 2, 2},
					   {3, 3, 3}};
  int   i, row, sum = 0;
  int   pipefd[2];
  
  /* Create a simple pipe */
  if (pipe (pipefd) < 0)
	errorExit("Error creating the pipe");
  
  /*
   * Create N child processes, each adds a row of the matrix
   * Note how the parent loops three times but does nothing.
   */
  for (i = 0; i < N; i++){
	if (fork() == 0) {
	  row = addVector(array[i], N);
	  if (write (pipefd[1], &row, sizeof(int)) == -1)
		errorExit("Error writing the pipe");
	  else
		printf ("Child process %d finished working\n", getpid());
	  return (EXIT_SUCCESS);  /* child is done, terminate*/
	}
  }	
  /*
   * This is the parent process, it suspends if the data is not
   * ready for consumption in the pipe. Parent collects partial
   * sums and generates the total.
   */
  printf ("Parent will read data\n");

  for (int i = 0; i < N; i++){
	if (read (pipefd[0], &row, sizeof(int)) == -1)
	  errorExit("Error reading the pipe");
	else
	  printf ("Parent read %d\n", row);
	sum += row;
  }
  
  printf ("The total is %d\n", sum);
  return (EXIT_SUCCESS);
}

/*
 *
 *  Function: addVector
 *
 *  Purpose:  This functions receives an array and its length as
 *            inputs and adds all its elements
 *
 *  Parameters:
 *            input #1  Pointer to the array
 *            input #2  Array length
 *            output    Sum of all array elements
 *
 */
int  addVector(int v[], int length){

  int i, sum;

  for (i = 0, sum = 0; i < length; i++)
	sum += v[i];

  sleep (random() % 4);

  return (sum);
}

/*
 *
 *  Function: errorExit
 *
 *  Purpose:  This functions receives a string as an input parameter
 *            The string is printed out and then the program is
 *            aborted
 *
 *  Parameters:
 *            input #1  Pointer to the string
 *
 */
void errorExit(char *s){
  
  fprintf (stderr, "\n ERROR: %s program will abort\n", s);
  exit (EXIT_FAILURE);
}
