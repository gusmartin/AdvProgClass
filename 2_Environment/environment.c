/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    processes.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 16, 2017 15:53
 *
 * @brief   This program shows how to access the environment of a
 *          UNIX process
 *
 * References:
 *          Based on code from Stevens UNIX book. However, the code
 *          has been changed to make it easier to understand.
 *
 * Restrictions:
 *          From the command line type: processes var
 *          Prints the value of the environment variable var, if
 *          there are no arguments it prints all the environment
 *          variables.
 *
 * Revision history:
 *          Jan 16, 2017 15:53 -- File created
 *
 * @note    For the TC2025 class (matches Topic II example)
 *
 */

/********************************************************************* 
 * Define file dependencies and global constants                     * 
 ********************************************************************/

#include <stdlib.h>                   /* Used for getenv definition */
#include <stdio.h>                              /* Used for fprintf */
#include <string.h>                              /* Used for strcmp */ 

const int NUMPAR = 2;
extern char **environ;                         /* Array of strings */

/********************************************************************* 
 *  Main entry point from the programmer's point of view             * 
 ********************************************************************/
int main (int argc, const char * argv[]) {
  
  int i;

  if (NULL == *environ){
    return (EXIT_FAILURE);
  } else {

#ifdef DEBUG
    for (i = 0; i< argc; i++){
      printf ("Argument %d = %s\n", i, argv[i]);
    }
#endif

    if (argc < NUMPAR){
      /* Print all the environment variables */
      for (i = 0; NULL != environ[i]; i++){
        printf ("%s\n", environ[i]);
      }
    } else {
	  // printf("Access just the TERM_PROGRAM:\n");
      //printf("value: %s\n", getenv("TERM_PROGRAM"));

      printf("Access just the environment variable: %s\n", argv[1]);
      printf("value: %s\n", getenv(argv[1]));
    }

    return (EXIT_SUCCESS);               /* Tell the OS all went OK */
  }
}
