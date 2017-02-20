#include "stdio.h"

int stringStat(const char *string, int mult, int *count)
{
	int n=0;
	while (*string){
		string++;
		n++;
	}
	
	*count = (*count)+1;
	
	return n*mult;
}



int main(int argc, char **argv) 
{
	int n=1;
	int res = stringStat("hello",1,&n);
	printf("5=%d 2=%d\n", res, n);
	res = stringStat("",1,&n);
	printf("0=%d 3=%d\n", res, n);
	res = stringStat("12345",0,&n);
	printf("0=%d 4=%d\n", res, n);
	res = stringStat("1234",3,&n);
	printf("12=%d 5=%d\n", res, n);
}
