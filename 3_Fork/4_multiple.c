/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    4_multiple.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 18, 2017 09:48
 *
 * @brief   Shows how to use fork(), exec(), waitpid(), getpid()
 *          among others. It is menat to show child-parent interaction.
 *
 * References:
 *          Based on Mij <mij@bitchx.it> excample that was
 *          modified to show more detailed interactions.
 *          Original source file available on
 *                   http://mij.oltrelinux.com/devel/unixprg/
 *
 * Restrictions:
 *          There is little or no validation of error conditions.
 *
 * Revision history:
 *          Thu 11 Feb 2016 11:14 -- File created
 *          Wed 18 Jan 2017 9:48  -- Added more comments & cleanup
 *
 * @warning  If the program detects an error it aborts
 *
 * @note    Use for the TC2025 class
 *
 */

#include <stdio.h>      // Used for perror()
#include <stdlib.h>     // Used for EXIT_SUCESS
#include <unistd.h>     // Used for fork()
#include <sys/types.h>  // Used for pid_t
#include <sys/wait.h>   // Used for wait()

int main(void) {
    pid_t mypid, childpid; // Parent and child PIDs
    int status;            // Value to be passed from child to parent

    mypid = getpid();      // Print parent's PID
    printf("Parent process with PID %d.\n", mypid);

	/* create the child */
    childpid = fork();
    if ( childpid == -1 ) {  // Error condition
	  perror("Cannot proceed. fork() error");
	  return 1;
    }

    if ( childpid == 0 ) {   // First child process
	  printf("Child 1: Inherited parent's pid as %d.\n", mypid);
	  /*
	   * Get child pid: notice that this doesn't touch the value
	   * of parent's "mypid" value
	   */
	  mypid = getpid();
	  printf("Child1: getppid() tells parent is %d. Own pid is %d.\n",
			 getppid(), mypid);

	  /* Create another another child */
	  childpid = fork();
	  if ( childpid == -1 ) {  // Error condition
		perror("Cannot proceed. fork() error");
		return 1;
	  }

	  if ( childpid == 0 ) {
		/* this is the child of the first child, thus "Child 2" */
		printf("Child2: Inherited parent's PID as %d.\n", mypid);

		mypid = getpid();
		printf("Child2: getppid() tells parent is %d. Own pid is %d\n"
			   , getppid(), mypid);

		childpid = fork();
		if ( childpid == -1 ) {   // Error condition
		  perror("Cannot proceed. fork() error");
		  return 1;
		}

		if ( childpid == 0 ) {
		  /*
		   * Child 3 sleeps 30 seconds then terminates, returns value of
		   * 12, hopefully before its parent Child 2
		   */
		  printf("Child3: Inherited parent's PID as %d.\n", mypid);

		  mypid = getpid();
		  printf("Child3: getppid() tells parent is %d. Own pid is %d.\n",
				 getppid(), mypid);

		  sleep(30);
		  printf("Still alive!\n");
		  return 12;
		} else   // The parent Child 2 returns 15
		  return 15;
	  } else {
		/* this Child 1, which waits for its child to exit */
		while ( waitpid(childpid, &status, WNOHANG) == 0 ) sleep(1);

		if ( WIFEXITED(status) )
		  printf("Child1: Child 2 exited with exit status %d.\n",
				 WEXITSTATUS(status));
		else
		  printf("Child 1: child has not terminated correctly\n");

		  return 2;
	  }
    } else {
	  /* then we're the parent process, "Parent" */
	  printf("Parent: fork() went ok. Child's PID is %d\n",
			 childpid);

	  /* wait for the child to terminate and report about that */
	  wait(&status);

	  if ( WIFEXITED(status) )
		printf("Parent: child has exited with status %d.\n",
			   WEXITSTATUS(status));
	  else printf("Parent: child has not terminated normally.\n");
    }

    return EXIT_SUCCESS;
}
