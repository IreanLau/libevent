#include<sys/signal.h>
#include<event.h>
#include <stdio.h>  
#include <string.h>  
#include <iostream>  
#include <sys/socket.h>      
#include <netinet/in.h>      
#include <arpa/inet.h>      
#include <netdb.h>  
using namespace std;


struct event_base* base;
//struct timeval tv={3,0};

void onRead(int fd,short iEvent,void* arg)
{
	char buf[1024];
	int readSize=recv(fd,buf,sizeof(buf),0);

	if(readSize<=0)
	{
		cout<<"client close~"<<endl;
		struct event *pEvRead = (struct event*)arg;  
		event_del(pEvRead);  
		delete pEvRead;  

		close(fd);
		return ;
	}
	
	buf[readSize] ='\0';
	cout<<"client info is :> "<<buf<<endl;
}

void onAccept(int fd,short iEvent,void* arg)
{
	struct sockaddr_in remote;
	socklen_t len=sizeof(remote);
	int remote_fd = accept(fd,(struct sockaddr*)&remote,&len);
	if(remote_fd<=0)
	{
		cout<<"not accept:"<<endl;
		return;
	}
	else
		cout<<"a new client connect!"<<endl;
	struct event* readEvent=new event;
	event_set(readEvent,remote_fd, EV_READ|EV_PERSIST,onRead,readEvent);
	event_base_set(base,readEvent);
	event_add(readEvent,NULL);
}

int main()
{
	int sockFd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8888);

	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);

	bind(sockFd,(struct sockaddr*)&addr,sizeof(addr));
	listen(sockFd,5);

	base = event_base_new();
	struct event ev_listen;
	event_set(&ev_listen,sockFd,EV_READ|EV_PERSIST,onAccept,NULL);
	event_base_set(base,&ev_listen);
	event_add(&ev_listen,NULL);
	event_base_dispatch(base);
	return 0;
}
