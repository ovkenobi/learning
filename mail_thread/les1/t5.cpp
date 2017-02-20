#include <iostream>
#include <stdlib.h>

int main()
{
    u_int32_t *i = (u_int32_t*)1024;
    i++;
    std::cout << i << "\n";
    return 0;
}
