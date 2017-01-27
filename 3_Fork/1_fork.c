/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    1_fork.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 18, 2017 09:07
 *
 * @brief   Shows the basic usage of fork()
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
 *          Fri 12 Feb 2016 16:54 -- Added WEXITSTATUS macro call for a
 *                                   consistent (platform independent)
 *                                   result.
 *          Wed 18 Jan 2017 9:17  -- Added more comments & cleanup
 *
 * @warning  If the program detects an error it aborts
 *
 * @note    Use for the TC2025 class
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>                   // Basic Unix API e.g. fork()
#include <sys/types.h>              // For pid_t & error conditions
#include <sys/wait.h>                                   // For wait

// This function simulates a work routine
int doWork(const char *who) {
	int b = 1,a = 1;

	printf("I am PID %d Entered work function (%s)\n", getpid(), who);
	fflush(stdout); // Make sure data is sent to stdout immediately

	for (int i = 1; i < 1000; i++)       // Simulate lengthily work
           for (int j = 0; j < 1000; j++)
				b = a + b;
	sleep(5);                                   // Wait even longer
	printf("Leaving work function (%s) with value %d\n", who, b);
	fflush(stdout); // Make sure data is sent to stdout immediately

	return b;
}

/* To check the status of the parent and child run the following
 * command in another terminal window:
 *
 * 			top -stats command,pid,ppid,state
 * Then
 *     ps aux | awk '"[Zz]" ~ $8 { printf("%s, PID = %d\n", $8, $2); }'
 *
 * Unfortunately ps only gives a snapshot, but shows Zombie processes
 * Top will not display them as Zombie (displays them as sleeping).
 *
 */
int main(void) {
	int result;

	/* Clone a new process to run alongside this one */
	pid_t pid=fork();
	if (pid==0) {                     // Is this the Child process?
		result = doWork("child") + 1; // Result is 1 more tha  parent
		printf ("The result of the child is %d\n", result);
		exit(result);                 // Terminate & send result
	}
	else {                      // pid!=0 so its the parent process
	  result = doWork("parent");
	  printf ("The result of the parent is %d\n", result);
	  result = 0;      // Clear, otherwise incorrect results happen

	 // Make the child process a zombie for a 10 seconds
	  sleep (10);

	/* We get the result from the child through the exit () call.
	 * However, this only captures the low byte of result. That is
	 * the reason we cleared it before waiting for the child to
	 * exit().
	 */
	  wait(&result);                      // Wait for child to exit

	/* Instead of printing the result as is (may be implementation
	 * dependent) use the WEXITSTATUS instead which is defined as a
	 * macro: #define WEXITSTATUS(status) (((status)>>8) & 0xFF)
	 * This way we guarantee a correct value from 0 to 255 when the
	 * process terminates normally. Evidently the result from the 
	 * doWork function will be truncated.
	 */
	  printf ("The (truncated) result of the child is %d\n", WEXITSTATUS(result));
	}
	
	return EXIT_SUCCESS;
}
