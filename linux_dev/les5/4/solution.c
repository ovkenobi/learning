#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "signal.h"

void sigurg(int s_ix)
{
	exit(0);
}

int main()
{
    pid_t pid = fork();

	if (pid == 0) {
		printf("%d\n", setsid());
		signal(SIGURG, sigurg);
		while(1);
	}
    return 0;
}
