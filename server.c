#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "queue.h"
#include "message.h"
#include "TList.h"
#define SIZE 80

int main() {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    fd_set readfds, testfds;
   
    unlink("receive_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
   
    
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "receive_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    
    TList list;
    InitList(&list);
    TList *curlist = &list;
    
    Message_for_server mes;
    mes.name = 0;
        
    listen(server_sockfd, 5);
    
    while(1) {
        char ch[SIZE];
      	int size;
        printf("server waiting\n");
        
      	client_len = sizeof(client_address);
  	client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
	
	read(client_sockfd, &mes.action, sizeof(int));	
	if(mes.action == 1){	 
 		read(client_sockfd, &size, sizeof(int));
  		read(client_sockfd, &ch, size*sizeof(char));
  	
  		mes.string = (char*)malloc(size*sizeof(char));
  		strcpy(mes.string, ch);
	}
	
  	TListElement *l = NULL;

    	switch (mes.action){
        	case 1:{
        		if(mes.name == 0){
        			mes.string = "Fail : Connect to queue, please";
        			break;
        		}
        	    	
        	        PushMessage(&list, mes);
       
            		l = FindElement(&list, mes.name);
            		mes.string = "Message is sended";
            		break;
            		    
        	}
        	case 2:{
        		if(mes.name == 0){
        			mes.string = "Fail : Connect to queue, please";
        			break;
        		}
        		mes.string = (char*)malloc(SIZE*sizeof(char));
        		strcpy(mes.string, PopMessage(&list, mes));
        		l = FindElement(&list, mes.name);
        		break;
        	}
        	case 3:{
        		read(client_sockfd, &mes.name, sizeof(int));   
            		AddInList(&list, mes.name);
            		mes.string = "New queue is created";
            		break;
        	}
        	case 4:{
        		read(client_sockfd, &mes.name, sizeof(int));
        		if(FindElement(&list, mes.name)){
        			mes.string = "Connected";
        		}
        		else{
        			mes.string = "Queue is not in list";
        		}
        		break;
        	}
        	
	}	
	size = strlen(mes.string)+1;
        write(client_sockfd, &size, sizeof(int));
        write(client_sockfd, mes.string, sizeof(char)*strlen(mes.string)+1);
	
	if(l)
		displayQueue(l->queue);
  	
  	close(client_sockfd);
    }
}
