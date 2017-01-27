/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    copyUnbuffered.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 16 09:43 2017
 *
 * @brief   Shows how un-bufferend data transfers take place.
 *          Note that the buffer is handled by the user. The
 *          buffer size is set based on the OS page size.
 *
 * References:
 *          Original code started in stack overflow, but have
 *          made minor changes to the source code.
 *
 * Restrictions:
 *          There is no error checking
 *
 * Revision history:
 *          Jan 16 09:43 2017 -- File created
 *
 * @note    Meant for TC2025 class
 *
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFSIZE 4096

int main(void)
{
  int     n;
  char    buf[BUFFSIZE];
  
  while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0){
	if (write(STDOUT_FILENO, buf, n) != n){
	  printf("write error\n");
	  exit(1);
    }
  }
  
  if (n < 0){
	printf("read error\n");
	exit(1);
  }
  
  exit(0);
}
