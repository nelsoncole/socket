#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define SERVER_PORT 5000

struct sockaddr_in caddr;
struct sockaddr_in saddr;
int client, server, csize;

char ip_server[INET_ADDRSTRLEN];
char ip_client[INET_ADDRSTRLEN];
char buf[128];

// SOCK_STREAM
// SOCK_D
int main()
{
	setlocale(LC_ALL, "portuguese");
	
	memset(ip_server,0,INET_ADDRSTRLEN);
	memset(ip_client,0,INET_ADDRSTRLEN);
	
	saddr.sin_family	= AF_INET;
	saddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	//saddr.sin_addr.s_addr	= inet_addr("127.0.0.1");
	saddr.sin_port	= htons(SERVER_PORT);
	
	csize = sizeof(struct sockaddr_in);
	server = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
	
	int r = bind(server, (struct sockaddr*)&saddr, sizeof(struct sockaddr_in));
	if(r)
	{
	
		
		printf("Porta: %d não disponível\n",SERVER_PORT);
		close(server);
		exit(1);
	}
	
	listen(server, 8);
	inet_ntop(AF_INET,&saddr.sin_addr, ip_server, INET_ADDRSTRLEN);
	printf("IP: %s, Porta: %d\n",ip_server,SERVER_PORT);
	
	while(1)
	{
		client = accept(server, (struct sockaddr*)&caddr, &csize);
		inet_ntop(AF_INET,&caddr.sin_addr, ip_client, INET_ADDRSTRLEN);
		
		printf("ClientIP: %s, ClientPorta: %d\n",ip_client,caddr.sin_port);
		int ex = 0;
		while(1){
		
			printf("Receber: ");
			
			int srecv = recv(client, buf, sizeof(buf), 0);
			
			if(srecv){
		
				puts(buf);
			
				if(!strcmp("sair",buf) ){
					ex = 1;
					break;
				}
			}
			
			printf("Enviar: ");
			fgets(buf, 128, stdin);
			send(client, buf, 128, 0);
		
		}
		
		if(ex){ 
			close(client);
			break;
		}
	}
	
	close(server);
	return 0;
}
