#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <map>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc, char ** argv)
{
	int server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server < 1) {
		std::cerr << "Error create socket\n";
		return -1;
	}
	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(12345);
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int res = bind(server, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
	if (res != 0 ) {
		std::cerr << "Error bind\n";
		return -1;
	}
	
	res = listen(server, SOMAXCONN);
	if (res != 0 ) {
		std::cerr << "Error listen\n";
		return -1;
	}

	fd_set set;

	std::map<int, int> sockets;

	while(1) {
		FD_ZERO(&set);
		FD_SET(server, &set);
		int max_socket = server;
		for (auto s = sockets.begin(); s != sockets.end(); s++) {
			FD_SET(s->first, &set);
		if (s->first > max_socket) {max_socket = s->first;}
		}

		int count = select(max_socket+1, &set, NULL, NULL, NULL);
		for (auto s = sockets.begin(); s != sockets.end(); s++) {
			if (FD_ISSET(s->first, &set)) {
				count--;
				static char buff[2048];
				static char msg[2048];
				int size = recv(s->first, buff, 2048, MSG_NOSIGNAL);
				if ((size == 0) && (errno != EAGAIN)) {
					sprintf(msg, "%s: Disconnected!\n", inet_ntoa(*(in_addr*)&(s->second)));
					shutdown(s->first, SHUT_RDWR);
					close(s->first);
					sockets.erase(s);
				} else if (size > 0) {
					buff[size] = 0;
					sprintf(msg, "%s: %s\n", inet_ntoa(*(in_addr*)&(s->second)), buff);
				}
				
				int len = strlen(msg);
				if (len > 0) {
					for (auto i = sockets.begin(); i != sockets.end(); i++) {
						if (i != s) {
							send(i->first, msg, len, MSG_NOSIGNAL);
						}
					}
					std::cout << msg;
				}
			}
			if (count == 0) {
				break;
			}
		}

		if (FD_ISSET(server, &set)) {
			struct sockaddr_in addr;
			size_t sizeaddr = 0;
			int slave = accept(server, (struct sockaddr*)&addr, &sizeaddr);
			
			sockets[slave] = ntohl(addr.sin_addr.s_addr);
			char msg[32];
			memset(msg, 0, 32);
			sprintf(msg, "%s: Connected\n", inet_ntoa(*(in_addr*)&(sockets.at(slave))));
			std::cout << msg;
			for (auto i = sockets.begin(); i != sockets.end(); i++ ) {
				send(i->first, msg, 32, MSG_NOSIGNAL);
			}
		}

	}
	return 0;
}
