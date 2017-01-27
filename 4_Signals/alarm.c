/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    alarm.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 18, 2017 12:19
 *
 * @brief   Shows how to set a timer using signals
 *
 * References:
 *          Original code was from Stack Overflow, but it has been
 *          changed to show how the signal interrupts the input
 *          capture but does not affect writing to an output file.
 *
 * Restrictions:
 *          There is no extensive error checking
 *
 * Revision history:
 *          Jan 18, 2017 12:19 -- File created
 *
 * @warning The program may abort if the signal handler can't
 *          be installed properly.
 *
 * @note    Code meant for the TC2025 class
 *
 */
#include <signal.h>    // For signal definitions
#include <stdio.h>     // For perror()
#include <unistd.h>    // For alarm, read & write

#define MAXLINE  4096

void sig_alrm(int);

int main(void)
{
	int		n;
	char	line[MAXLINE];
	
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
	perror("signal(SIGALRM) error");

	alarm(5); /* Wait 10 seconds then send a SIGALRM */

	if ( (n = read(STDIN_FILENO, line, MAXLINE)) < 0)
	  perror("read error");

	write(STDOUT_FILENO, line, n);

	return (0);
}

void sig_alrm(int signo)
{
  printf ("\nEntered handler\n");
  return;	/* nothing to do, just return to interrupt the read */
}
