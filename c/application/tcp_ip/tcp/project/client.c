#include "common.h"

int main(int argc, char **argv[])
{
	int clientfd;

        char recv_buff[1024];
	if(argc!=2)
	{
		fprintf(stderr,"Usage:./fileclient <IP_Address>\n");
		exit(1);
	}
	struct sockaddr_in clientaddr;
	bzero(&clientaddr,sizeof(clientaddr));	

	clientaddr.sin_family=AF_INET;
	clientaddr.sin_addr.s_addr=htons(INADDR_ANY);
	clientaddr.sin_port=htons(0);
	
	clientfd=socket(AF_INET,SOCK_STREAM,0);
	
	if(clientfd<0)	
	{
		perror("socket");
		exit(1);
	}

	if(bind(clientfd,(struct sockaddr*)&clientaddr,sizeof(clientaddr))<0)
	{
		perror("bind");
		exit(1);
	}

	struct sockaddr_in svraddr;
	bzero(&svraddr,sizeof(svraddr));
	if(inet_aton(argv[1],&svraddr.sin_addr)==0)
	{
		perror("inet_aton");
		exit(1);
	}
	svraddr.sin_family=AF_INET;
	svraddr.sin_port=htons(PORT);
	
	socklen_t svraddrlen=sizeof(svraddr);
	if(connect(clientfd,(struct sockaddr*)&svraddr,svraddrlen)<0)	
	{
		perror("connect");
		exit(1);
	}
	
	//recv file imformation
	char buff[BUFFSIZE];
	char filename[FILE_NAME_MAX_SIZE];
	int count;
    struct test {
        int head;
        int cmd_ctr;
        char data[256];
        int ack;
        int end;
    }test_cmd;
test_cmd.head = 0x68;
test_cmd.cmd_ctr = 0x01;
memset(test_cmd.data,'0',sizeof(test_cmd.data));
test_cmd.ack = 0x69;
test_cmd.end = 0x16;
//while(1)
{
	bzero(buff,BUFFSIZE);
memcpy(buff,&test_cmd,sizeof(test_cmd));
    count = send(clientfd,buff,sizeof(test_cmd),0);


char buff[BUFFSIZE];
	char filename[FILE_NAME_MAX_SIZE];
	int count;


memset(test_cmd.data,0,sizeof(test_cmd.data));
	bzero(buff,BUFFSIZE);
	count=recv(clientfd,buff,BUFFSIZE,0);
	if(count<0)
	{
		perror("recv");
		exit(1);
	}
memcpy(&test_cmd,buff,sizeof(test_cmd));
printf("test%s\n",test_cmd.data);
	strcpy(filename,test_cmd.data);

	printf("Preparing recv file : %s from 127.0.0.1:%s \n",filename,test_cmd.data);	

	//recv file
	FILE *fd=fopen(filename,"wb+");
	if(NULL==fd)
	{
		perror("open");
		exit(1);
	}
	bzero(buff,BUFFSIZE);

	int length=0;
	while(length=recv(clientfd,buff,BUFFSIZE,0))
	{
		if(length<0)
		{
			perror("recv");
			exit(1);
		}
		int writelen=fwrite(buff,sizeof(char),length,fd);
		if(writelen<length)
		{
			perror("write");
			exit(1);
		}
		bzero(buff,BUFFSIZE);
	}
	printf("Receieved file:%s from 127 finished!\n",filename);
#if 0
    recv(clientfd,recv_buff,BUFFSIZE,0);
memcpy(&test_cmd,recv_buff,sizeof(test_cmd));

    printf("recv_buff:%s\n",test_cmd.data);
    #endif
}
#if 0
	count=recv(clientfd,buff,BUFFSIZE,0);
	if(count<0)
	{
		perror("recv");
		exit(1);
	}
	strncpy(filename,buff,strlen(buff)>FILE_NAME_MAX_SIZE?FILE_NAME_MAX_SIZE:strlen(buff));

	printf("Preparing recv file : %s from %s \n",filename,argv[1]);	
	//recv file
	FILE *fd=fopen(filename,"wb+");
	if(NULL==fd)
	{
		perror("open");
		exit(1);
	}
	bzero(buff,BUFFSIZE);

	int length=0;
	while(length=recv(clientfd,buff,BUFFSIZE,0))
	{
		if(length<0)
		{
			perror("recv");
			exit(1);
		}
		int writelen=fwrite(buff,sizeof(char),length,fd);
		if(writelen<length)
		{
			perror("write");
			exit(1);
		}
		bzero(buff,BUFFSIZE);
	}
	printf("Receieved file:%s from %s finished!\n",filename,argv[1]);
	fclose(fd);

#endif
	close(clientfd);
	return 0;
}
