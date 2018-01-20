/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    cntrl_c.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Mar  3 15:28 2017
 *
 * @brief   Shows how to intercept the control-c signal
 *
 * References:
 *          Original code was from "A book on C" by Al
 *          Kelley & Ira Pohl
 *
 * Restrictions:
 *          There is no extensive error checking
 *
 * Revision history:
 *          Mar  3 15:28 2017 -- File created
 *
 * @warning The program may abort if the signal handler can't
 *          be installed properly.
 *
 * @note    Code meant for the TC2025 class
 *
 */
#include <signal.h>    // For signal definitions
#include <stdio.h>     // For perror()
#include <stdlib.h>    // For EXIT_SUCCESS & EXIT_FAILURE

#define LENGTH  50

// Function prototypes
void     CntrlCHandler (int signal);
unsigned fib           (int number); 

// Gloab flag used to know if we have caught a signal
unsigned char flag = 0;

int main(void) {
  char option;
  
  if (signal(SIGINT, CntrlCHandler) == SIG_ERR)
    perror("signal(SIGINT) error");

  for (int i = 0; i < LENGTH; i++){
    printf ("fib(%3d) = %u\n", i, fib(i));
    
    if (flag != 0){    // SIGINT was detected
      printf ("\nEntered handler\n");
      printf ("Do you want to continue or quit? [c,q]: ");
      scanf  ("%c", &option);
      
      if (option == 'c'){
	// On some systems after intercepting SIGINT the OS reverts
	// to the default of not catching the signal so catch it again
	if (signal(SIGINT, CntrlCHandler) == SIG_ERR)
	  perror("signal(SIGINT) error");

	flag = 0; // Reset the option
      } else
	exit (EXIT_FAILURE);
    }      
  }
  
  return EXIT_SUCCESS;
}

void CntrlCHandler (int signal) {

  flag = 1;
  
  return;
}

unsigned fib (int n){
  
  if (n <= 1)
    return 1;
  else
    return (fib(n-1) + fib (n-2));

}
