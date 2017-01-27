/**
 * @copyright (c) 2017 Abelardo López Lagunas
 * 
 * @file    limits.c
 *
 * @author  Abelardo López Lagunas
 *
 * @date    Jan 16, 2017 15:50
 *
 * @brief   This program shows how to access the limits imposed by
 *          the OS to a process.
 *
 * References:
 *          The code was based on the program in Figure 7.16 of
 *          the Steven's UNIX book.
 *
 * Restrictions:
 *          Only works on UNIX systems
 *
 * Revision history:
 *          Jan 16, 2017 15:50 -- File created
 *
 * @note    For the TC2025 class
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

/*
 * Create a macro that calls the pr_limits function also
 * define the pr_limits function prototype.
 */
#define Print(name)  PrintLimits(#name, name)

static void PrintLimits(char *name, int resource);

int main(void)
{
  /* 
   * Selectively call the doit macro depending on the
   * presence of the specific limit.
   */
  printf("Resource\tSoft limit  Hard limit\n");
  printf("--------------+------------+----------\n");

#ifdef  RLIMIT_AS
    Print(RLIMIT_AS);
#endif

    Print(RLIMIT_CORE);
    Print(RLIMIT_CPU);
    Print(RLIMIT_DATA);
    Print(RLIMIT_FSIZE);

#ifdef  RLIMIT_MEMLOCK
    Print(RLIMIT_MEMLOCK);
#endif

#ifdef RLIMIT_MSGQUEUE
    Print(RLIMIT_MSGQUEUE);
#endif

#ifdef RLIMIT_NICE
    Print(RLIMIT_NICE);
#endif

    Print(RLIMIT_NOFILE);

#ifdef  RLIMIT_NPROC
    Print(RLIMIT_NPROC);
#endif

#ifdef RLIMIT_NPTS
    Print(RLIMIT_NPTS);
#endif

#ifdef  RLIMIT_RSS
    Print(RLIMIT_RSS);
#endif

#ifdef  RLIMIT_SBSIZE
    Print(RLIMIT_SBSIZE);
#endif

#ifdef RLIMIT_SIGPENDING
    Print(RLIMIT_SIGPENDING);
#endif
	
    Print(RLIMIT_STACK);
	
#ifdef RLIMIT_SWAP
    Print(RLIMIT_SWAP);
#endif
	
#ifdef  RLIMIT_VMEM
    Print(RLIMIT_VMEM);
#endif
	
	/* Program terminated normally */
	exit(0);
}

/* pr_limits function definition */
static void PrintLimits(char *name, int resource)
{
  struct rlimit       limit;
  unsigned long long  lim;

  if (getrlimit(resource, &limit) < 0){
	printf("getrlimit error for %s", name);
	exit(1);
  }
  printf("%-14s  ", name);
  if (limit.rlim_cur == RLIM_INFINITY) {
	printf("(infinite)  ");
  } else {
	lim = limit.rlim_cur;
	printf("%10lld  ", lim);
  }
  if (limit.rlim_max == RLIM_INFINITY) {
	printf("(infinite)");
  } else {
	lim = limit.rlim_max;
	printf("%10lld", lim);
  }
  putchar((int)'\n');
}
