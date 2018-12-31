#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 8848
#define BUFFSIZE 1024

int main (int argc,char *argv)
{
	int socket_fd;
	int listen_fd;
	char buf[BUFFSIZE];
	pid_t fpid;
	struct sockaddr_in servaddr;
	int rd;
	socklen_t len;

	socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if (socket_fd < 0)
	{
		perror("create socket fail!");
		return -1;
	}
	printf("create socket successful!\n");
	memset(&servaddr,0,sizeof(servaddr));
	printf("clean the STRUCT SOCKADDR_IN successful!\n");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons (PORT);
	servaddr.sin_addr.s_addr  = htonl (INADDR_ANY);
	if (bind(socket_fd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
	{
		perror("bind fail!");
		return -2;
	}
	printf("bind successful!\n");
	if (listen(socket_fd,10) < 0)
	{
		perror("listen fail!");
		return -3;
	}
	printf("start to listen port %d.........\n",PORT);
	while (1)
	{
		printf("the PID is %d\n",getpid());
		listen_fd = accept(socket_fd,(struct sockaddr *)&servaddr,&len);
		if (listen_fd < 0)
		{
			perror("listen fail!");
			continue;
		}
		printf("listen successful!\n");
		fpid = fork();
		if (fpid < 0)
		{
			perror("fork fail!");
			close(listen_fd);
			continue;
		}
		if (0 == fpid)
		{
			while(1)
			{
				printf("the parent process PID is %d\n",getppid());
				printf("child process start.....\n");
				printf("the child procsee PID is %d\n",getpid());
				memset(buf,0,sizeof(buf));
				printf("clean buffer successful!\n");
				rd = read(listen_fd,buf,sizeof(buf));
				if (rd < 0)
				{
					perror("read fail !");
					close(listen_fd);
					continue;
				}
				printf("read successful !\n");
				if (write(listen_fd,buf,rd) < 0)
				{
					perror("write fail!");
					close(listen_fd);
					continue;
				}
				printf("write successful!\n");
				printf("receive the message:%s\n",buf);
				sleep(100);
				}
				return 0;
			}
		if (fpid > 0)
		{
			sleep (2);
			printf("I am in the parent process now !\n");
			printf("the parent process PID is %d\n",getpid());
			close(listen_fd);
			printf("the parent process close the listen_fd!\n");
			continue;
		}
	}
	return 0;
}
