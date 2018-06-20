/*****************************************

*TCP服务器端步骤：

*创建套接字  socket()

*绑定套接字  bind()  ------> listen()

*设置套接字为监听模式，进入被动接受连接请求状态

*接受请求，建立连接 recv()

*读写数据  send()

*终止连接   close()

******************************************/

#include <stdio.h>

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>
#include <string.h>


#define BUFSIZE 1000

int

main (int argc, char *argv[])

{

  int s;

  int fd;

  int len;

  struct sockaddr_in my_addr;

  struct sockaddr_in remote_addr;

  int sin_size;

  char buf[BUFSIZE];

  memset (&my_addr, 0, sizeof (my_addr));

  my_addr.sin_family = AF_INET;

  my_addr.sin_addr.s_addr = INADDR_ANY;

  my_addr.sin_port = htons (8000);

  if ((s = socket (PF_INET, SOCK_STREAM, 0)) < 0)

    {

      perror ("socket");

      return 1;

    }

  if (bind (s, (struct sockaddr *) &my_addr, sizeof (struct sockaddr)) < 0)

    {

      perror ("bind");

      return 1;

    }

  listen (s, 5);

  sin_size = sizeof (struct sockaddr_in);

  if ((fd = accept (s, (struct sockaddr *) &remote_addr, &sin_size)) < 0)

    {

      perror ("accept");

      return 1;

    }

  printf ("accept client %s\n", inet_ntoa (remote_addr.sin_addr));

  len = send (fd, "Welcome to my serve\n", 21, 0);

  while ((len = recv (fd, buf, BUFSIZE, 0)) > 0)

    {

      buf[len] = '\0';

      printf ("%s\n", buf);

      if (send (fd, buf, len, 0) < 0)

{

 perror ("write");

 return 1;

}

    }

  close (fd);

  close (s);

  return 0;

}

 
