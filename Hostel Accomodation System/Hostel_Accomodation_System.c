#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

struct date {
    int  day;
    int  month;
    int  year;
};

struct student {
    char name[40];
    int  roll;
    char gender[10];
    char course[10];
    char dob[15];
    char city[20];
    char mobile[12];
    char hostel;
    int  room_no;
    /*char room_alph;
    int  room_num;*/
};

//USER FUNCTIONS:
void reg_info();
void disp_info();
void mod_info();
void del_info();
//ADMIN FUNCTIONS:
int  no_of_rec();
int  check_roll(int);
void clr_file();
void printRandom();
int  room_allot();
int  get_room(int);

int lower=1, upper=30;

int main() {
    int  ch;
    int  test;
    system("cls");
    //MAIN MENU
    printf("Welcome to Hostel accomodation program\n");
    printf("----------------------------------------");

    do {
        printf("\n1.Register for new application");
        printf("\n2.Display existing application");
        printf("\n3.Modify existing application");
        printf("\n4.Delete existing application");
        printf("\n5.EXIT");

        printf("\n\nTOTAL NUMBER OF REGISTERED STUDENTS:::::>%d", no_of_rec());

        printf("\n\nEnter your choice:::> ");
        scanf("%d",&ch);
        system("cls");

        switch(ch) {
        case 1: reg_info();
                system("cls");
                break;
        case 2: disp_info();
                system("cls");
                break;
        case 3: mod_info();
                system("cls");
                break;
        case 4: del_info();
                system("cls");
                break;
        case 6: no_of_rec();
                system("cls");
                break;
        case 7: clr_file();
                system("cls");
                break;
        case 8: printf("Enter a number: ");
                scanf("%d",&test);
                printf("isdigit? = %d",isdigit(test));
                printf("isalpha? = %d",isalpha(test));
                getchar();
                getchar();
                break;
        }

    } while(ch!=5);

    return 0;
}

void reg_info() {
    int roll;

    struct student stud;

    FILE *fptr = fopen("details.txt","a+");

    printf(":::::::::::::::NEW REGISTRATION:::::::::::::::\n\n");
    printf("ROLL NUMBER:::::::::::::::> ");
    scanf("%d",&stud.roll);
    roll = stud.roll;

    if(check_roll(roll) == 0) {
        printf("FULL NAME:::::::::::::::::> ");
        scanf(" %[^\n]s",stud.name);
        printf("GENDER::::::::::::::::::::> ");
        scanf(" %s",stud.gender);
        printf("COURSE::::::::::::::::::::> ");
        scanf(" %s",stud.course);
        printf("DOB (DD/MM/YYYY)::::::::::> ");
        scanf(" %s",stud.dob);
        printf("CITY::::::::::::::::::::::> ");
        scanf(" %s",stud.city);
        printf("MOBILE::::::::::::::::::::> ");
        scanf(" %s",stud.mobile);

        if(!strcmp(stud.city,"Mumbai") || !strcmp(stud.city,"mumbai") || !strcmp(stud.city,"Bombay") || !strcmp(stud.city,"bombay")) {
            stud.room_no = 100;
        } else {
            srand(time(NULL));
            stud.room_no = get_room((rand()%(upper - lower + 1))+ lower);
        }
    } else {
        printf("The entered roll no already exists\nPlease try again... ");
        getchar();
        getchar();
        system("cls");
        return;
    }

    if(stud.room_no != 0) {
        if(!strcmp(stud.gender,"Male") || !strcmp(stud.gender,"male") || !strcmp(stud.gender,"M")) {
            stud.hostel = 'A';
            fwrite(&stud,sizeof(stud),1,fptr);
        } else if(!strcmp(stud.gender,"Female") || !strcmp(stud.gender,"female") || !strcmp(stud.gender,"F")) {
            stud.hostel = 'B';
            fwrite(&stud,sizeof(stud),1,fptr);
        } else {
            printf("\nEnter a valid gender");
            goto End;
        }
    }

    printf("\nYour details have been saved succesfully");

    End:
    printf("\nPress ENTER to continue...");
    fclose(fptr);
    getchar();
    getchar();
    system("cls");
    return;
}

