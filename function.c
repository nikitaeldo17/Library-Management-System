#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include <conio.h>
#include <time.h>
#include "addl.h"

#define BUILD_VERSION "1.0.0"
#define DATABASE_FILE ".\\Database\\library.csv"
#define BUFFERWIDTH_RATIO 0.5

struct date{
    int dd,mm,yy;
};

struct Book{
    int id;
    char name[100];
    char author[100];
    double price;
    int count;
    int rack;
    struct date issued;
    struct date duedate;
};

struct Book* data_dynamic;
int datasize;
int maxsize;

struct date make_date(char str[]){
    int dd = 0 ,mm = 0,yy = 0;
    sscanf(str,"%d %d %d",&dd,&mm,&yy);
    //printf("%s = %d , %d , %d\n",str,dd,mm,yy);
    struct date myDate;
    myDate.dd = dd;
    myDate.mm = mm;
    myDate.yy = yy;
    return myDate;
}

void parse_csv_line(struct Book* book, char* str){

    int count = 0;

    char word[100];
    char* pWord =word;

    char* beg=word;

    while(*str != '\0'){

        if(*str == ',' || *str == '\n'){

            //printf("...%s...\n",beg);

            switch(count){
                case 0: //printf("CASE 0 called\n");
                        book -> id= atoi(beg);
                        break;
                case 1: //printf("CASE 1 called\n");
                        strcpy(book -> name,beg);
                        break;
                case 2: //printf("CASE 2 called\n");
                        strcpy(book -> author,beg);
                        break;
                case 3: //printf("CASE 3 called\n");
                        book -> price = atof(beg);
                        break;
                case 4: //printf("CASE 4 called\n");
                        book -> count = atoi(beg);
                        break;
                case 5: //printf("CASE 5 called\n");
                        book -> rack = atoi(beg);
                        break;
                case 6: //printf("CASE 6 called\n");
                        book -> issued = make_date(beg);
                        break;
                case 7: //printf("CASE 7 called\n");
                        book -> duedate = make_date(beg);
                        break;
            }

            count++;
            pWord=beg;
            *beg = '\0';
        }
        else{
            if(pWord-beg > (100* sizeof(char))){
                printf("ERROR: Text Overflow.\n");
                exit(0);
            }
            *pWord=*str;
            pWord++;
            *pWord='\0';
        }
        if(*str == '\0')
            break;
        str++;
    }
    count=0;
}

void loaddata(){
    //start loading
    printf("Loading.....");
    FILE* data = fopen(DATABASE_FILE,"r");
    if(data == NULL){
        printf("Failed to open Database\n");
        return;
    }

    // buffer to store input
    char buff[1000];

    //first line of csv holds the number of entries
    char* entries = fgets(buff,1000,data);
    if (entries==NULL){
        printf("ERROR.\n");
        return;
    }
    datasize=atoi(entries);

    printf("%d entries found. ",datasize);
    //allocate dynamic memory

    int size = (int)((1.0+BUFFERWIDTH_RATIO)*datasize*sizeof(struct Book));

    data_dynamic = (struct Book*) malloc(((100*sizeof(struct Book))> size ? 100*sizeof(struct Book) : size));
    if (data_dynamic == NULL){
        printf("ERROR ALLOCATING MEMORY.\n");
        return;
    }
    printf("%d Bytes of Memory Allocated. \n",((100*sizeof(struct Book))> size ? 100*sizeof(struct Book) : size));

    maxsize=((int)((1.0+BUFFERWIDTH_RATIO)*datasize)) > 100 ? ((int)((1.0+BUFFERWIDTH_RATIO)*datasize)) : 100;

    struct Book* pData_dynamic = data_dynamic;
    while(!feof(data)){
        char* line = fgets(buff,1000,data);
        if (line==NULL){
            break;
        }
        parse_csv_line(pData_dynamic,line);
        pData_dynamic++;
    }
    printf("Loaded Database\n");
    fclose(data);
    data=NULL;
}

