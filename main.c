#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "function.h"
#include "addl.h"
#define BUILD_VERSION "1.0.0"
#define DATABASE_FILE ".\\Database\\library.csv"


int main()
{

    printf("====================================\n");
    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
    printf("====================================\n");
    printf("Version: %s\n", BUILD_VERSION);
    loaddata();
    //testDataBase();
    build_menu();
    int close = 0;
    while (!close){
        switch(getch()){
            case '1':system("cls");
                    printf("====================================\n");
                    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
                    printf("====================================\n");
                    printf("Version: %s\n\n", BUILD_VERSION);
                    search_book();
                    break;
            case '2':system("cls");
                    printf("====================================\n");
                    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
                    printf("====================================\n");
                    printf("Version: %s\n\n", BUILD_VERSION);
                    testDataBase();
                    break;
            case '3':printf("\nThank You for using Library Management System");
                    flushDatabase();
                    close=1;
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
