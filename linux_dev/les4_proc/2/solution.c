#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int findGenenv(const char *dirname) 
{
//    printf("%s\n", dirname);
    int n = 0;
    DIR *dir = opendir(dirname);
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL ) {
//        printf("%s  %d\n", entry->d_name, entry->d_type);
        if ((entry->d_type & 4) == 4 ) {
            if (isdigit(entry->d_name[0])) {
                char s[256];
                memset(s,0,256);
                sprintf(s,"%s/%s",dirname,entry->d_name);
                n += findGenenv(s);
            }
        } else if (0 == strcmp(entry->d_name, "comm")) {
            char s[256];
            char name[256];
            memset(name, 0, 256);
            memset(s,0,256);
            sprintf(name, "%s/comm", dirname);
            int fd = open(name, O_RDONLY);
            if (fd && read(fd, s, 256)>5 && strstr(s, "genenv")) {
                n++;
            }
            close(fd);
        }
    }
    closedir(dir);
    return n;
}

int main(int c, char** v)
{
    printf("%d\n", findGenenv("/proc"));
    return 0;
}
