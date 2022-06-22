#include <stdio.h> 

#include <string.h> 

#include <stdlib.h> 

#include <strings.h> 

#include <sys/types.h> 

#include <sys/socket.h> 

#include <netinet/in.h> 

#include <arpa/inet.h> 

int main() 

{ 

 int sockfd; 

    if (0 > (sockfd = socket(AF_INET, SOCK_STREAM, 0))) 

    { 

        perror("socket"); 

        return -1; 

    } 

    printf("socket...........\n"); 

 

    struct sockaddr_in srv_addr; 

    memset(&srv_addr, 0, sizeof(srv_addr)); 

    srv_addr.sin_family         = AF_INET; 

    srv_addr.sin_port           = htons(10000); 

    srv_addr.sin_addr.s_addr    = inet_addr("172.20.10.3"); 

    if (0 > connect(sockfd, (struct sockaddr*)&srv_addr, sizeof(srv_addr))) 

    { 

        perror("connect"); 

        return -1; //exit //pthread_exit 

    } 

    printf("connect..............\n"); 

    char buf[100]; 

    int ret; 

    while (1) 

    { 

        printf("send: "); 

        fgets(buf, sizeof(buf), stdin); 

        ret = write(sockfd, buf, sizeof(buf)); 

        if (ret < 0) 

        { 

            perror("write"); 

            break; 

        } 

        if (strncmp(buf, "quit", 4) == 0) 

            break; 

    } 

    close(sockfd); 

    return 0; 

} 