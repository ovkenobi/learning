#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int parent_id(int id)
{
    char name[256];
    sprintf(name, "/proc/%d/stat", id);
    FILE * fd = fopen(name, "r");
    if (!fd) {
        printf("error open: %s\n", name);
        exit(1);
    }

    int n1=0;
    char s1[256];
    memset(s1,0,256);

    fscanf(fd, "%d %s %s %d", &n1,s1,s1,&n1);
//    fscanf(fd, "%d", &n1);
    return n1;
}

int main(int c, char ** v)
{
    int i = atoi(v[1]);
    printf("%d\n",i);
 
    while (i!=1) {
        i = parent_id(i);
        printf("%d\n",i);
    }

    return 0;
}
