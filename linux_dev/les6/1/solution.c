#include "stdio.h"
#include "netdb.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "arpa/inet.h"

int main(int argc, char ** argv)
{
	if (argc != 2) return -1;

	struct hostent *h = gethostbyname(argv[1]);
	
	if (h) {
		int i=0;
		while ((h->h_addr_list[i]) != NULL) {
			struct in_addr *addr = (struct in_addr*)h->h_addr_list[i];
			printf("%s\n", inet_ntoa(*addr));
			i++;
		}
	}

	return 0;
}
