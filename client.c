#include <stdio.h>
#include <locale.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

char ip_server[16];
char buf[128];

int client;
struct sockaddr_in  saddr;

int main(int argc, char **argv)
{

	setlocale(LC_ALL, "portuguese");
	memset(ip_server,0,16);
	printf("ServerIP: ");
//	fgets(ip_server,16,stdin);
	scanf("%s",ip_server);
	getchar();

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	inet_aton(ip_server,&(saddr.sin_addr));
	

	client = socket(AF_INET, SOCK_STREAM, 0/*IPPROTO_TCP*/);
	printf("Socket criado\n");

	int r = connect(client, (struct sockaddr*)&saddr, sizeof(saddr));
	if(r){
		printf("Erro na concaxao\n");
		close(client);
		return (0);
	}

	printf("Conetado ao servidor\n");
	
	while(1){
		printf("Enviar: ");
		
		fgets(buf,128,stdin);
		send(client,buf,128,0);

		printf("Receber: ");
		recv(client, buf,128,0);

		puts(buf);
	}
	close(client);

	return (0);
}
