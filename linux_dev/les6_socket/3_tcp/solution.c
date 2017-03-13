#include "stdio.h"
#include "netinet/ip.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "string.h"
#include "stdlib.h"


#define BUF_SIZE 1024*5

int main(int argc, char ** argv)
{
	if (argc != 2) return -1;


	int port = atoi(argv[1]);
	
	int s = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in a;
	inet_aton("127.0.0.1", &a.sin_addr);
	a.sin_port = htons(port);
	a.sin_family = AF_INET;

	bind(s, (struct sockaddr*)&a, sizeof(a));

	listen(s, 5);
	int cs = accept(s, NULL, NULL);

	char buf[BUF_SIZE];

	while(1) {
		
		int n = read(cs, buf, BUF_SIZE);

		if (strncmp(buf, "OFF", 3)==0) {
			break;
		}
		
		int i;
		for (i=0; i<n-1;i++) {
			int j;
			for (j=i+1; j<n-1;j++) {
				if (buf[i]<buf[j]) {
					char t = buf[i];
					buf[i] = buf[j];
					buf[j] = t;
				}
			}
		}
		write(cs, buf, n);
	}

	close(cs);
	close(s);
	return 0;
}
