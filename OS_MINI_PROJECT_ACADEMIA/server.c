#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<netinet/ip.h>
#include<string.h>
#include<errno.h>
#include<stdbool.h>
#include<time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include<fcntl.h>
#include<sys/socket.h>
#define _GNU_SOURCE

#include "./structs.h"
#include "./functionsd.h"
#include "./hmenu.h"
#include "./hlogin.h"
#include "./hstudent.h"
#include "./hfaculty.h"
#include "./hcourse.h"
#include "./record_set.h"
#include "./studentg_s.h"
#include "./facultyg_s.h"
#include "./coursegs.h"
#include "./read_write.h"

void handle_server(int cfd){
	menu(cfd);}
void main()
{
		struct sockaddr_in serveraddr, clientaddr;
		int sfd=socket(AF_INET,SOCK_STREAM,0);
		if(sfd==-1){
		perror("Error while creating socket: ");
		exit(1);
		}
		printf("socket is created successfully \n");
		serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port=htons(8083);
		int bind_status=bind(sfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
		if(bind_status==-1){ 
		perror("Error while binding: ");
		exit(1);
		}
		printf("Socket binding is successfull\n");
		int listen_status=listen(sfd,2);

		if(listen_status==-1){ 
		perror("Error trying to listen for connections: ");
		exit(1);
		}
		int clientSize;
		while(1){
		clientSize=(int)sizeof(clientaddr);
		int cfd=accept(sfd,(struct sockaddr *)&clientaddr,&clientSize);
		if(cfd==-1){ 
		perror("Error while accepting connection: ");
		close(sfd);
		exit(1);
		}
		if(!fork()){
		handle_server(cfd);
		close(cfd);
		exit(0);
		}

		}
		close(sfd);
}

