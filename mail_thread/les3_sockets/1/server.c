#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv)
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	bind(sock, (struct sockaddr *) &addr, sizeof(addr));

	listen(sock, 100);
	
	while(1) {
		struct sockaddr_in addr_r;
		int size = sizeof(addr_r);
		int sock_r = accept(sock, (struct sockaddr*)&addr_r, &size);
		
		if (sock_r>0) {
//			printf("socket #%d\n",sock_r);
			char data[256];
			int n = recv(sock_r, data, sizeof(data)-1, MSG_NOSIGNAL);
			shutdown(sock_r, SHUT_RDWR);
			close(sock_r);
			data[n]=0;
			printf("%s\n",data);
			if (0==strcmp(data,"exit")) {
				break;
			}
		} else {
			printf("Error accept: %s\n", strerror(errno));
		}
	}

	close(sock);
	return 0;
}
