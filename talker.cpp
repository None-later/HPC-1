#include <curses.h>

extern "C"
{
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <errno.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
}

#define SERVERPORT "4950"	// the port users will be connecting to
void sendMsg(char **argv, int nodeCount,  char *msg);

int main(int argc, char *argv[])
{
	int key = 0;
	initscr();
	cbreak();

	while(key != 'q')
	{
		key = wgetch(stdscr);

		if(key == 'w') //increase
		{
			clear();
			printw("\rClock Increase\r");
			sendMsg(argv, argc, "w");
		}
		else if(key == 's') //Decrease
		{
			clear();
			printw("\rClock Decrease\r");
			sendMsg(argv, argc, "s");
		}
	}

	endwin();
	return 0;
}

void sendMsg(char **argv, int nodeCount, char *msg)
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	/*if (argc != 3) {
		fprintf(stderr,"usage: talker hostname message\n");
		exit(1);
	}*/

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	for(int i = 1; i < nodeCount; i++)
	{
		printw("Send msg to: %s\n", argv[i]);
		if ((rv = getaddrinfo(argv[i], SERVERPORT, &hints, &servinfo)) != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		}

		// loop through all the results and make a socket
		for(p = servinfo; p != NULL; p = p->ai_next) {
			if ((sockfd = socket(p->ai_family, p->ai_socktype,
					p->ai_protocol)) == -1) {
				perror("talker: socket");
				continue;
			}

			break;
		}

		if (p == NULL) {
			fprintf(stderr, "talker: failed to create socket\n");
		}

		if ((numbytes = sendto(sockfd, msg, strlen(msg), 0,
				 p->ai_addr, p->ai_addrlen)) == -1) {
			perror("talker: sendto");
			exit(1);
		}
	

		printw("Sent: %s to %s\n", msg, argv[i]);
		refresh();
		close(sockfd);
	}
	freeaddrinfo(servinfo);
}
