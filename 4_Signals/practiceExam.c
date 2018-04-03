#include <stdio.h>  // For printf(), exit() & exit values
#include <stdlib.h> // For exit conditions
#include <unistd.h> // For pipe constants
#include <time.h>   // For time() [seeding srandom()]
#include <math.h> 
#include <signal.h>

/* Controls the concurrency of the program*/
#define N 4         // Use this instead of a const to avoid a warning
#define NUMBER 10

int sum = 0;
int n = 0;
	
int fd[2];

int sumFunc(int count){
	
	int sumP = 0;
	
	if(count == N-1){
		
		for(int j = floor(NUMBER/N)*count; j <= NUMBER ; j++){
			sumP += j;
		
		}
	}
	
	else{
	
		for(int j = floor(NUMBER/N)*count; j <= floor((NUMBER/N))*(count+1)-1; j++){

			sumP += j;
		
		}
	}
	
	return sum;
}

void readFunc(int signal){
	
	static int signalCount;
		
	close(fd[1]);
		
	if(read(fd[0], &n, sizeof(int)) == -1)
		perror("Couldn´t read data");
		
	printf("Partial sum from thread was %d\n", n);
	
	sum += signal;
	
	signalCount++;
	
	if(signalCount == N)
		printf("sum is %d\n", sum);
}

int main(void){
		
	
	if(pipe(fd) == -1){
		perror("Couldn´t create pipe\n");
	}
	
	signal(SIGCHLD, &readFunc);
		
	for(int i = 0; i < N; i++){
		
		if(fork() == 0){
			
			close(fd[0]);
			
			n = sumFunc(i);
			
			if(write(fd[1], &n, sizeof(int)) == -1)
				perror("Couldn´t write data");
			
			return n;
		}	
	}
	
	for(int i = 0; i< 5; i++){
		
		sleep(1);
	}
	
}
