/*************************************************************************
    > File Name: signal.c
    > Author: malunkun
    > Mail: malunkun<209446860qq.com> 
    > Created Time: 2019年01月16日 星期三 19时40分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void hander(int num)
{
	printf("this is handler func!\n");
	printf("num = %d\n",num);
}

int main(int argc,char *argv[])
{
	signal(SIGQUIT,hander);
	printf("signal had be register!\n");
	while(1)
	{
		printf("this just be a test \n");
		sleep(1);
	}
	return 0;
}
