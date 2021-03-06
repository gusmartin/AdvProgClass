/**
 * @copyright (c) 2018 
 * 
 * @file    findNumber.c
 *
 * @author  Gustavo Martin
 *
 * @date    Feb 12, 2018
 *
 * @brief   Searches a number within a given range, for accomplishing the task the
 *			program uses a number of child processes that are specified in a variable.
 *			If the number is found it prints which process found it, if it is not found
 *			it displays number not found
 *
 *
 * Revision history:
 *          Mon 12 Feb 2018  -- Created file
 *
 * Restrictions:
 *          If parent finds the number it doesn´t wait for the childs
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Used for fork()
#include <sys/types.h>  // Used for pid_t
#include <sys/wait.h>   // Used for wait()

#define processes 4		//number of processes to use
#define range 1000  	//performs a search from 0 to range-1
#define number 999		//this will be the number to find

int main(void){

	int status;            // Value to be passed from child to parent
	
	/*store the pid of the childs*/
	pid_t pid[processes];    
	

	/**
	  *
	  * found = 2
	  * not found = 3
	  *
	  */

	/* creates (proccesses - 1) childs */
	for(int i = 1 ; i < processes; i++){ 
	
		pid[i] = fork();
		
		if (pid[i] == 0) {   // The child process
		
			printf("Child PID[%d] = %d\n", i,getpid());
		
			for(int j = (range/processes)*i; j <= ((range/processes)*(i+1))-1; j++){ //these are the formulas to divide the search in equal parts
				
				/* if found number notify the parent */
				if(j == number)
					return 2;
				
			}
			
			/* this means number not found in this area*/
			/* this return is key, because it ensures the child stays in this if*/
			return 3;
		}
			
			
	}
		
	printf("Parent PID = %d\n", getpid());
	
	/* Parent proccess always searches the first block */
	for(int i = 0; i <= (range/processes)-1 ; i++){ 
		
		if(i == number){
			
			printf("found by = %d\n", getpid());
			return EXIT_SUCCESS;
		}
	}
	
	for(int i = 1; i < processes; i++){
	
    	/* wait for the childs */
		while ( waitpid(pid[i], &status, WNOHANG) == 0 ) sleep(1);
		
		//printf("WEXITSTATUS(status) = %d\n",WEXITSTATUS(status));
		
		if (WEXITSTATUS(status) == 2){
			
		  	printf("found by = %d\n", pid[i]);
		  	return EXIT_SUCCESS;
		}		  
	}

	printf("Number not found, sorry\n");  
	  
	return EXIT_SUCCESS;
}
