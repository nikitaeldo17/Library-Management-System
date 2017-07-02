#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    testDataBase();
    build_menu();
    int close = 0;
    while (!close){
        switch(getchar()){
            case '1':break;
            case '2':break;
            case '3':break;
            case '4':break;
            case '5':break;
            case '6':printf("Thank You for using Library Management System");
                    flushDatabase();
                    exit(0);
                    break;
            default:printf("Unknown Input\n");
                    waitFor(1);
                    system("cls");
                    printf("====================================\n");
                    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
                    printf("====================================\n");
                    printf("Version: %s\n\n", BUILD_VERSION);
                    build_menu();
                    break;
        }
    }
    return 0;
}
