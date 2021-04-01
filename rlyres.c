#include<stdio.h>
#include"conio2.h"
#include"rlyres.h"
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdio.h>
int enterchoice()
{
    int choice;
    textcolor(BLUE);
    gotoxy(27,1);
    printf("RAILWAY RESERVATION SYSTEM(By Aniket Sinha)");
    gotoxy(1,2);
    for(int i=1;i<80;i++)
        printf("-");
    textcolor(GREEN);
    gotoxy(1,4);
    for(int i=1;i<80;i++)
        printf("-");
    for(int i=0;i<=80;i++)
        printf("-");
    gotoxy(30,6);
    printf("Select an option :-");
    gotoxy(32,7);
    printf("1.  View Trains");
    gotoxy(32,8);
    printf("2.  Book Ticket");
    gotoxy(32,9);
    printf("3.  View Ticket");
    gotoxy(32,10);
    printf("4.  Search Ticket no");
    gotoxy(32,11);
    printf("5.  View All Bookings");
    gotoxy(32,12);
    printf("6.  View Train Bookings");
    gotoxy(32,13);
    printf("7.  Cancel Ticket");
    gotoxy(32,14);
    printf("8.  Cancel Train");
    gotoxy(32,15);
    printf("9.  Quit");
    gotoxy(32,17);
    printf("Enter Your Choice: ");
    gotoxy(1,19);
    for(int i=1;i<=80;i++)
        printf("-");
    for(int i=1;i<=80;i++)
        printf("-");
    gotoxy(52,17);
    scanf("%d",&choice);
    gotoxy(1,23);
    return choice;
}

void add_trains()
{
    Train alltrains[4]={
    {"123","BPL","GWA",2100,1500},
    {"546","BPL","DEL",3500,2240},
    {"345","HBJ","AGR",1560,1135},
    {"896","HBJ","MUM",4500,3360}
    };
   FILE *fp=fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\alltrains.dat","rb");
   if(fp==NULL)
   {
      fp=fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\alltrains.dat","wb");
      fwrite(alltrains,4*sizeof(Train),1,fp);
      printf("File created and saved!\n");

   }
   else
   {
       printf("File already present");
   }
   fclose(fp);
}
void view_trains()
{
  Train tr;
  printf("TRAIN NO\tFROM\tTO\tFIRST AC FARES\tSECOND AC FARES\n");
  for(int i=1;i<=80;i++)
    printf("-");
  FILE *fp=fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\alltrains.dat","rb");
 while(fread(&tr,sizeof(tr),1,fp)==1)
 {
     printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
 }
 printf("\n\n");
 fclose(fp);
}
int check_train_no(char *t)
{
    FILE *fp=fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,t)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            return 0;
        p_mob++;
    }
    return 1;
}

Passenger *get_passenger_details()
{
    clrscr();
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    static Passenger psn;
    printf("Enter passenger name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    char *pos;
    pos=strchr(psn.p_name,'\n');
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    int valid;
    printf("Enter gender(M/F):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.gender!='M'&&psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Error! Gender should be M or F(in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(19,2);
            textcolor(YELLOW);
        }

    }while(valid==0);
  gotoxy(1,25);
  printf("\t\t\t\t\t\t\t\t");
  gotoxy(1,3);
  printf("Enter train number:");
  do
  {
      fflush(stdin);
      scanf("%s",psn.train_no);
      if(strcmp(psn.train_no,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    valid=check_train_no(psn.train_no);
     if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Error! Invalid Train no.");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(20,3);
            textcolor(YELLOW);
        }
    }while(valid==0);
  gotoxy(1,25);
  printf("\t\t\t\t\t\t\t\t");
  gotoxy(1,4);
  printf("Enter travelling class(First AC:F,Second AC:S):");
   do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.p_class!='F'&&psn.p_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Error!Travelling class should be F or S ");
            valid=0;
            getch();
            gotoxy(48,4);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(48,4);
            textcolor(YELLOW);
        }

    }while(valid==0);
     gotoxy(1,25);
  printf("\t\t\t\t\t\t\t\t");
  gotoxy(1,5);
  printf("Enter address:");
  fflush(stdin);
  fgets(psn.address,50,stdin);
  if(strcmp(psn.address,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("\t\t\t\t\t\t\t\t");
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
    }
    printf("Enter age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.age<0||psn.age>126)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Error!Age Should be positive and valid");
            valid=0;
            getch();
            gotoxy(11,6);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(11,6);
            textcolor(YELLOW);
        }

    }while(valid==0);
   gotoxy(1,25);
   printf("\t\t\t\t\t\t\t\t");
   gotoxy(1,7);
   printf("Enter mobile number:");
   do
   {
       fflush(stdin);
       fgets(psn.mob_no,12,stdin);
       pos=strchr(psn.mob_no,'\n');
       if(pos!=NULL)
        *pos='\0';
       if(strcmp(psn.mob_no,"0")==0)
       {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled");
        getch();
        textcolor(YELLOW);
        clrscr();
        return NULL;
       }
      valid=check_mob_no(psn.mob_no);
      if(valid==0)
      {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(1,25);
          printf("Error! Invalid Mobile no.");
          getch();
          gotoxy(21,7);
          printf("\t\t\t\t\t\t\t\t");
          gotoxy(21,7);
          textcolor(YELLOW);
      }


   }while(valid==0);
   return &psn;
}

