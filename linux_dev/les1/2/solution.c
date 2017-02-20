#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
	char libName[128];
	sprintf(libName,"./%s", argv[1]);
	char *funcName = argv[2];
	int arg = atoi(argv[3]);

	void *handle = dlopen(libName, RTLD_LAZY);
	if (handle) {
		int (*soFunc)(int);
		soFunc = (int (*)(int))dlsym(handle, funcName);

		if (soFunc) {
			printf("%d\n",soFunc(arg));
		}
	}
	return 0;
}
