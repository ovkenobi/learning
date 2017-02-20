#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

/*
	Пример использования парсера аргументов getopt
*/



int main(int argc, char **argv)
{

    struct option options[] = {
        {"query", required_argument, 0, 'q'},
        {"longinformationrequest", no_argument, 0, 'i'},
        {"version", no_argument, 0, 'v'},
        {0,0,0,0}
    };
    
    int ix = 0;
    int res = 0;
    
    while ((res=getopt_long(argc, argv, "q:iv", options, &ix)) != -1) {
        switch (res) {
            case 0: printf("-\n"); return 0;
            case 'i': 
            case 'v': if (optarg) {printf("-\n"); return 0;} else break;
            case 'q': if (!optarg) {printf("-\n"); return 0;} else break;
            default : printf("-\n"); return 0;
        }
    }
    printf("+\n");
    return 0;
}

