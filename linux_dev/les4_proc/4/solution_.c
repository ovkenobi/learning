#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

static int count = 1;
static int pid;

void check(char* name)
{
    FILE * fd = fopen(name, "r");
    if (!fd) {
        printf("error open: %s\n", name);
        exit(1);
    }
    
    int ppid=0;
    
    char _[256];
   
    fscanf(fd, "%d %s %s", &ppid, _, _);
    fscanf(fd, "%d", &ppid);

    fclose(fd);

    if (ppid==pid) count++;
}

void findAllProc(char *dirname)
{
    DIR *dir = opendir(dirname);
    if (!dir) {
//       printf("error open dir: %s\n",dirname);
       return; 
    }
//    printf("open\n");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL ) {
        if (((entry->d_type & 4) == 4 ) && entry->d_name[0] != '.') {
            char name[256];
            memset(name,0,256);
            sprintf(name,"%s/%s",dirname,entry->d_name);

            if (isdigit(entry->d_name[0])) {
               check(name);
            }
            findAllProc(name);
        }
    }
    closedir(dir);
}


int main(int c, char **v)
{
    pid = atoi(v[1]);
    findAllProc("/proc");
    printf("%d\n",count);
    return 0;
}
