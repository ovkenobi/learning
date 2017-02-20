#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int check(char* id, int pid)
{
    char name[256];
    sprintf(name, "/proc/%s/stat", id);

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

    if (ppid==pid) return 1;
    else return 0; 
}

int child_count_4_pid(int pid)
{
    int n=0;
    DIR *dir = opendir("/proc");
    if (!dir) {
       printf("error");
       return; 
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL ) {
        if ((entry->d_type & 4) == 4 ) {
            if (isdigit(entry->d_name[0])) {
                if (check(entry->d_name, pid)) {
                    n++;
                    n+=child_count_4_pid(atoi(entry->d_name));
                }
            }
        }
    }
    closedir(dir);
    return n;
}

int main(int c, char **v)
{
    int count = child_count_4_pid(atoi(v[1]))+1;
    printf("%d\n",count);
    return 0;
}
