#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int serverFd;
  struct sockaddr_in server;
  int len,port, array[26],k=0,i,j,n,choice;
  const char *ns[2];
  const char *ch1[2];
  char *server_ip = "127.0.0.1";
  char buffer[100],c,ch;
  if (argc == 3) {
    server_ip = argv[1];
    port = atoi(argv[2]);
  }
  serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd < 0) {
    perror("Cannot create socket");
    exit(1);
  }
  printf("\nEnter port number");
  scanf("%d",&port);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(server_ip);
  server.sin_port = htons(port);
  len = sizeof(server);
  printf("Enter the text: ");
  scanf("%s",buffer);
  for (c = 'A'; c <= 'Z'; ++c)
    {
        array[k++]=c;
    }
    int g=0;
    int p[10];
   for(i=0;buffer[i]!='\0';i++)
    {
        ch=buffer[i];
        for(j=0;j<26;j++)
        {
            if(ch==array[j])
            p[g++]=i;
        }
    }
  if (connect(serverFd, (struct sockaddr *)&server, len) < 0) {
    perror("Cannot connect to server");
    exit(2);
  }
  int size = write(serverFd, buffer, strlen(buffer));
printf("Transmitting frame");
for(i=0;i<g;i++)
{
printf("%d",p[i]);
}


  if ( size < 0) {
    perror("Cannot write");
    exit(3);
  }

  memset(ns, 0, sizeof(ns));
  if (read(serverFd, ns, sizeof(ns)) < 0) {
    perror("cannot read");
    exit(4);
  }
  printf("\nReceived error in %s\n", ns);
  sscanf(ns,"%d",&n);
  printf("\n\n");
  write(serverFd, ns, strlen(ns));
  printf("Retransmitting frame %d\n",n);
  close(serverFd);
  return 0;
}
