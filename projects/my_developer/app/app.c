/*
 * This is a user-space application that reads /dev/sample
 * and prints the read characters to stdout
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void socket_send()
{
	int sockfd = 0;
	sockfd = socket(AF_INET , SOCK_STREAM , 0);

	if (sockfd == -1){
		printf("Fail to create a socket.");
	}

	struct sockaddr_in info;
	bzero(&info,sizeof(info));
	info.sin_family = AF_INET;

	info.sin_addr.s_addr = inet_addr("192.168.1.100");
	info.sin_port = htons(8080);

	int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
	if(err==-1){
		printf("Connection error");
	}

	//static char message[20] = "Requester: fanfan";
	/*static char message[20];
	malloc(sizeof(char) * 20);
	memset(message, ' ', sizeof(char) * 20);
	for(int i = 0; i < 100000; i++)
		message[i] = (i % 10) + '0';*/

	/* priority queue test */

	int i = 0, optval; // valid values are in the range [1,7], 1- low priority, 7 - high priority
	while(i++ < 1000){
		if(i % 20){
			optval = 7;
			setsockopt(sockfd, SOL_SOCKET, SO_PRIORITY, &optval, sizeof(optval));
			static char message[20] = "Priority: High";
			send(sockfd,message,sizeof(message),0);
		}
		else{
			optval = 4;
			setsockopt(sockfd, SOL_SOCKET, SO_PRIORITY, &optval, sizeof(optval));
			static char message[20] = "Priority: Low";
			send(sockfd,message,sizeof(message),0);
		}
	}
	char receiveMessage[100] = {};
	recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
	//printf("%s",receiveMessage);
	//printf("close Socket\n");
	close(sockfd);
	return NULL;
}

int main(int argc, char **argv)
{
	char * app_name = argv[0];
	char * dev_name = "/dev/sample";
	int ret = -1;
	int fd = -1;
	int c, x;

	/*
 	 * Open the sample device RD | WR
 	 */
	if ((fd = open(dev_name, O_RDWR)) < 0) {
		fprintf(stderr, "%s: unable to open %s: %s\n", 
			app_name, dev_name, strerror(errno));
		goto Done;
	}

	/*
 	 * Read the sample device byte-by-byte
 	 */
	while (1) {
		if ((x = read(fd, &c, 1)) < 0) {
			fprintf(stderr, "%s: unable to read %s: %s\n", 
				app_name, dev_name, strerror(errno));
			goto Done;
		}	
		if (! x) break;

		/*
		 * Print the read character to stdout
		 */
		//fprintf(stdout, "%c", c);
	}

	/*
 	 * If we are here, we have been successful
 	 */
	ret = 0;

	socket_send();

Done:
	if (fd >= 0) {
		close(fd);
	}
	return ret;
}
