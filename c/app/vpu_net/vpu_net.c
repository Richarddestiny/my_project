#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define STATUS_SIZE 0x08
#define BUFSZ 0x28000 
struct sendbuf {
	int n;
	struct sockaddr_in addr;
};

static int debug_on = 0;

#define dbg(fmt, arg...) \
    do { \
        if (debug_on) { \
            printf(fmt, ##arg);\
        }\
    } while (0)


struct nethdr {
	int seqno;
	int iframe;
	int len;
	int dframe;
};


//static char recvbuf[BUFSZ];
char *recvbuf = NULL;

static int fd_int = 0;
static void * map_base;
static long long filelen = 0;
static char filename[128];

#if 0
static int memcmpb(void *a, int c, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		if (c != ((unsigned char *)a)[i])
			return 1;
	}
	return 0;
}
#endif

void notify_slave()
{
	dbg("notify S\n");
	write(fd_int, "M", 1);
}

void wait_slave_send_over()
{
	char buf[8];
	read(fd_int, buf, 1);
	dbg("OK! Slave Send Over!!!\n");
}

//žñÊœ:
//PCIe
//slave_dvp.264
//123456789
void parse_start_frame(void)
{
    char *p = recvbuf;
    int i = 0;

    if (strncmp(p, "PCIe", 4) == 0)
    	dbg("Validata OK!\n");
    else {
    	printf("Validate fail\n");
    	return ;
    }
    
    p += 5;//pÖžÏòfilename
    while(*p != '\n') {
    	filename[i] = *p;
    	i++,p++;
    }
    p++;//skip cr
    filelen = atoll(p);

    printf("filename:%s filelen:%lld\n", filename, filelen);
}

void do_recv_one_frame()
{
    dbg("do_recv_one_frame\n");
     
    memcpy(recvbuf, map_base, BUFSZ);//PCI===>file      
}

void write_one_frame(int fd)
{
    int nbytes;

    nbytes = write(fd, recvbuf, BUFSZ);
    if (nbytes != BUFSZ) {
        printf("write_one_frame error: nbytees=%x (%d)\n", nbytes, nbytes);
        exit(1);
    }
    //fsync(fd); ¿ÉÄÜÒýÆðoops£¬¶ÔŽóÊýŸÝÎÄŒþ²Ù×÷Ê±
    dbg("write_one_frame ok\n");       
}

void write_rest_frame(int fd, int rest)
{
    int nbytes;

    nbytes = write(fd, recvbuf, rest);
    if (nbytes != rest) {
        printf("write_rest_frame error: nbytees=%x (%d)\n", rest, rest);
        exit(1);
    }
    fsync(fd);
    dbg("write_rest_frame ok\n");    
}


#define SERVER_PORT 5555 
#define BUFFER_SIZE 1024 
//Ö÷°å£º
//./pcie_int_file_mr
//such as:
//   ./pcie_int_file_mr
//   ./pcie_int_file_mr
int main(int argc, char * argv[])
{
    int fd_pci, fd_cam;
    long k, cnt, rest;
    int sd;
    char *buf;
     char send_buf[20] ={0};
int n;
    struct nethdr *net_h;
 struct sockaddr_in server_addr; 
int nSendBuf=0x80000;
int ret;
struct net_h *p_net;
 bzero(&server_addr, sizeof(server_addr)); 
 server_addr.sin_family = AF_INET; 
 server_addr.sin_addr.s_addr = inet_addr("192.168.0.150"); 
 server_addr.sin_port = htons(SERVER_PORT); 
  
	sd = socket(PF_INET, SOCK_STREAM, 0); 
	if (sd < 0) {
	printf("failed to open udp socket\n");
	return -1;
	}



	fd_int = open("/dev/gpio_dev_master", O_RDWR);
	if (fd_int == -1) {
		printf("open /dev/gpio_dev_master fail\n");
		return 1;
	}
    


    fd_pci = open("/dev/mem", O_RDWR|O_SYNC);
    if (fd_pci == -1) {
        printf("open /dev/mem fail\n");
        return (-1);
    }
    
    map_base = mmap(NULL, BUFSZ, PROT_READ|PROT_WRITE, MAP_SHARED, fd_pci, 0x40000000);//0x40000000:sdram¿ÕŒä
    if (map_base == 0) {
        printf("mmap  0x40000000 fail!\n");
        return 1;
    }
    
    recvbuf = (char *)malloc(BUFSZ);
    if (!recvbuf) {
    	printf("Error: mallco recvbuf fail\n");
    	exit(1);
    }
	
		while(1)
		{
			ret = connect(sd, (struct sockaddr *)& server_addr, sizeof(struct sockaddr_in));
			if(-1 == ret)	{	
				printf("connect: %s\n", strerror(errno));
				sleep(1);	
				continue;	
			}
			else
				{
				printf("connect success fd:%d\n",sd);
				break;
				}
			
		}

	notify_slave();
	while(1)
	{
	        wait_slave_send_over();	   
	        do_recv_one_frame();
		memcpy(&n, recvbuf+STATUS_SIZE,sizeof(n));
//		printf("size :%d\n",n);
		net_h = (struct nethdr *)(recvbuf+STATUS_SIZE +sizeof(n));
		//printf( "TX: neth seqno %d, iframe %d, len %d,n:%d\n", net_h->seqno, net_h->iframe, net_h->len,n);
#if 1
		if(send(sd,(recvbuf+STATUS_SIZE +sizeof(n)),n , 0) <0)
		{
			perror("sendto");
		}
	#endif	
		notify_slave();		
	}
    	
	
	free(recvbuf);
    
    munmap(map_base, 0xFFC000);
    close(fd_int);
    close(fd_pci);
   
    return (0);
}
