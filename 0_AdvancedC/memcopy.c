/**
 * @copyright (c) 2017 Abelardo López Lagunas
 *
 * @file    memcopy.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan  9 09:41 2017
 *
 * @brief   Shows how to use pointers to copy blocks of memory
 *
 * References:
 *          The code is probably in the K&R book but I am not sure. It is
 *          very common so there should be no copyright.
 *
 * Restrictions:
 *          There is no error checking. The code is meant to fail in some
 *          cases.
 *
 * Revision history:
 *          Jan 9 09:41 2017 -- File created from original code. Added constants
 *                            for the source and destination array sizes.
 *
 * @note    The code is meant for the TC2025 class.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SRC_SIZE  5        // Use #defines to declare constants to
#define DES_SIZE 10        // eliminate a warning about constant arrays

int main(void){

   	int i;
   	int dest[DES_SIZE] = {0};
    int src[SRC_SIZE] =  {1, 2, 3, 4, 5};

    printf ("Array before memcpy\n");
	for (i = 0; i < DES_SIZE; i++)
		printf("%i\n", dest[i]);

	memcpy (dest, src, sizeof(int)*SRC_SIZE);
// Tyr the following:
	//memcpy (&dest[6], src, sizeof(int)*SRC_SIZE);

   	printf("Array after memcpy\n");
   	for (i = 0; i < DES_SIZE; i++)
		printf("%i\n", dest[i]);

   	return (EXIT_SUCCESS);
}