void testDataBase(){
    int i;
    printf("++++++++++++++++++++++++++++++++++++++++++++++++++++BOOK LIST++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("BOOK ID\t%-30s\t%-15s\tPRICE\tRACK NO\tCOUNT\tISSUED ON\tDUE DATE\n","NAME","AUTHOR");
    for(i=0;i<datasize;i++){
        struct Book book = *(data_dynamic + i);
        printf("%d\t%-30s\t%-15s\t%.2f\t%d\t%d\t%d/%d/%d\t\t%d/%d/%d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
    }
    printf("===============================================================================================================\n");
    printf("Press A to add new Book, R to Return.\n");
    int close = 0;
    while(!close){
        switch(getch()){
            case 'A':
            case 'a':
                    add_book();
                    struct Book book = *(data_dynamic + datasize -1);
                    printf("Book Details : ID:%d\t%s\t%s\t%.2f\t%d\t%d\t%d/%d/%d\t\t%d/%d/%d\n",book.id,book.name,book.author,book.price,
                    book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
                    book.duedate.dd,book.duedate.mm,book.duedate.yy);
                    printf("Press A to add new Book, R to Return.\n");
                    break;
            case 'R':
            case 'r':
                    system("cls");
                    printf("====================================\n");
                    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
                    printf("====================================\n");
                    printf("Version: %s\n\n", BUILD_VERSION);
                    build_menu();
                    close=1;
                    break;
        }
    }
}

void build_menu(){
    printf("1. SEARCH FOR BOOK\n");
    printf("2. VIEW DATABASE\n");
    printf("3. EXIT\n");
    printf("Enter Choice: ");
}

void flushDatabase(){
    FILE* data = fopen(DATABASE_FILE,"w");
    if(data == NULL){
        printf("Failed to save Database\n");
        return;
    }
    fprintf(data,"%d\n",datasize);
    int i;
    for(i=0;i<datasize;i++){
        struct Book book = *(data_dynamic + i);
        fprintf(data,"%d,%s,%s,%.2f,%d,%d,%d %d %d,%d %d %d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
    }
    fclose(data);
    data=NULL;
}

void add_book(){
    datasize++;
    if(datasize > maxsize){
        printf("ERROR BOOK BUFFER OVERFLOW.");
        flushDatabase();
        exit(1);
    }
    printf("Name of Book : ");
    char name[100];
    gets(name);
    printf("Name of Author : ");
    char author[100];
    gets(author);
    char buff[100];
    printf("Book Id : ");
    int bookid = atoi(gets(buff));
    printf("Count : ");
    int count = atoi(gets(buff));
    printf("Rack No : ");
    int rack = atoi(gets(buff));
    printf("Price : ");
    double price = atof(gets(buff));
    struct Book* book = (data_dynamic + datasize -1);
    book -> id=bookid;
    strcpy(book -> name,name);
    strcpy(book -> author,author);
    book -> price = price;
    book -> rack = rack;
    book -> count =count;
    book -> issued.dd = 0;
    book -> issued.mm = 0;
    book -> issued.yy = 0;
    book -> duedate.dd = 0;
    book -> duedate.mm = 0;
    book -> duedate.yy = 0;
    if((*book).id == bookid){
        printf("Book addition successful.\n");
    }
    else{
        printf("Adding book failed.\n");
    }
}

void editbook(struct Book* pBook){
    printf("====================================\n");
    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
    printf("====================================\n");
    printf("Version: %s\n\n", BUILD_VERSION);
    printf("Name of Book: %s\n",pBook -> name);
    printf("Book Id: %d\n",pBook -> id);
    printf("Author: %s\nPrice:%.2f\nRack No. : %d\nNumber of Books in Stock: %d\nIssued Date:%d/%d/%d Due Date:%d/%d/%d\n",pBook->author,pBook->price,
               pBook->rack,pBook->count,pBook->issued.dd,pBook->issued.mm,pBook->issued.yy,
               pBook->duedate.dd,pBook->duedate.mm,pBook->duedate.yy);
    printf("I to issue, 1 to Edit Name, 2 to Edit Author, 3 to Edit Price, 4 to Edit Count, 5 to Edit Rack Number and E to Exit\n");
    int close=0;
    char buff[100];
    int flag=0;
    int i=0;
    while(!close){
        switch(getch()){
            case 'e':
            case 'E':close= 1;
                     break;
            case '1':printf("Name of Book : ");
                    char name[100];
                    gets(name);
                    strcpy(pBook->name,name);
                    close=1;
                    break;
            case '2':printf("Name of Author : ");
                    char author[100];
                    gets(author);
                    strcpy(pBook->author,author);
                    close=1;
                    break;
            case '3':printf("Price : ");
                    double price = atof(gets(buff));
                    pBook->price=price;
                    close=1;
                    break;
            case '4':printf("Count : ");
                    int count = atoi(gets(buff));
                    pBook->count=count;
                    close=1;
                    break;
            case '5':printf("Rack No : ");
                    int rack = atoi(gets(buff));
                    pBook->rack=rack;
                    close=1;
                    break;
            case 'i':
            case 'I':
                    printf("Enter Issue Date as DD <ENTER> MM <ENTER> YY:\n");
                    int dd = atoi(gets(buff));
                    pBook->issued.dd=dd;
                    int mm = atoi(gets(buff));
                    pBook->issued.mm=mm;
                    int yy = atoi(gets(buff));
                    pBook->issued.yy=yy;
                    printf("Enter Due Date as DD <ENTER> MM <ENTER> YY:\n");
                    dd = atoi(gets(buff));
                    pBook->duedate.dd=dd;
                    mm = atoi(gets(buff));
                    pBook->duedate.mm=mm;
                    yy = atoi(gets(buff));
                    pBook->duedate.yy=yy;
                    close=1;
                    break;
            case 'D':
            case 'd':
                    for(i=0;i<datasize-1;i++){
                        struct Book* book = (data_dynamic + i);
                        if(pBook->id == book->id)
                            flag=1;
                        if(flag){
                            strcpy(book->author,(book+1)->author);
                            strcpy(book->name,(book+1)->name);
                            book->id = (book+1)->id;
                            book->count = (book+1)->count;
                            book->rack = (book+1)->rack;
                            book->price = (book+1)->price;
                            book->issued = (book+1)->issued;
                            book->duedate = (book+1)->duedate;
                        }
                    }
                    datasize--;
                    close=1;
                    break;
            default:printf("\nUnknown Input. Try Again.\nEnter Choice:");
                    break;
                }
    }
}

void by_name(char* name){
    int i=0;
    for(i=0;i<datasize;i++){
        struct Book book = *(data_dynamic + i);
        struct Book* pBook = (data_dynamic + i);
        char* a = stristr(book.name,name);
        if(a!=NULL){
            printf("%d\t%-30s\t%-15s\t%.2f\t%d\t%d\t%d/%d/%d\t\t%d/%d/%d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
            printf("E to Edit, N for Next\n");
            int close=0;
            while(!close){
                switch(getch()){
                    case 'e':
                    case 'E':system("cls");
                            editbook(pBook);
                            close=1;
                            break;
                    case 'n':
                    case 'N':close=1;
                            break;
                    default:printf("\nUnknown Input. Try Again.\nEnter Choice:");
                            break;
                }
            }
        }
    }
    printf("End Of List.");
}

void by_author(char* author){
    int i=0;
    for(i=0;i<datasize;i++){
        struct Book book = *(data_dynamic + i);
        struct Book* pBook = (data_dynamic + i);
        char* a = stristr(book.author,author);
        if(a!=NULL){
            printf("%d\t%-30s\t%-15s\t%.2f\t%d\t%d\t%d/%d/%d\t\t%d/%d/%d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
            printf("E to Edit, N for Next\n");
            int close=0;
            while(!close){
                switch(getch()){
                    case 'e':
                    case 'E':system("cls");
                            editbook(pBook);
                            close=1;
                            break;
                    case 'n':
                    case 'N':close=1;
                            break;
                    default:printf("\nUnknown Input. Try Again.\nEnter Choice:");
                            break;
                }
            }
        }
    }
    printf("End Of List.");
}

void by_rack(int rck){
    int i=0;
    for(i=0;i<datasize;i++){
        struct Book book = *(data_dynamic + i);
        struct Book* pBook = (data_dynamic + i);
        int a = rck == book.rack;
        if(a!=0){
            printf("%d\t%-30s\t%-15s\t%.2f\t%d\t%d\t%d/%d/%d\t\t%d/%d/%d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
            printf("E to Edit, N for Next\n");
            int close=0;
            while(!close){
                switch(getch()){
                    case 'e':
                    case 'E':system("cls");
                            editbook(pBook);
                            close=1;
                            break;
                    case 'n':
                    case 'N':close=1;
                            break;
                    default:printf("\nUnknown Input. Try Again.\nEnter Choice:");
                            break;
                }
            }
        }
    }
    printf("End Of List.");
}

void search_book(){
    printf("Search By ?\n1. Name\n2. Author\n3. Rack\nEnter Choice:");
    int close=0;
    while(!close){
        switch(getch()){
            case '1':printf("\nEnter Name or Part of Name:");
                    char name[50];
                    gets(name);
                    by_name(name);
                    close=1;
                    waitFor(1);
                    system("cls");
                    printf("====================================\n");
                    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
                    printf("====================================\n");
                    printf("Version: %s\n\n", BUILD_VERSION);
                    build_menu();
                    break;
            case '2':printf("\nEnter Author Name or Part of Author Name:");
                    char auth[50];
                    gets(auth);
                    by_author(auth);
                    close=1;
                    waitFor(1);
                    system("cls");
                    printf("====================================\n");
                    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
                    printf("====================================\n");
                    printf("Version: %s\n\n", BUILD_VERSION);
                    build_menu();
                    break;
            case '3':printf("\nEnter Rack No:");
                    char buff[50];
                    gets(buff);
                    by_rack(atoi(buff));
                    close=1;
                    waitFor(1);
                    system("cls");
                    printf("====================================\n");
                    printf("WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
                    printf("====================================\n");
                    printf("Version: %s\n\n", BUILD_VERSION);
                    build_menu();
                    break;
            default:printf("\nUnknown Input. Try Again.\nEnter Choice:");
                    break;
        }
    }
}
