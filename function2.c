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
#define MAX_BOOKS 10000

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



struct Book* PBOOKS[MAX_BOOKS];
int datasize;

void loaddataV2(){
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
    int i=0;
    for(i=0;i<datasize;i++){
        struct Book* temp = (struct Book*) malloc(sizeof(struct Book));
        if (temp == NULL){
            printf("ERROR ALLOCATING MEMORY.\n");
            return;
        }
        PBOOKS[i]=&temp;
    }

    printf("%d Bytes of Memory Allocated. \n",datasize*sizeof(struct Book));

    struct Book** pBOOKS = PBOOKS;

    while(!feof(data)){
        char* line = fgets(buff,1000,data);
        if (line==NULL){
            break;
        }
        printf("%s",line);
        parse_csv_line(*pBOOKS,line);
        struct Book book = **pBOOKS;
        printf("%d\t%-30s\t%-15s\t%.2f\t%d\t%d\t%d/%d/%d\t\t%d/%d/%d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
        pBOOKS++;
    }

    for(i=0;i<datasize;i++){
        struct Book book = **(PBOOKS+i);
        printf("%d\t%-30s\t%-15s\t%.2f\t%d\t%d\t%d/%d/%d\t\t%d/%d/%d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
    }
    printf("Loaded Database\n");
    fclose(data);
    data=NULL;

}
