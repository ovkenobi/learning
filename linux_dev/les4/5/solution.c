#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

	if (pid == 0) {
		printf("%d\n", setsid());
		while(1);
	}
    return 0;
}
