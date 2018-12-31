#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define domain AF_INET
#define type SOCK_STREAM
#define protocol 0
#define MSG "i am successed!"
#define CLI_PORT 8848
#define CLI_IP "127.0.0.1"
#define BUFFSIZE 1024
int main(int argc,char *argv)
{
	int cli_fd;
	char buf[BUFFSIZE];
	struct sockaddr_in cli_addr;
	int rd;
	socklen_t len;
	cli_fd=socket(domain,type,protocol);
	if (cli_fd<0)
	{
		perror("create socket failure!:");
		return -1;
	}
	printf("create socket successful!\n");
	memset(&cli_addr,0,sizeof(cli_addr));
	cli_addr.sin_family = domain;
	cli_addr.sin_port = htons(CLI_PORT);
	inet_aton(CLI_IP,&cli_addr.sin_addr);
	printf("ready to connect..........\n");
	if (connect(cli_fd,(struct sockaddr *)&cli_addr,sizeof(cli_addr))<0)
	{
		perror("connect failure!:");
		return -1;
	}
        printf("connect successful!\n");	
	if (write(cli_fd,MSG,strlen(MSG))<0)
	{
		perror("write failure!:");
		goto clean;
	}
	printf("write successful!\n");

	memset(buf,0,sizeof(buf));
	printf("clean data successful!\n");
	rd = read(cli_fd,buf,sizeof(buf));
	printf("read successful!%d\n",rd);
	if (rd<0)
	{
		perror("read fail!:");
		goto clean;
	}
	if (0==rd)
		goto clean;
clean:
	printf("finish sending !!!!\n");

	close(cli_fd);
	return 0;

}
