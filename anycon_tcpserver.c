#include <stdio.h>
#include "queue.h"
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

//消息处理任务声明
void *msgfunc(void* arg);

int main ()
{	
	int sockfd;
	int addrlen;
	//1. 创建TCP socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2. 绑定IP地址与端口号
	struct sockaddr_in myaddr,client_addr;
	addrlen = sizeof(struct sockaddr_in);
    memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET; 
    myaddr.sin_port = htons(10000);  
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))
    { 
        perror("bind"); 
        return -1; 
    } 
	//3. 创建监听客户端连接队列
	listen(sockfd, 10);

	while(1)
	{		 
		//4. 等待并建立客户端的连接
		printf("accept..........\n");
		int connfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
	
		//5. 为已连接客户端创建消息处理任务
		create_task(msgfunc, (void*)&connfd);
	}
	
	close(sockfd);
	
	return 0;
}

//消息处理任务实现
void *msgfunc(void* arg)
{
	int connfd = *(int*)arg; //连接套接字
	Queue *que = NULL;
	T msg;
	
	//1.创建消息队列
	que = CreateQueue();
	
	while(1)
	{
		memset(msg, 0, sizeof(msg));
		//接收对方消息
		if (recv(connfd, msg, sizeof(msg), 0)>0)
		{
			printf("msg is %s\n", msg);
			//对方确认消息接收完备
			if ('q' == msg[0])
			{
				break;
			}
			
			Push(que, msg);//进队
		}
		
	}
	
	//显示所有已接收消息
	Print(que);
	DestroyQueue(que);
	close(connfd);
}
