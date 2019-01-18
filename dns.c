/*************************************************************************
    > File Name: client.c
    > Author: malunkun
    > Mail: malunkun<209446860qq.com> 
    > Created Time: 2019年01月15日 星期二 14时13分53秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>  
#include<sys/socket.h>
#include<signal.h>
#include<unistd.h>
#include<netdb.h>
#include<string.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	int optret;
	char *ipname = NULL;
	char ip[50];
	struct hostent *gethost = NULL;
	int file_fd;
	char buf[50];
	char *ptrf;
	char *ptrb;
	int n;
	char fptr[50];
	const char *ptr = NULL;
	struct in_addr  inAddr;
	while((optret = getopt(argc,argv,"i:p:")) != -1)
	{
		switch(optret)
		{
			case 'i':
				ipname = optarg;
				printf("option = i,the ipname is:%s\n",optarg);
				break;
			case 'p':
 	//			printf("option = p,the port will be set=%s\n",optarg);
				break;
		}
	}
	gethost = gethostbyname(ipname);
	if (NULL == gethost)
	{
		perror("get ipaddr fail!");
		return -1;
	}
	printf("get host successfully!\n");
	memset(ip,0,sizeof(ip));
	//printf("clear buffer!\n");
	ptr = inet_ntop(gethost->h_addrtype,gethost->h_addr_list[0],ip,sizeof(ip));
	//printf("right2\n");
	printf("DNS ip is:%s\n",ptr);
/////////////////////////////////////////////////////////////////
	system("ping studio.iot-yun.com -c 2 >> /home/deepin/APUE/malunkun/test/.domain.log");
	file_fd=open("/home/deepin/APUE/malunkun/test/.domain.log",O_RDONLY,644);
	if (file_fd < 0)
	{
		perror("open file fail!\n");
	}
	read(file_fd,buf,sizeof(buf));
	close(file_fd);
	ptrf = strstr(buf,"(");
	ptrf += 1;
	ptrb = strstr(buf,")");
	n = strlen(ptrf)-strlen(ptrb);
	strncpy(fptr,ptrf,n);
	printf("ping ip is:%s\n",fptr);
//////////////////////////////////////////////////////////////////////////
	return 0;
}

