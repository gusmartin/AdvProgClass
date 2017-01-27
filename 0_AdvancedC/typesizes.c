/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    typesizes.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 11 11:34 2017
 *
 * @brief   ThThis file shows the amount of memory used by basic and
 *              complex types. 
 *
 * References:
 *          The code is my own code. Its too simple to worry about copyright.
 *
 * Restrictions:
 *          There is no error checking.
 *
 * Revision history:
 *          Jan 11 11:34 2017 -- File created from original code.
 *	
 * @note    The code is meant for the TC2025 class.
 */

#include <stdio.h>
#include <stdlib.h>

struct complex{
  float real;
  float imaginary;
  char  *name;
};

union tag{
  int  integer;
  char character;
};

int main(void){

  /* Display some basic system information */
  printf ("The size of an int is %lu\n", sizeof (int));
  printf ("The size of an unsigned int is %lu\n", sizeof (unsigned int));
  printf ("The size of a long int is %lu\n", sizeof (long int));
  printf ("The size of a short int is %lu\n", sizeof (short int));
  printf ("The size of a float is %lu\n", sizeof (float));
  printf ("The size of a double is %lu\n", sizeof (double));
  printf ("The size of a char is %lu\n", sizeof (char));
  printf ("The size of a pointer is %lu\n", sizeof (void *));

  /* Now show the size of a complex structure */
  printf ("The size for the structure complex is %lu\n",
          sizeof (struct complex));
  printf ("The size for the structure tag is %lu\n",
          sizeof (union tag));

   return (EXIT_SUCCESS);
}
