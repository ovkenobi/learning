#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
#include <stdio.h>
#include <errno.h>

/*
	Пример использования очередей Posix сообщений 
	Создаем очередь по ключу "/test.mq"
	Ждем сообщения, печатаем в файл
*/

const char key_name[] = "/test.mq";

int main()
{
	int fd = open("message.txt", O_RDWR | O_CREAT, 0666);
	if (fd<0) {
		printf("Error create file\n");
		return -1;
	}

	struct mq_attr attr;
	memset(&attr, 0, sizeof(attr));
	attr.mq_maxmsg=10;
	attr.mq_msgsize=128;


	int mqid = mq_open(key_name, O_RDWR | O_CREAT, 0666, &attr);
	if (mqid<0) {
		printf("Eror create message queue\n");
		return -1;
	}

	memset(&attr, 0, sizeof(attr));
	
	if (mq_getattr(mqid, &attr) == -1) {
		printf("error get attr\n");
		return -1;
	}
	printf("Attr:\n");
	printf("\tflags:%ld\n", attr.mq_flags);
	printf("\tmax msg:%ld\n", attr.mq_maxmsg);
	printf("\tsize:%ld\n", attr.mq_msgsize);
	printf("\tcur:%ld\n", attr.mq_curmsgs);
	

	char str[128];

	int res = mq_receive(mqid, str, 128, 0);
	if (res<0) {
		printf("Error receive\n%s\n", strerror(errno));
	} else {
		str[res]=0;
		printf("received %d bytes\n", res);
		write(fd, str, res);
	}

	close(fd);
	mq_unlink(key_name);
	
	return 0;
}