void disp_info() {
    struct student stud;

    FILE *fptr = fopen("details.txt","r");
    int roll,found=0;

    //rollEnter:
    printf("Enter your roll number::::> ");
    scanf("%d",&roll);

    while(fread(&stud,sizeof(struct student),1,fptr)) {
        if(stud.roll == roll) {
            found = 1;
            printf("\nFULL NAME:::::::::::::::::> %s",stud.name);
            printf("\nROLL NUMBER:::::::::::::::> %d",stud.roll);
            printf("\nGENDER::::::::::::::::::::> %s",stud.gender);
            printf("\nCOURSE::::::::::::::::::::> %s",stud.course);
            printf("\nDOB (DD/MM/YYYY)::::::::::> %s",stud.dob);
            printf("\nCITY::::::::::::::::::::::> %s",stud.city);
            printf("\nMOBILE::::::::::::::::::::> %s",stud.mobile);

            if(stud.room_no != 0 && stud.room_no != 100) {
                printf("\nROOM ALLOTED::::::::::::::> %c-%d",stud.hostel,stud.room_no);
            } else {
                printf("\nROOM ALLOTED::::::::::::::> Not alloted");
            }
        }
    }

    if(found == 0) {
        printf("\nStudent doesn't exist please register yourself");
    }

    perror("\n\nError: ");
    fclose(fptr);
    printf("\n\nPress ENTER to continue");
    getchar();
    getchar();
    return;
}

void mod_info() {
    struct student stud;

    FILE *fptr  = fopen("details.txt","r");
    FILE *fptr1 = fopen("temp.txt","w");
    int roll,found=0;

    //rollEnter:
    printf("Enter your roll number::::> ");
    scanf("%d",&roll);

    while(fread(&stud,sizeof(struct student),1,fptr)) {
        if(stud.roll == roll) {
            found = 1;
            printf("\n:::::::::::::::OLD INFORMATION:::::::::::::::\n\n");
            printf("FULL NAME:::::::::::::::::> %s",stud.name);
            printf("\nROLL NUMBER:::::::::::::::> %d",stud.roll);
            printf("\nGENDER::::::::::::::::::::> %s",stud.gender);
            printf("\nCOURSE::::::::::::::::::::> %s",stud.course);
            printf("\nDOB (DD/MM/YYYY)::::::::::> %s",stud.dob);
            printf("\nCITY::::::::::::::::::::::> %s",stud.city);
            printf("\nMOBILE::::::::::::::::::::> %s",stud.mobile);

            if(stud.room_no != 0 && stud.room_no != 100) {
                printf("\nROOM ALLOTED::::::::::::::> %c-%d",stud.hostel,stud.room_no);
            } else {
                printf("\nROOM ALLOTED::::::::::::::> Not alloted");
            }

            printf("\n\n:::::::::::::::NEW INFORMATION:::::::::::::::\n\n");
            printf("FULL NAME:::::::::::::::::> ");
            scanf(" %[^\n]s",stud.name);
            printf("GENDER::::::::::::::::::::> ");
            scanf(" %s",stud.gender);
            printf("COURSE::::::::::::::::::::> ");
            scanf(" %s",stud.course);
            printf("DOB (DD/MM/YYYY)::::::::::> ");
            scanf(" %s",stud.dob);
            printf("CITY::::::::::::::::::::::> ");
            scanf(" %s",stud.city);
            printf("MOBILE::::::::::::::::::::> ");
            scanf(" %s",stud.mobile);

            if(!strcmp(stud.city,"Mumbai") || !strcmp(stud.city,"mumbai") || !strcmp(stud.city,"Bombay") || !strcmp(stud.city,"bombay")) {
                stud.room_no = 100;
            } else {
                srand(time(NULL));
                stud.room_no = get_room((rand()%(upper - lower + 1))+ lower);
            }
        }

        if(stud.room_no != 0) {
            if(!strcmp(stud.gender,"Male") || !strcmp(stud.gender,"male") || !strcmp(stud.gender,"M")) {
                stud.hostel = 'A';
                fwrite(&stud,sizeof(struct student),1,fptr1);;
            } else if(!strcmp(stud.gender,"Female") || !strcmp(stud.gender,"female") || !strcmp(stud.gender,"F")) {
                stud.hostel = 'B';
                fwrite(&stud,sizeof(struct student),1,fptr1);
            } else {
                printf("Enter a valid gender\n\nRecord deleted due to one or more invalid inputs please register again");
            }
        }
    }
    fclose(fptr);
    fclose(fptr1);

    if(found == 0) {
        printf("\nStudent doesn't exist please register yourself");
        getchar();
        getchar();
        return;
    }

    if(found == 1) {
        fptr1 = fopen("temp.txt","r");
        fptr = fopen("details.txt","w");

        while(fread(&stud,sizeof(struct student),1,fptr1)) {
            fwrite(&stud,sizeof(struct student),1,fptr);
        }

        fclose(fptr);
        fclose(fptr1);
    }


    perror("\n\nError: ");
    printf("\n\nPress ENTER to continue");
    getchar();
    getchar();
    return;
}

