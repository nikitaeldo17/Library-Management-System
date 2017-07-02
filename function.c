#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"
#include <conio.h>
#include <time.h>

#define DATABASE_FILE ".\\Database\\library.csv"
#define BUFFERWIDTH_RATIO 0.5

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

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

    data_dynamic = (struct Book*) malloc((int)((1.0+BUFFERWIDTH_RATIO)*datasize*sizeof(struct Book)));
    if (data_dynamic == NULL){
        printf("ERROR ALLOCATING MEMORY.\n");
        return;
    }
    printf("%d Bytes of Memory Allocated. \n",(int)((1.0+BUFFERWIDTH_RATIO)*datasize*sizeof(struct Book)));

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
    for(i=0;i<datasize;i++){
        struct Book book = *(data_dynamic + i);
        printf("%d %s %s %f %d %d %d/%d/%d %d/%d/%d\n",book.id,book.name,book.author,book.price,
               book.rack,book.count,book.issued.dd,book.issued.mm,book.issued.yy,
               book.duedate.dd,book.duedate.mm,book.duedate.yy);
    }

}

void build_menu(){
    printf("1. ADD BOOK\n");
    printf("2. DELETE BOOK\n");
    printf("3. EDIT BOOK\n");
    printf("4. ISSUE BOOK\n");
    printf("5. SEARCH FOR BOOK\n");
    printf("6. EXIT\n");
    printf("Enter Choice: ");
}
