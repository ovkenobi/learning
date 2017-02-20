/*
   ВОЗВРАЩАЕТ PID РОДИТЕЛЬСКОГО ПРОЦЕССА
   Парсит /proc/self/status в поисках строки
   с PPid и возвращает найденное число
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main(int c, char **v)
{
    FILE *fp;

    char *line = 0;
    size_t len=0;
    ssize_t read;

    char *fname;
    
    fname = "/proc/self/status";

    fp = fopen(fname, "r");

    if (!fp) {
        printf("error open\n");
        return 0;
    }

    while ((read = getline(&line, &len, fp)) != -1 ) {
        if (strstr(line, "PPid")) {
            printf("%s", line + 6);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);

    if (line) free(line);
    return 0;
}