void del_info () {
    char conf;
    struct student stud;

    FILE *fptr  = fopen("details.txt","r");
    FILE *fptr1 = fopen("temp.txt","w");
    int roll,found=0;

    //rollEnter:
    printf("Enter your roll number::::> ");
    scanf("%d",&roll);

    while(fread(&stud,sizeof(struct student),1,fptr)) {
        if(stud.roll == roll) {
            printf("\n::::::::::::::STORED INFORMATION::::::::::::::\n\n");
            printf("FULL NAME:::::::::::::::::> %s",stud.name);
            printf("\nROLL NUMBER:::::::::::::::> %d",stud.roll);
            printf("\nGENDER::::::::::::::::::::> %s",stud.gender);
            printf("\nCOURSE::::::::::::::::::::> %s",stud.course);
            printf("\nDOB (DD/MM/YYYY)::::::::::> %s",stud.dob);
            printf("\nCITY::::::::::::::::::::::> %s",stud.city);
            printf("\nMOBILE::::::::::::::::::::> %s",stud.mobile);

            if(stud.room_no != 0 && stud.room_no != 100) {
                printf("\nROOM ALLOTED::::::::::::::> %c-%d",stud.hostel,stud.room_no);
            } else {
                printf("\nROOM ALLOTED::::::::::::::> Not alloted");
            }

            printf("\n\nThe Above Stored record will be permantly deleted\n\n");
            printf("Do you wish to continue? (Y/N)::::::::> ");
            scanf(" %c",&conf);

            if(conf == 'y' || conf == 'Y') {
                found =  1;
            } else if(conf == 'n' || conf == 'N'){
                found =  100;
            } else {

            }
        } else {
            fwrite(&stud,sizeof(struct student),1,fptr1);
        }
    }
    
    fclose(fptr);
    fclose(fptr1);

    if(found == 0) {
        printf("\nStudent doesn't exist please register yourself");
        getchar();
        getchar();
        return;
    } else if(found == 1) {
        fptr1 = fopen("temp.txt","r");
        fptr = fopen("details.txt","w");

        while(fread(&stud,sizeof(struct student),1,fptr1)) {
            fwrite(&stud,sizeof(struct student),1,fptr);
        }

        fclose(fptr);
        fclose(fptr1);
    } else if(found == 100) {
        printf("\nRecord not deleted");
    } else {
        printf("\nInvalid input");
    }

    perror("\n\nError: ");
    printf("\n\nPress ENTER to continue");
    getchar();
    getchar();
    return;
}

/*
    ADMIN FUNCTIONS
*/

int no_of_rec() {
    struct student stud;

    FILE *fptr = fopen("details.txt","r");
    fseek(fptr,0,SEEK_END);
    int n = ftell(fptr)/sizeof(struct student);

    fclose(fptr);
    return n;
}

int check_roll(int roll) {
    int result;
    struct student stud;
    
    FILE *fptr = fopen("details.txt","r");

    while(fread(&stud,sizeof(struct student),1,fptr)) {
        if(roll == stud.roll) {
            result = 1;
        } else {
            result = 0;
        }
    }
    fclose(fptr);
    return result;
}

void clr_file() {
    FILE *fptr  = fopen("details.txt","w");
    FILE *fptr1 = fopen("temp.txt","w");
    fclose(fptr1);
    fclose(fptr);
}

int get_room(int room_no) {
    int allocated = 0;
    srand(time(0));

    FILE *fptr = fopen("details.txt","r");

    struct student s1;

    while(fread(&s1, sizeof(struct student), 1, fptr)) {
        if(s1.room_no == room_no) {
            allocated = 1;
        }
    }
    if(allocated == 0) {
        return room_no;
    } else {
        return get_room((rand()%(upper - lower + 1))+ lower);
    }
    fclose(fptr);
}