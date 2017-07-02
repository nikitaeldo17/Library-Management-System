#include <stdio.h>
#include <string.h>

#define DATABASE_FILE ".\\Database\\library.csv"

struct Book* data_dynamic;


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
    int datasize=atoi(entries);

    printf("%d entries found. ",datasize);
    //allocate dynamic memory

    data_dynamic = (struct Book*) malloc(datasize*sizeof(struct Book));
    if (data_dynamic == NULL){
        printf("ERROR ALLOCATING MEMORY.\n");
        return;
    }
    printf("%d Bytes of Memory Allocated. ",datasize*sizeof(struct Book));

    while(!feof(data)){
        char* line = fgets(buff,1000,data);
        if (line==NULL){
            printf("ERROR.\n");
            return;
        }

    }
    printf("Loaded Database\n");
}

void parse_csv_line(struct Book* book, char* str){
    int count = 0;
    char word[100];
    char* beg=word;
    while(*str != '\0'){
        if(*str == ','){
            word++;
            printf("%s",beg);
            switch(count){
                case 0: book -> id= atoi(beg);
                        break;
                case 1: book -> name = beg;
                        break;
                case 2: book -> author = beg;
                        break;
                case 3: book -> price = atof(beg);
                        break;
                case 4: book -> count = atoi(beg);
                        break;
                case 5: book -> rack = atoi(beg);
                        break;
                case 6: book -> issued = make_date(beg);
                        break;
                case 7: book -> duedate = make_date(beg);
                        break;
            }
            count++;
            word=beg;
            *beg = '\0';
        }
        else{
            *word=*str;
            word++;
        }
        str++;
    }
    count=0;
}

date make_date(char str[]){

}

void build_menu(){
    printf("1. ADD BOOK\n");
    printf("2. DELETE BOOK\n");
    printf("3. EDIT BOOK\n");
    printf("4. ISSUE BOOK\n");
    printf("5. SEARCH FOR BOOK\n");
    printf("6. EXIT\n");
}
