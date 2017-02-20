#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_digit(int fd)
{	
	char buf[256];
	int size = read(fd,buf,255);
	if (size>0)	buf[size]=0;
	else return 0;
	return atoi(buf);
}

int main(int argc, char** argv)
{
	int sum=0;
	int c=0;

	int in1=open("./in1", O_RDWR);
	int in2=open("./in2", O_RDWR);

	int fd = in2+1;

	fd_set fd_read;
	struct timeval t;
	t.tv_sec=4;
	t.tv_usec=730000;

	do {

		FD_ZERO(&fd_read);
		FD_SET(in1, &fd_read);
		FD_SET(in2, &fd_read);

		int afd = select(fd, &fd_read, NULL, NULL, &t);
		if (FD_ISSET(in1,&fd_read)) {
			sum += get_digit(in1);
		} 
		if (FD_ISSET(in2,&fd_read)) {
			sum += get_digit(in2);
		}
//		printf("%d: %d %d\n", afd, sum, c);
		if (afd == 0)  break;

	} while (c<2);

	printf("%d\n", sum);
	return 0;
}
