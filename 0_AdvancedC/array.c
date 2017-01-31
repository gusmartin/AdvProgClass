/**
 * @copyright (c) 2017 Abelardo López Lagunas
 *
 * @file    arrays.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 9, 2017 09:02
 *
 * @brief   Test the assignment of memory locations in C
 *
 * References:
 *          The file was created based on several comment threads from
 *          Stack Overflow
 *
 * Restrictions:
 *          There is no error checking. The code is meant to fail in some
 *          cases.
 *
 * Revision history:
 *          Jan 9, 2017 09:02 -- File created from original code. Added code
 *                            to show how the compiler does memory layout.
 *
 * @note    The code is meant for the TC2025 class. Those using llvm will
 *          see a lot of warnings, this is good since the code is meant
 *          to be incorrect by design.
 *
 */

#include <stdio.h>                     /* Used for (f)printf() functions */
#include <stdlib.h>                                   /* Used for exit() */

#define ROWS 2         // Use #defines to declare constants to
#define COLS 2         // eliminate a warning about constant arrays

int  array[ROWS] = {0,1};                 /* Declares a global array */
int  data = 8;

int brray[ROWS][COLS] = {{0,1},{2,3}};
int another = 100;

int main (void){

    int  data1 = 5;     /* Note thow arr[2] is 5!, Stacks grow backwards */
    int  arr[ROWS] = {2,3};
    int  data2 = 10;

    printf ("Testing the assignment of the array\n");
    printf ("array[0]= %d, array[1]= %d, array[2]= %d (incorrect)\n",
     		array[0], array[1], array[2]);

    printf ("\nTesting the assignment of multidimentional arrays\n");
    printf ("brray[0][1]=%d, brray[1][0]=%d, brray[2][0]=%d (incorrect)\n",
            brray[0][1], brray[1][0], brray[2][0]);

	/* See the addresses of the local variables */
	printf ("\nThe compiler can re-arrange the layout of the variables\n");
	printf ("Address of data1 is %p\n", (void *) &data1);
	printf ("Address of arr   is %p\n", (void *) arr);
	printf ("Address of data2 is %p\n", (void *) &data2);

    /* Now test it using local variables */
    printf ("\nTesting memory allocation for local variables\n");
    printf ("arr[0]= %d, arr[1]= %d, arr[2]= %d\n", arr[0], arr[1], arr[2]);
	printf ("arr[-1]= %d, arr[-2]= %d, arr[-3]= %d\n", arr[-1], arr[-2], arr[-3]);

	/* Prevent unused variable elimination by the compiler */
	brray[0][0] = data1 + data2;

    /* Now test a segmentation fault */
    printf ("\nTesting a potential segmentation fault\n");
    printf ("arr[100]  = %d\n", arr[100]);
    printf ("arr[1000] = %d\n", arr[1000]);

    return (EXIT_SUCCESS);
}