int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp=fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    int count=0;
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0&&pr.p_class==tc)
          ++count;
    }
    fclose(fp);
    return count;
}
int last_ticket_no()
{
    FILE *fp=fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","rb");
    Passenger pr;
    if(fp==NULL)
        return 0;
    fseek(fp,-1L*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}

int book_ticket(Passenger p)
{
    int ticket_count;
    ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no. %s in %c class!",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no();
    p.ticketno=ticket_no+1;
    FILE *fp=fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return p.ticketno;
}
int accept_ticket_no(){
    printf("Enter a valid ticket number : ");
    int valid;
    int ticket_no;
    do{
        valid = 1;
        scanf("%d",&ticket_no);
        if(ticket_no==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("CANCELLING INPUT!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(ticket_no<0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, ticket no. should be positive");
            valid = 0;
            getch();
            gotoxy(31,1);
            printf("\t\t\t\t\t\t");
            gotoxy(31,2);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return ticket_no;
}

void view_ticket(int ticket_no){
    FILE*fptr;
    fptr = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTGREEN);
        printf("ERROR!, file not found!");
        return;
    }
    Passenger psn;
    int found = 0;
    while(fread(&psn,sizeof(psn),1,fptr) == 1){
        if(psn.ticketno==ticket_no){
            printf("\nNAME : %s\nGENDER : %c\nTRAIN NO. : %s\nCLASS : %c\nADDRESS : %s\nAGE : %d\nMOBILE NO : %s\nTICKET NO. : %d\n\n",psn.p_name,psn.gender,psn.train_no,psn.p_class,psn.address,psn.age,psn.mob_no,psn.ticketno);
            found = 1;
            break;
        }
    }
    if(found==0){
        textcolor(LIGHTRED);
        printf("NOT FOUND!, no result found for ticket no : %d\n",ticket_no);
    }
    fclose(fptr);

}

char*accept_mob_no(){
    static char mob_no[12];
    int valid;
    char*pos;
    printf("Enter your mobile no. : ");
    do{
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos = strchr(mob_no,'\n');
        if(pos!=NULL){
            *pos = '\0';
        }
        if(strcmp(mob_no,"0")==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("CANCELLING INPUT!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid = check_mob_no(mob_no);
        if(valid==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, Invalid mobile no.");
            getch();
            gotoxy(25,1);
            printf("\t\t\t\t\t\t");
            gotoxy(25,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}

int*get_ticket_no(char*mob_no){
    FILE*fptr;
    fptr = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTRED);
        printf("ERROR!, file not found!");
        return NULL;
    }
    Passenger psn;
    int count = 0;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
        if(strcmp(psn.mob_no,mob_no)==0){
            count++;
        }
    }
    if(!count){
        fclose(fptr);
        return NULL;
    }
    int*p=(int*)malloc((count+1)*sizeof(int));
    rewind(fptr);
    int i=0;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
        if(strcmp(psn.mob_no,mob_no)==0){
            *(p+i) = psn.ticketno;
            i++;
        }
    }
    *(p+1)=-1;
    fclose(fptr);
    return p;
}

void view_all_tickets(char*mob_no,int*tno){
    if(tno == NULL){
        textcolor(LIGHTRED);
        printf("No tickets found for Mobile no. : %s\n",mob_no);
        textcolor(WHITE);
        printf("Press any key to go back");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following tickets are booked for Mobile no. : %s\n",mob_no);
    int i = 0;
    printf("\n\nTICKET NUMBER:\n\n");
    for(int j=0;j<80;j++)
        printf("-");
    while(*(tno+i)!=-1){
        printf("%d\n",*(tno+i));
        i++;
    }
    textcolor(WHITE);
    printf("\nPress any key to exit...");
    textcolor(YELLOW);
    getch();
    free(tno);
}

char*accept_train_no(){
    static char train_no[5];
    int valid;
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train no : ");
    do{
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("CANCELLING INPUT!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid = check_train_no(train_no);
        if(valid==0){
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("ERROR!, Invalid Train Number");
            getch();
            gotoxy(18,1);
            printf("\t\t\t\t\t\t");
            gotoxy(18,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}

void view_bookings(char*train_no){
    FILE*fptr;
    fptr = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTRED);
        printf("ERROR!, file not found!");
        return;
    }
    Passenger psn;
    int found=0;
    printf("TICKET NO.\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO.\n");
    for(int i=0;i<80;i++)
        printf("-");
    int row = 3;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
        if(strcmp(train_no,psn.train_no)==0){
            printf("%d\t\t%c\t%s",psn.ticketno,psn.p_class,psn.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",psn.gender,psn.age,psn.mob_no);
            row++;
            found = 1;
        }
    }
    if(!found){
        textcolor(LIGHTRED);
        printf("No bookings found for train no. : %s",train_no);
    }
    textcolor(WHITE);
    printf("\nPress any key to exit.....");
    getch();
    fclose(fptr);
}

void view_all_bookings()
{
   FILE*fptr;
    fptr = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","rb");
    if(fptr == NULL){
        textcolor(LIGHTRED);
        printf("ERROR!, file not found!");
        return;
    }
    Passenger psn;
    printf("TICKET NO.\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO.\n");
    for(int i=0;i<80;i++)
        printf("-");
    int row = 3;
    while(fread(&psn,sizeof(psn),1,fptr)==1){
            printf("%d\t\t%c\t%s",psn.ticketno,psn.p_class,psn.p_name);
            gotoxy(41,row);
            printf("%c\t%d\t%s\n",psn.gender,psn.age,psn.mob_no);
            row++;
    }

    textcolor(WHITE);
    printf("\nPress any key to exit.....");
    getch();
    fclose(fptr);

}

int cancel_ticket(int ticket_no){
    int result;
    FILE*fptr1 = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat","rb");
    if(fptr1 == NULL){
        textcolor(LIGHTRED);
        printf("File not found!");
        return -1;
    }
    FILE*fptr2 = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\temp.dat","wb");
    Passenger psn;
    int found=0;
    while(fread(&psn,sizeof(psn),1,fptr1)==1){
        if(psn.ticketno==ticket_no){
            found = 1;
        }
        else{
            fwrite(&psn,sizeof(psn),1,fptr2);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    if(found==0){
        remove("D:\\Aniket\\Cproject\\Myprojectfiles\\temp.dat");
    }
    else{
        result = remove("D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat");
        if(result!=0)
            return 2;
        result = rename("D:\\Aniket\\Cproject\\Myprojectfiles\\temp.dat", "D:\\Aniket\\Cproject\\Myprojectfiles\\allbookings.dat");
        if(result!=0){
        return 2;
        }
    }
    return found;
}
int cancel_train(char*train_no){
    int result;
    FILE*fptr1 = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\alltrains.dat","rb");
    if(fptr1 == NULL){
        textcolor(LIGHTRED);
        printf("File not found!");
        return -1;
    }
    FILE*fptr2 = fopen("D:\\Aniket\\Cproject\\Myprojectfiles\\temptrain.dat","wb");
    Train trn;
    int found=0;
    while(fread(&trn,sizeof(trn),1,fptr1)==1){
        if(strcmp(trn.train_no,train_no)==0){
            found = 1;
        }
        else{
            fwrite(&trn,sizeof(trn),1,fptr2);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    if(found==0){
        remove("D:\\Aniket\\Cproject\\Myprojectfiles\\temptrain.dat");
    }
    else{
        result = remove("D:\\Aniket\\Cproject\\Myprojectfiles\\alltrains.dat");
        if(result!=0)
            return 2;
        result = rename("D:\\Aniket\\Cproject\\Myprojectfiles\\temptrain.dat", "D:\\Aniket\\Cproject\\Myprojectfiles\\alltrains.dat");
        if(result!=0){
        return 2;
        }
    }
    return found;
}
