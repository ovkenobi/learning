#include "stdio.h"
#include "unistd.h"
#include "signal.h"

void signal_handler(int ix)
{
	printf("calling signal #%d\n",ix);
}

int main()
{
	signal(SIGINT, signal_handler);
	int n=0;
	while (1) {
		printf("Hello %d\n", n++);
		sleep(1);
	}
	return 0;
}
