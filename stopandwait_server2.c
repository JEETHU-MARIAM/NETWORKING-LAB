//SERVER working
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/time.h>
#define BUFFER_SIZE 100
#define TIMEOUT_SECONDS 10 // Timeout in seconds
int main() {
    int i, s_sock, c_sock,flag=0;
    s_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, other;
    memset(&server, 0, sizeof(server));
    memset(&other, 0, sizeof(other));
    server.sin_family = AF_INET;
    server.sin_port = htons(9003);
    server.sin_addr.s_addr = INADDR_ANY;
    socklen_t add;

    if (bind(s_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Binding failed\n");
        return 0;
    }
    printf("\tServer Up\n Stop and wait ARQ protocol used to send 5 messages with a timeout\n\n");
    listen(s_sock, 10);
    add = sizeof(other);
    c_sock = accept(s_sock, (struct sockaddr*)&other, &add);
    char msg[50] = "server message: ";

    char sbuff[BUFFER_SIZE],cbuff[BUFFER_SIZE];
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = 0;
    setsockopt(c_sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    for (i = 0; i < 10;i++)
    {
                if (flag==0)
                {
                       printf("ENTER MESSAGE:  ");
                       fgets(sbuff, sizeof(sbuff), stdin);
                       sbuff[strcspn(sbuff, "\n")] = '\0';
                }
                printf("MESSAGE SENT TO CLIENT: %s\n", sbuff);
                write(c_sock, sbuff, strlen(sbuff));
                int n = read(c_sock, cbuff, sizeof(cbuff));
                if (n > 0) 
                {
                      cbuff[n] = '\0';
                      if(cbuff[0]=='n')
                      {
                            printf("MESSAGE FROM CLIENT: %s\n", cbuff);
                            flag=1;
                            printf("have to resend msg bcoz of nack\n");
                      }
                      else if(cbuff[0]=='a')
                      {
                            printf("MESSAGE FROM CLIENT: %s\n", cbuff);
                            flag=0;
                      }
                      else
                      {
                              printf("Timeout occurred. No acknowledgment received.\n");
                              flag=1;
                              // Resend the message or take appropriate action
                      }
               }
              printf("\n");
    }
    close(c_sock);
    close(s_sock);
    return 0;
}



