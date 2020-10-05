#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <arpa/inet.h> 
#include <string.h>

int main(int argc, char const *argv[]) {

  int serverFd, clientFd;
  struct sockaddr_in server, client;
  int len,port,array[26],k=0,i,j,n,choice;
  const char *ns[2];
  const char *ch1[2];
  char buffer[100],c,ch;
  if (argc == 2) {
    port = atoi(argv[1]);
  }
  serverFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverFd < 0) {
    perror("Cannot create socket");
    exit(1);
  }
  printf("\nEnter port number");
  scanf("%d",&port);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);
  len = sizeof(server);
  if (bind(serverFd, (struct sockaddr *)&server, len) < 0) {
    perror("Cannot bind sokcet");
    exit(2);
  }
  if (listen(serverFd, 10) < 0) {
    perror("Listen error");
    exit(3);
  }
     for (c = 'A'; c <= 'Z'; ++c)
    {
        array[k++]=c;
    }
    
  while (1) {
    len = sizeof(client);
    if ((clientFd = accept(serverFd, (struct sockaddr *)&client, &len)) < 0) {
      perror("accept error");
      exit(4);
    }
    char *client_ip = inet_ntoa(client.sin_addr);
    //printf("Accepted new connection from a client %s:%d\n", client_ip, ntohs(client.sin_port));
    memset(buffer, 0, sizeof(buffer));
    int size = read(clientFd, buffer, sizeof(buffer));
    if ( size < 0 ) {
      perror("read error");
      exit(5);
    }
printf("\nReceived frame: %s",buffer);


  for(i=0;buffer[i]!='\0';i++)
    {
        ch=buffer[i];
        for(j=0;j<26;j++)
        {
            if(ch==array[j])
            printf("%d",i);
        }
    }
    
    printf("\n");
    printf("Any Error? 1-Yes   0-No ");
    scanf("%s",&ch1);
    sscanf(ch1,"%d",&choice);// string to int
    if(choice==1)
    {
    printf("\nEnter sequence no. of frame where error has occured: ");
    scanf("%s",&ns);
    write(clientFd,ns,strlen(ns));
    printf("\n\n\n");
    read(clientFd, ns, sizeof(ns));
    sscanf(ns,"%d",&n);//string to int
    printf("\nReceived the retransmitted frame %c%d",buffer[n],n);
    printf("\nExit\n");
    
   }
    else if(choice==0)
    {
    printf("\nExit\n");
    exit(6);
    }
    

     exit(0);
    close(clientFd);
  }
  close(serverFd);
 
  return 0;
}
