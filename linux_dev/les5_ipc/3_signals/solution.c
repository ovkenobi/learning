#include "signal.h"
#include "stdio.h"

int s1=0;
int s2=0;

void su(int n)
{
	switch (n) {
	case SIGUSR1: s1++; break;
	case SIGUSR2: s2++; break;
	}
}

void sterm(int t)
{
	printf("%d %d\n",s1,s2);

	exit(0);
}

int main(int argc, char** argv)
{
	signal(SIGUSR1, su);
	signal(SIGUSR2, su);
	signal(SIGTERM, sterm);

	while(1);
	

	return 0;
}
