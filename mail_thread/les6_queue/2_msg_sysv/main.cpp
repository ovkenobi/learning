#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/*
	Пример использования SysV сообщений
	Создаем очередь по ключу "/tmp/msg.temp"
	Ждем сообщения, печатаем в файл
*/

const char key_name[] = "/tmp/msg.temp";

int main()
{
	key_t key = ftok("/tmp/msg.tmp", 1);
	
	if (key <0) {
		printf("error create key\n");
		return -1;
	}

	printf("key: %d\n", key);
	int fd = open("message.txt", O_RDWR | O_CREAT, 0666);
	if (fd<0) {
		printf("Error create file\n");
		return -1;
	}

	int msgid = msgget(key, IPC_CREAT | 0666);
	if (msgid < 0) {
		printf("Error create msg id\n");
		return -1;
	}
	
	struct message {
		long type;
		char text[2048];
	} msg;

	memset(&msg, 0, sizeof(msg));

	int res = msgrcv(msgid, &msg, 2048, 0, 0);
	
	printf("Receive %d bytes\n", res);

	write(fd, msg.text, 2048);
	close(fd);
	msgctl(msgid, IPC_RMID, 0);

	
	return 0;
}
