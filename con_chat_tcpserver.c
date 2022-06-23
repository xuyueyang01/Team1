#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

//聊天任务声明
void *chatfunc(void* arg);

int main ()
{	
	//1. 创建TCP socket
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2. 绑定IP地址与端口号
	struct sockaddr_in myaddr,client_addr;
	int addrlen = sizeof(struct sockaddr_in);
    memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET; 
    myaddr.sin_port = htons(10000);  
    myaddr.sin_addr.s_addr = INADDR_ANY; 
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
		int connfd = accept(sockfd,(struct sockaddr *) &client_addr, &addrlen);
	
		//5. 为已连接客户端创建聊天任务
		create_task(chatfunc, (void*)&connfd);
		printf("task ok.........connfd is %d\n", connfd);
	}
	
	close(sockfd);
	
	return 0;
}

//聊天任务实现
void *chatfunc(void* arg)
{
	int connfd = *(int*)arg; //连接套接字
	char msg[100] = {0};
	char buf[100] = {0};
	
	while(1)
	{
		memset(msg, sizeof(msg), 0);
		memset(buf, sizeof(buf), 0);
		//接收对方聊天信息
		printf("recv..........connfd is %d\n", connfd);
		recv(connfd, buf, sizeof(buf), 0);
		printf("from server: %s\n", buf);
		
		//发送本方聊天信息
		printf("please chat:");
		scanf("%s", msg);
		send(connfd, msg, strlen(msg), 0);	
	}
	
	close(connfd);
}
