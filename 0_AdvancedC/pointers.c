/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    pointers.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 9, 10:25 2017
 *
 * @brief   This file tests basic pointer concepts in C
 *
 * References:
 *          The code is my own code. Its too simple to worry about copyright.
 *
 * Restrictions:
 *          There is no error checking. The code is meant to fail in some
 *          cases.
 *
 * Revision history:
 *          Jan 9, 10:25 2017 -- File created from original code.
 *
 * @note    The code is meant for the TC2025 class.
 *
 */
#include <stdio.h>                        /* Used for printf() functions */
#include <stdlib.h>                                   /* Used for exit() */

int main (void){
    
    int i = 10;
    int j = 100;
    int *p, *q;

    q = &i;                   /* Get the address of i. Note the %p */
    printf ("The address of i(p) is %p, the content is %d\n", q, *q);
    
    /* Now assign pointers */
    p = q;
    printf ("The content of *(p = q) is %d\n", *p);
    
    /* Basic pointer arithmetic */
    printf ("Variable j is at address %p\n", &j);
    
    --p;
    printf ("Now --p(j) is %p. The content of *(--p) is %d\n", p, *p);
    
    p++;
    printf ("The content of *(p++) (i) is %d\n", *p);
    
    p++;
    printf ("The content of *((p++)++) is %d (garbage)\n", *p);
    
    
    return (EXIT_SUCCESS);
}
