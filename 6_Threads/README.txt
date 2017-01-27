These files are used to teach POSIX thread programming. The correct order is the following:

1. Simple.c will show how to create threads then then wait for them to finish. Thread naming is introduced but its very basic.

2. Space.c shows that data sharing should be done in the heap or through global variables and not through the stack. Need to add more comments to this code.

3. Mutex.c shows how to invoke simple mutexes. The example is contrived so it does not show an efficient use of mutexes. It does show what happens when the mutex is removed from the critical region.

4. parallelSum.c is a more advanced example of why a mutex is needed. However it is not an efficient implementation. As with the mutex example it does show what happens when the mutex code is commented out.

5. parallelSumImproved.c shows the correct way to solve the parallel sum without mutexes. It leads to the general case (6)

6. parallelSumCL.c reads the limit and # of threads to solve the problem from the command line.

7. ProdCons.c shows how conditionals are used to solve the producer consumer problem. Its simple enough to understand but may need more elaboration on the data that is accessed.

8. ProdConsComplex.c shows an example of one producer and two consumers. It can be generalized to other configurations.

9. ProdConsExam.c shows the beginning of a pipeline implementation. It needs to be generalized but its a good starting point.