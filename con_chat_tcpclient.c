#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 

//TCP聊天客户端
int main ()
{
	char chat[64] = {0};
	char buf[64] = {0};
	int sockfd;
	struct sockaddr_in myaddr; 
	
	//1. 创建TCP socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2. 向服务器发起连接
	//给saddr设定服务器端的ip和端口号
	
    memset(&myaddr, 0, sizeof(myaddr)); 
    myaddr.sin_family = AF_INET; 
    myaddr.sin_port = htons(10000); 
    myaddr.sin_addr.s_addr = inet_addr("172.20.10.3"); 
	
	if (0 > connect(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))) 
    { 
        perror("connect"); 
        return -1; //exit //pthread_exit 
    } 
	
	
	//3. 循环聊天
	while(1)
	{
		//先情空缓存
		memset(chat, 0 , sizeof(chat));
		memset(buf, 0 , sizeof(chat));
		
		//从控制台获取聊天输入
		printf("please chat:");
		scanf("%s", chat);
		
		//向服务器发聊天信息
		send(sockfd, chat, strlen(chat), 0);
		
		//从服务器收聊天信息
		recv(sockfd, buf, sizeof(buf), 0);
		printf("from server: %s\n", buf);
	}
	
	close(sockfd);	
	
	return 0;
}