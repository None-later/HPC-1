#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <curses.h>


/*
** listener.c -- a datagram sockets "server" demo
*/

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
#define MYPORT "4950"	// the port users will be connecting to

#define MAXBUFLEN 100

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main()
{
	std::vector<int> clocks;
	std::string str = "1380 1372 1365 1357 1350 1342 1335 1327 1320 1312 1305 1297 1290 1282 1275 1267 1260 1252 1245 1237 1230 1222 1215 1207 1200 1192 1185 1177 1170 1162 1155 1147 1140 1132 1125 1117 1110 1102 1095 1087 1080 1072 1065 1057 1050 1042 1035 1027 1020 1012 1005 997 990 982 975 967 960 952 945 937 930 922 915 907 900 892 885 877 870 862 855 847 840 832 825 817 810 802 795 787 780 772 765 757 750 742 735 727 720 712 705 697 690 682 675 667 660 652 645 637 630 622 615 607 600 592 585 577 570 562 555 547 540 532 525 517 510 502 495 487 480 472 465 457 450 442 435 427 420 412 405 397 390 382 375 367 360 352 345 337 330 322 315 307 300 292 285 277 270 262 255 247 240 232 225 217 210 202 195 187 180 172 165 157 150 142 135";
	
	std::stringstream ss(str);
	int i = 0;
	int currClock = 1335;
	int key = 0;
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN];
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
	std::string command;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	while(ss >> i)
	{
		clocks.push_back(i);
		
		if(ss.peek() == ' ')
		{
			ss.ignore();
		}
	}

		
	ptrdiff_t index = std::find(clocks.begin(), clocks.end(), currClock) - clocks.begin();
	
///////////////////////////////////////////////////////////////////////////////////////
	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1) {
			perror("listener: socket");
			continue;
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("listener: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		return 2;
	}

	freeaddrinfo(servinfo);

	printf("listener: waiting to recvfrom...\n");
	
	while(strcmp(buf, "q") != 0)
	{
		memset(&buf[0], 0, sizeof(buf));
		addr_len = sizeof their_addr;
		if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0, (struct sockaddr *)&their_addr, &addr_len)) == -1) 
		{
			perror("recvfrom");
			exit(1);
		}
	
		//printf("listener: %s\n", buf);
	
		if(strcmp(buf, "test") == 0)
		{
			printf("Received test\n");
		}

		if(strcmp(buf, "s")) //Increase
		{
			index--;
			if(index < 0)
			{
				index = 0;
			}
			command = "./update_GPU_Clocks.sh " + std::to_string(clocks.at(index));
			printf("Clocks set to: %d\n", clocks.at(index));
			system(command.c_str());
		}

		if(strcmp(buf, "w")) //Decrease
		{
			index++;
			if(index > clocks.size() - 1)
			{
				index = clocks.size() - 1;
			}

			printf( "Clocks set to: %d\n", clocks.at(index));   
		}
	}	
	close(sockfd);

	return 0;
}



