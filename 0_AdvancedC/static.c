/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    static.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan  9 10:39 2017
 *
 * @brief   This file shows how to use static functions in C
 *
 * References:
 *          The code is my own code. Its too simple to worry about copyright.
 *
 * Restrictions:
 *          There is no error checking. The code is meant to fail in some
 *          cases.
 *
 * Revision history:
 *          Jan  9 10:39 2017 -- File created from original code.
 *	
 * @note    The code is meant for the TC2025 class.
 */
 
#include <stdio.h>

void myFunction () {
  int static numberOfCalls = 1;  /* Allocates as global but with local scope */
  printf("This function has been called %i times\n", numberOfCalls);
  numberOfCalls++;
}

int main (void) {
  myFunction();
  myFunction();
  myFunction();
}



