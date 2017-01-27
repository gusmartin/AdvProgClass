/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    3_fork_exec.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 18, 2017 09:26
 *
 * @brief   Shows how to use fork() and exec() on a child process.
 *          In this example just calls a command, implementing a
 *          simple shell. 
 *
 * References:
 *          Based on Orion Lawlor's Short UNIX Examples
 *          olawlor@acm.org 2004/9/5
 *
 * Restrictions:
 *          There is little or no validation of error conditions.
 *
 * Revision history:
 *          Thu 11 Feb 2016 11:14 -- File created
 *          Wed 18 Jan 2017 9:17  -- Added more comments & cleanup
 *
 * @warning  If the program detects an error it aborts
 *
 * @note    Use for the TC2025 class
 *
 */
 
#include <stdio.h>
#include <stdlib.h>     // Used for EXIT_SUCESS
#include <unistd.h>     // Used for fork()
#include <sys/types.h>  // Used for pid_t
#include <sys/wait.h>   // Used for wait()

int main(void){
	/* Spawn a child to run the program */
	pid_t pid=fork();
   
	if (pid==0) {  // The child process
		static char *argv[]={"echo","New process\n",NULL};
		execv("/bin/echo",argv);
		exit(127);    // Only if execv() fails
	} else {          // pid != 1 the parent process
		printf ("I am the parent, the PID of the child is %d\n", pid);
	waitpid(pid,NULL,0); // Wait for child to exit
	}
   
   return EXIT_SUCCESS;
}
