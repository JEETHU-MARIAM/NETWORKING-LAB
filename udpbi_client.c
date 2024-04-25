//udp bi client 


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define PORT 5047

int main()
{
        int sock;
        struct sockaddr_in addr;
        socklen_t addr_size;
        char buf[1024];

        sock=socket(AF_INET,SOCK_DGRAM,0);
        if(sock<0)
        {
                      perror("Client is not created\n");
                      exit(0);
        }
        else
                      printf("Client is created successfully\n");
        memset(&addr,'\0',sizeof(addr));
        addr.sin_family=AF_INET;
        addr.sin_port=htons(PORT);
        addr.sin_addr.s_addr=inet_addr("127.0.0.1");
        addr_size=sizeof(addr);

        while(1)
        {
                  bzero(buf,1024);
                  printf("\nEnter message:");
                  fgets(buf,sizeof(buf),stdin);
                  sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&addr,addr_size);
                  if(strncmp("exit",buf,4)==0)
                  {
                          printf("Client Disconnected\n");
                          close(sock);
                          break;
                  }
   
                  recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&addr,&addr_size);
                  printf("From Server:%s",buf);

                  if(strncmp("exit",buf,4)==0)
                  {
                          printf("Client Disconnected\n");
                          close(sock);
                          break;
                  }

        }
        return 0;
}