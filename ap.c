#include <stdio.h>
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#define getTime 333
#define printInfo 334
#define myAdd 335


int main ( int argc, char** argv)
{
  struct timespec start, end;
  printf("%d %d\n", syscall(getTime, &start), start.tv_nsec);
  printf("%d\n", syscall(myAdd, 1, 1));
  for(volatile int i = 0; i < 1000000000; i++);
  printf("%d %d\n", syscall(getTime, &end), end.tv_nsec);
  printf("%d \n", syscall(printInfo, getpid(), start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec));
}
