//CLIENT working
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>

#define BUFFER_SIZE 100
#define TIMEOUT_SECONDS 5 // Timeout in seconds

int main() {
    int i, c_sock;
    c_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client;
    memset(&client, 0, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(9003);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
   
    if (connect(c_sock, (struct sockaddr*)&client, sizeof(client)) == -1) {
        printf("Connection failed");
        return 0;
    }
    char msg[50];

    char buff[BUFFER_SIZE];
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = 0;
    setsockopt(c_sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    for (i = 0; i < 10; i++)
    {
              int n = read(c_sock, buff, sizeof(buff));
              if (n > 0)
              {
                      buff[n] = '\0';
                      printf("Message received from server: %s\n", buff);
                      int num=rand()%3;
                      //printf("%d\n",num);
                      if(num==0)
                      {
                               printf("acknowledgement message:ack \n");
                               //fgets(msg, sizeof(msg), stdin);
                               strcpy(msg,"ack");
                      }
                      else if(num==1)
                      {
                              printf("acknowledgement message:nack\n");
                              strcpy(msg,"nack");
                      }
                      else
                      {
                              strcpy(msg,"t");
                              printf("ack sent\n");
                      }
                      write(c_sock, msg, strlen(msg));
            }
            else
            {
                      printf("Timeout occurred. No message received from server.\n");
                     // Resend the acknowledgment or take appropriate action
            }
            printf("\n");
    }
    close(c_sock);
    return 0;
}