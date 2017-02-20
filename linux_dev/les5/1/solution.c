#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

/*
	Пример работы с каналами (pipes)
	Пример запуска ./solution someprog arg
	программа запускает переданную в аргементе программу с аргументов arg
	и читает ее вывод, подсчитывает кол-во символов '0'
*/


int main(int count, char **v)
{
	int pipefd[2];
	char s[256];

	memset(&s,0,256);
	
	sprintf(s, "./%s %s", v[1], v[2]);

//	printf("%s\n",s);

	FILE *exe = popen(s, "r");

	char c;
	int n=0;
	while (1 == fread(&c, 1,1,exe)) {
//		printf("%c\n",c);
		if (c=='0') n++;
	}
	fclose(exe);
    printf("%d\n",n);
	
	return 0;
}

