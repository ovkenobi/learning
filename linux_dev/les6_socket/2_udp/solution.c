#include "stdio.h"
#include "netinet/ip.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "string.h"
#include "stdlib.h"

#define BUF_SIZE 1024*5

int main(int argc, char **argv)
{
	if (argc != 2) {
		return -1;
	}
	int port = atoi(argv[1]);
	int s = socket(AF_INET, SOCK_DGRAM, 0);

	if (s<=0) {
		printf("error\n");
		return -1;
	}

	struct sockaddr_in a;
	inet_aton("127.0.0.1", &a.sin_addr);
	a.sin_port = htons(port);
	a.sin_family = AF_INET;

	int n = bind(s, (struct sockaddr*)&a, sizeof(a));
	
//	printf("bind: %d %d\n",port,n);


	int res = BUF_SIZE;

	char buf[BUF_SIZE];
	while (1){
		memset(buf, 0, res);
		res=read(s,buf,BUF_SIZE);
		if (strcmp(buf,"OFF\n")==0) {
			break;
		}

		printf("%s\n",buf);

	}
	close(s);
}
