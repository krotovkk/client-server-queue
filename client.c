#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include "message.h"
#define SIZE 80

int main() {
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char ch[SIZE] = "allal";
    
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "receive_socket");
    len = sizeof(address);
    
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1) {
        perror("oops : result -1");
        exit(1);
    }
    
    printf("Choose action please :\n1.Push\n2.Pop\n3.Create queue\n4.Connect to queue\n");

    int action, name, size;
    	
    scanf("%d", &action);
    write(sockfd, &action, sizeof(int));
    
    if(action == 1){
    	printf("Enter your message : ");
    	scanf("%s", ch);
    	size = sizeof(char)*strlen(ch)+1;
    	write(sockfd, &size, sizeof(int));
   	write(sockfd, &ch, sizeof(char)*size);
    }
    
    if(action == 3 || action == 4){
    	printf("Enter queue name : ");
    	scanf("%d", &name);
    	write(sockfd, &name, sizeof(int));
    }
    
    read(sockfd, &size, sizeof(int));
    read(sockfd, &ch, size*sizeof(char));
    printf("%s\n", ch);
    close(sockfd);
    exit(0);
}

