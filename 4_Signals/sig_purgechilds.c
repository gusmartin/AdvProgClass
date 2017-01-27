/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    sig_purgechilds.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 19, 2017 08:07
 *
 * @brief   The parent process pulls a child exit status when
 *          the OS notifies a child status change.
 *
 * References:
 *          Created by Mij <mij@bitchx.it> on 04/01/05.
 *          Original source file available at
 *              http://mij.oltrelinux.com/devel/unixprg/
 *          Some modifications done to make code intention
 *          more amenable for students.
 *
 * Restrictions:
 *          There is almost no error checking
 *
 * Revision history:
 *          Jan 19, 2017 08:07 -- File created
 *
 * @note    Created for the TC2025 class
 *
 */

#include <stdio.h>       // For printf() and fgetc()
#include <unistd.h>      // sleep(), getpid()
#include <stdlib.h>      // For srandom() and random()
#include <time.h>        // For time() [seeding srandom()]
#include <sys/wait.h>    // For waitpid()
#include <signal.h>      // For signal(), kill() and raise()

const int NUM_PROCS = 5; // How many childs to create


/* handler prototype for SIGCHLD */
void child_handler(int);

int main(int argc, char *argv[])
{
    int i, exit_status;
    
    /* execute child_handler() when receiving a signal of type SIGCHLD */
    signal(SIGCHLD, &child_handler);

    /* Seed the random num generator */
    srandom(time(NULL));
    
    printf("Issue a \'top\' while the process is running...\n");
    
    /* produce NUM_PROCS childs */
    for (i = 0; i < NUM_PROCS; i++) {
        if (! fork()) {
            /* child */
            
            /* choosing a random exit status between 0 and 99 */
            exit_status = (int)(random() % 100);
            printf(" -> New child %d, will exit with %d\n",
				   (int)getpid(), exit_status);
            
            /* try to skip signals overlapping */
            sleep((unsigned int)(random() % 3));
            
            /* choosing a value to exit between 0 and 99 */
            exit(exit_status);
        } 
        
        /* father */
        sleep((unsigned int)(random() % 2));
    }

    /* checkpoint */
    printf("parent: done with creating processes\n");

    /* why this is not equivalent to sleep(10) here? */
	for (i = 0; i < 10; i++) {
	  sleep(1);
	}
	/* all the child processes should be done now */
	printf("I did not purge all the childs. Timeout; exiting\n");
	
    /* terminate myself => exit */
    kill(getpid(), 15);
    
    /* this won't be actually executed */
    return 0;
}


/* handler definition for SIGCHLD */
void child_handler(int sig_type)
{
    int child_status;
    pid_t child;
    static int call_num = 0;

    /* getting the child's exit status */
    child = waitpid(0, &child_status, 0);
    
    printf("<-  Child %d exited with status %d\n", child,
		   WEXITSTATUS(child_status)); 
    
    /* did we get all the childs? */
    if (++call_num >= NUM_PROCS) {
        printf("I got all the childs this time. Going to exit\n");
        exit (0);
    }
    
    return;
}
