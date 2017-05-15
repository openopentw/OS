#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void *thread_fun(void *ptr);

int main(int argc ,const char **agrv)
{ 
  int flag =0;
  cpu_set_t cpumask;
  CPU_ZERO(&cpumask);
  CPU_SET(0,&cpumask);
  sched_setaffinity(0,sizeof(cpumask),&cpumask);
  if (argc >= 2)
  {
    if (strcmp(agrv[1],"SCHED_FIFO")==0)
    {
      flag = 1 ;
      printf("%d\n",flag);
    }
  }
  pthread_t t1;
  pthread_t t2;
  struct sched_param par[2];
  int arr[2][1]; arr[0][0] = 1 ; arr[1][0] = 2;
  pthread_create(&t1 , NULL,thread_fun,&arr[0]);
  printf("thread 1 is created\n");
  pthread_create(&t2 , NULL,thread_fun,&arr[1]);
  printf("thread 2 is created\n");
  if (flag)
  {
    par[0].sched_priority = 99;
    pthread_setschedparam(t1,SCHED_FIFO,&par[0]);
    par[1].sched_priority = 98;
    pthread_setschedparam(t2,SCHED_FIFO,&par[1]);
  }
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
}
void *thread_fun(void *ptr)
{
    int *tmp;
    tmp = (int *)ptr;
    for(int i =0; i<3;i++){
    printf("thread %d is running\n",*tmp);
    clock_t start = clock();
    while(1){   
      clock_t t1 = clock();
      if((t1 - start) > 500000)
    	    break;
        }
    }
}
