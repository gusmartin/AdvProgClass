/**
 * @copyright (c) 2017 Abelardo López Lagunas
 *
 * @file    2_parentChild.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 19, 2017 09:35
 *
 * @brief   Shows how a simple pipe can be shared between
 *          parent and child processes
 *
 * References:
 *          Based on the UNIX network programming book by
 *          W. Richard Stevens
 *
 * Restrictions:
 *          If an error is found the program is aborted
 *
 * Revision history:
 *          Jan 19, 2017 09:35 -- File created
 *
 * @note    Meant as an example for the TC2025 students
 *
 */
#include <stdio.h>                 // For printf(), exit(), exit values
#include <stdlib.h>                // For exit conditions
#include <unistd.h>                // For pipe constants

#define MAXLINE 50     // Use this instead of a const to avoid a warning

const int STDOUT  = 1;

int main(void)
{
    int     n;
    int     fd[2];
    pid_t   pid;
    char    line[MAXLINE];

    if (pipe(fd) < 0)
        perror("pipe error");

    if ((pid = fork()) < 0) {
        perror("fork error");
    } else if (pid > 0) {
        close(fd[0]);           /* parent */
		sleep(5);
        write(fd[1], "hello world\n", 12);
    } else {                    /* child */
        close(fd[1]);
		printf ("Waiting...\n");
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }

	return EXIT_SUCCESS;
}
