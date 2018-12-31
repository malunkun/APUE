#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define LISTEN_PORT 8848
#define domain AF_INET
#define type SOCK_STREAM
#define protocol 0
#define BUFFSIZE 1024

int main(int argc,char *argv)
{
	int sever_fd;
	int accept_fd;
	int rd;
	char buf[BUFFSIZE];
	socklen_t len;
	struct sockaddr_in listen_addr;
	sever_fd = socket(domain,type,protocol);
	if (sever_fd < 0)
	{
		perror("create socket fail!:");
		return -1;
	}
	printf("create socket successful!!\n");

	memset(&listen_addr,0,sizeof(listen_addr));
	printf("clean listen_addr successful!\n");
	listen_addr.sin_family = domain;
	listen_addr.sin_port   = htons(LISTEN_PORT);
	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sever_fd,(struct sockaddr *)&listen_addr,sizeof(listen_addr))<0)
		{
			perror("bind fail!:");
			return -2;
		}
	printf("bind successful!\n");

	if (listen(sever_fd,1)<0)
	{
		perror("listen fail!:");
		return -3;
	}
	printf("listen successful!!\n");

while(1)
	{
		printf("waitint for receive.........\n");
		accept_fd = accept(sever_fd,(struct sockaddr *)&listen_addr,&len);
		if(accept_fd <0)
		{	
			perror("accept fail!:");
			return -4;
		}
		printf("accept successful !!\n");
		memset(buf,0,sizeof(buf));
		printf("data clean successful!\n");

		rd = read(accept_fd,buf,sizeof(buf));
		if (rd < 0)
		{
			perror("read fail!:");
			return -4;
		}
		if (rd==0)
			goto clean;
		if (write(accept_fd,buf,rd)<0)
		{
			perror("write fail!:");
			goto clean;
		}
		printf("receive message:%s\n",buf);
	}
	
clean:
	close(accept_fd);
	return 0;

}
