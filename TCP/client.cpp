#include<sys/signal.h>
#include<event.h>
#include <stdio.h>  
#include <string.h>  
#include <iostream>  
#include <sys/socket.h>      
#include <netinet/in.h>      
#include <arpa/inet.h>      
#include<iostream>
using namespace std;


int main()
{
	int sock = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));

	addr.sin_family=AF_INET;
	addr.sin_port=htons(8888);
	inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);

	connect(sock,(struct sockaddr*)&addr,sizeof(addr));
	
	char buf[1024];
	while(1)
	{
		bzero(buf,sizeof(buf));
		cout<<"Enter:> "<<endl;
		fflush(stdout);

		gets(buf);
		if(strncmp(buf,"quit",4)==0)
		{
			close(sock);
		}
		send(sock,buf,sizeof(buf),0);
		bzero(buf,sizeof(buf));
	}
	return 0;
}
