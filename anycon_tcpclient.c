#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

//TCP异步并发服务器测试客户端
int main ()
{
	char msg[128] = {0};
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

	//3. 循环发送
	while(1)
	{
		//先清空缓存
		memset(msg, 0 , sizeof(msg));
		
		//从控制台获取消息输入
		printf("please input:");
		scanf("%s", msg);
		
		//向服务器发信息
		send(sockfd, msg, strlen(msg), 0);
		
		if ('q' == msg[0])
		{
			break; //消息输入结束
		}
		
	}
	
	close(sockfd);	
	
	return 0;
}