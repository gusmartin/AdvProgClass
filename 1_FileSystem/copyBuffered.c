/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    copyBuffered.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 16 09:39 2017
 *
 * @brief   Shows how bufferend data transfers take place. Note
 *          that the buffer is handled by the OS.
 *
 * References:
 *          Original code started in stack overflow, but have
 *          made minor changes to the source code.
 *
 * Restrictions:
 *          There is no error checking
 *
 * Revision history:
 *          Jan 16 09:39 2017 -- File created
 *
 * @note    Meant for TC2025 class
 *
 */
 
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
  int c;
  
  while ((c = getc(stdin)) != EOF){
	if (putc(c, stdout) == EOF){
	  printf("output error\n");
	  exit(1);
	}
  }
	
  if (ferror(stdin)){
	printf("input error\n");
	exit(1);
  }
  
  exit(0);
}
