/*************************************************************************
    > File Name: daemon.c
    > Author: malunkun
    > Mail: malunkun<209446860qq.com> 
    > Created Time: 2019年01月17日 星期四 21时57分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

int main(int argc,char *argv[])
{
	daemon(0,1);
	while(1)
	{
	printf("i am here!\n");
	syslog(LOG_DEBUG,"daemon test message!\n");
	sleep(5);
	}
	return 0;
}
