#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <error.h>
#include <pthread.h>

void *thread_func1(void *args);
void *thread_func2(void *args);

int main (int argc,char * argv)
{
	pthread_t tid;
	pthread_attr_t thread_attr;
	if (pthread_attr_init(&thread_attr))
	{
		perror("pthread_attr_init() fail!");
		return -1;
	}
	if (pthread_attr_setstacksize(&thread_attr,120*1024))
	{
		perror("pthread_attr_setstacksize() fail!");
		return -2;
	}
	if (pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED))
	{
		perror("pthread_attr_setdetachstate() fail!");
		return -3;
	}
	pthread_create(&tid,&thread_attr,thread_func1,NULL);
	printf("pthread_create func1 successful!\n");
	pthread_create(&tid,NULL,thread_func2,NULL);
	printf("pthread_create func2 successful!\n");
	pthread_attr_destroy(&thread_attr);
	printf("destroy pthread_addr successful!\n");
	pthread_join(tid,NULL);
	printf("destroy pthread_addr successful!\n");

		printf("i am doing something in the main func!\n");
	return 0;
}

void *thread_func1(void *args)
{
	while(1)
	{
		printf("i am doing something in the func1................!\n");
		sleep(5);
	}
	return 0;
}
void *thread_func2(void *args)
{
		printf("i am doing something in the func2................!\n");
		sleep(50);
	return 0;
}





