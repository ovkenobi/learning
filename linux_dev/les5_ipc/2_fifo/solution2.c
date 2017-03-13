#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_digit(int fd)
{	
	usleep(5000);
	char buf[256];
	int size = read(fd,buf,255);
	if (size>0)	buf[size]=0;
	else return 0;
	printf("%d: %d '%s'\n", fd, size, buf);
	return atoi(buf);
}


int main(int argc, char** argv)
{
	int in1=open("./in1", O_RDWR);
	int in2=open("./in2", O_RDWR);

//	printf("descriptors: %d %d\n",in1,in2);
	
	int fd = ((in1>in2)?in1:in2)+1;
	int sum=0;
	struct timeval timeout;
	timeout.tv_sec=4;
	timeout.tv_usec=1000;
	if (in1>0 && in2>0) {
		do {
			fd_set rfds;
			FD_ZERO(&rfds);
			FD_SET(in1, &rfds);
			FD_SET(in2, &rfds);

			int afd = select(fd, &rfds, NULL, NULL, &timeout);
			if (afd==0) break;
//			printf("select(%d)\n",afd);
			if (FD_ISSET(in1,&rfds)) {
				sum += get_digit(in1);
//				printf("read from in1\n");
			} 
			if (FD_ISSET(in2,&rfds)) {
				sum += get_digit(in2);
//				printf("read from in2\n");
			}
//			printf("sum %d\n", sum);
		} while (1);
	}
	close(in1);
	close(in2);

	printf("%d\n", sum);
	return 0;
}
