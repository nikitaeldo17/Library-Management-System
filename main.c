#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#define BUILD_VERSION "1.0.0"
#define DATABASE_FILE ".\\Database\\library.csv"


int main()
{

    printf("====================================\n");
    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
    printf("====================================\n");
    printf("Version: %s\n", BUILD_VERSION);
    loaddata();
    build_menu();
    int close = 0;
    while (!close){

    }
    return 0;
}
