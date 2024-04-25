//udp bi server 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define PORT 5047

int main()
{
         int server_sock,client_sock,n;
         socklen_t addr_size;
         struct sockaddr_in serveraddr,clientaddr;
         char buf[1024];

         server_sock=socket(AF_INET,SOCK_DGRAM,0);

         if(server_sock<0)
         {
                  perror("Server not created\n");
                  exit(0);
         }
         else
                 printf("Server is created successfully\n");

         memset(&serveraddr,'\0',sizeof(serveraddr));
         serveraddr.sin_family=AF_INET;
         serveraddr.sin_port=htons(PORT);
         serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

         n=bind(server_sock,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
         if(n<0)
         {
                 perror("Bind error\n");
                 exit(0);
         }
         else
                 printf("Bind to the Port number %d\n",PORT);

         addr_size=sizeof(clientaddr);
 
         while(1)
         {
                   bzero(buf,1024);
                   recvfrom(server_sock,buf,sizeof(buf),0,(struct sockaddr*)&clientaddr,&addr_size);
                   printf("From Client:%s",buf);
                   if(strncmp(buf,"exit",4)==0)
                   {
                              printf("Server is disconnected\n");
                              close(server_sock);
                              break;
                   }
                   printf("\nEnter message:");
                   fgets(buf,sizeof(buf),stdin);
                   sendto(server_sock,buf,strlen(buf),0,(struct sockaddr*)&clientaddr,addr_size);
                   if(strncmp(buf,"exit",4)==0)
                   {
                            printf("Server is disconnected\n");
                            close(server_sock);
                            break;
                   }
         }
         return 0;
}