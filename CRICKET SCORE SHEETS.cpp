#include<stdio.h>
#include <string.h>
struct cricket
{
char name [100];
char team_name[100];
int b_or_c;
float battingavg;
float economy;
};
struct cricket player[200];
FILE *fp;
void insertplayers(){  //opt=1
        int n,i,count,t,s,totover,totgiven,over,gnrun;
        fp=fopen("score.txt","a");
        printf("HOW MANY PLAYERS:");
        scanf("%d",&n);
        for (i=0;i<n;i++)
        {
        printf("\n---------------------------------------------------------");
        printf("\n|\t\tENTER:\t\t\t\t\t|\n|\t\t[1]BATSMAN(Batting Average)\t\t|\n|\t\t[2]BOWLERS(Economy Rate)\t\t|");
        printf("\n---------------------------------------------------------");
        printf("\nWhat's your Preference?:");
        scanf("%d",&player[i].b_or_c);
        printf("\nINPUT THE NAME OF THE PLAYER %d:",i+1);
        fseek(stdin,0,SEEK_END);
        gets(player[i].name);
        printf("INPUT THE TEAM NAME OF THE PLAYER %d:",i+1);
        fseek(stdin,0,SEEK_END);
        gets(player[i].team_name);
        printf("INPUT THE NO OF MATCHES PLAYED BY THE PLAYER %d:",i+1);
        scanf("%d",&count);
        if(player[i].b_or_c==1){
        printf("\n--------------------------------------");
        printf("\nTo Find BATTING AVERAGE for %d Matches|",count);
        printf("\n--------------------------------------");
        printf("\nENTER THE BATTING SCORES FOR %d MATCHES:",count);
        s=0;
        for(int j=0;j<count;j++){
            scanf("%d",&t);
            s+=t;
        }
        player[i].battingavg=s/count;
        player[i].economy=0;
        }
        else if(player[i].b_or_c==2){
        totover=0;
        totgiven=0;
        for(int j=0;j<count;j++){
        printf("\n-----------------------------------");
        printf("\nTo Find ECONOMY RATE for %d Matches|",count);
        printf("\n-----------------------------------");
        printf("\nENTER THE NO OF OVERS BOWLED FOR %d th MATCH:",j+1);
        scanf("%d",&over);
        totover+=over;
        printf("ENTER THE NO OF RUNS GIVEN FOR %d th MATCH:",j+1);
        scanf("%d",&gnrun);
        totgiven+=gnrun;
        }
        player[i].economy=totgiven/totover;
        player[i].battingavg=0;
        }
        fwrite(&player[i],sizeof(player[i]),1,fp);
        }

        fclose(fp);

}
void displayall(){   //opt=2
        int i,n;
        fp=fopen("score.txt","r");
        struct cricket p;
        printf("\n=========================================================================================================\n");
        printf(" \tPLAYER'S NAME\t\tTEAM NAME\t\tBATTING AVERAGE\t\tECONOMY\n");
        printf("=========================================================================================================\n");
        while(fread(&p,sizeof(p),1,fp)){
        printf("\t%7s\t%22s\t\t\t     %.2f\t\t %.2f\n",p.name, p.team_name,p.battingavg,p.economy);
        printf("=========================================================================================================\n");
        }
        fclose(fp);
}
void searchteam(){   //opt=3
        int i,n;
        int found=0;
        char team[100];
        struct cricket p;
        fp = fopen("score.txt","r");
        printf("\nINPUT FOR WHICH TEAM YOU WANT TO LIST:");
        fseek(stdin,0,SEEK_END);
        gets(team);
        printf("\n=========================================================================================================\n");
        printf(" \tPLAYER'S NAME\t\tTEAM NAME\t\tBATTING AVERAGE\t\tECONOMY\n");
        printf("=========================================================================================================\n");
        while(fread(&p,sizeof(p),1,fp)){  
        if(strcmp(p.team_name,team)==0){
        found=1;
        printf("\t%7s\t%22s\t\t\t     %.2f\t\t %.2f\n",p.name, p.team_name,p.battingavg,p.economy);
        printf("=========================================================================================================\n");
        }
        }
        if(!found){
        	printf("\t\t\t\t\t  Team Name not found!");
        }
        fclose(fp);
}
void searchname(){   //opt=4
        int i,n;
        int found=0;
        char name[100];
        struct cricket p;
        fp = fopen("score.txt","r");
        printf("\nINPUT FOR WHICH PLAYER NAME YOU WANT TO LIST:");
        fseek(stdin,0,SEEK_END);
        gets(name);
        printf("\n=========================================================================================================\n");
        printf(" \tPLAYER'S NAME\t\tTEAM NAME\t\tBATTING AVERAGE\t\tECONOMY\n");
        printf("=========================================================================================================\n");
        while(fread(&p,sizeof(p),1,fp)){
        if(strcmp(p.name,name)==0){
        found=1;
        printf("\t%7s\t%22s\t\t\t     %.2f\t\t %.2f\n",p.name, p.team_name,p.battingavg,p.economy);
        printf("=========================================================================================================\n");
        }
        }
        if(!found){
        	printf("\t\t\t\t\t  Name not found!");
        }
        fclose(fp);
}
void update_player(){   //opt=5
        FILE *fp1;
        int n,i,count,t,s,totover,totgiven,over,gnrun;
        int found=0;
        char name[100];
        struct cricket p;
        printf("\nENTER THE NAME OF THE PLAYER TO UPDATE:");
        fflush(stdin);
        gets(name);
        fp = fopen("score.txt","r");
        fp1=fopen("temp.txt","w");
        while(fread(&p,sizeof(p),1,fp)){
        if(strcmp(p.name,name)!=0){
            fwrite(&p,sizeof(p),1,fp1);
        }
        else if(strcmp(p.name,name)==0){
            found=1;
        }
        }
        if(!found){
            printf("NAME NOT FOUND");
            fclose(fp);
            fclose(fp1);
            remove("score.txt");
            rename("temp.txt","score.txt");
            return;
        }
        fclose(fp);
        fclose(fp1);
        remove("score.txt");
        rename("temp.txt","score.txt");
        printf("\nENTER THE DETAILS TO UPDATE:");
        fp=fopen("score.txt","a");
        printf("\nINPUT THE NAME OF THE PLAYER : ");
        fseek(stdin,0,SEEK_END);
        gets(p.name);
        printf("INPUT THE TEAM NAME OF THE PLAYER:");
        fseek(stdin,0,SEEK_END);
        gets(p.team_name);
        printf("\n---------------------------------------------------------");
        printf("\n|\t\tENTER:\t\t\t\t\t|\n|\t\t[1]BATSMAN(Batting Average)\t\t|\n|\t\t[2]BOWLERS(Economy Rate)\t\t|");
        printf("\n---------------------------------------------------------");
        printf("\nWhat's your Preference?:");
        scanf("%d",&p.b_or_c);
        printf("\nINPUT THE NO OF MATCHES PLAYED BY THE PLAYER:");
        scanf("%d",&count);
        if(p.b_or_c==1){
        printf("\n--------------------------------------");
        printf("\nTo Find BATTING AVERAGE for %d Matches|",count);
        printf("\n--------------------------------------");
        printf("\nENTER THE BATTING SCORES FOR %d MATCHES :",count);
        s=0;
        for(int j=0;j<count;j++){
            scanf("%d",&t);
            s+=t;
        }
        p.battingavg=s/count;
        p.economy=0;
        }
        else if(p.b_or_c==2){
        totover=0;
        totgiven=0;
        for(int j=0;j<count;j++){
        printf("\n-----------------------------------");
        printf("\nTo Find ECONOMY RATE for %d Matches|",count);
        printf("\n-----------------------------------");
        printf("\nENTER THE NO OF OVERS BOWLED FOR %d th MATCH:",j+1);
        scanf("%d",&over);
        totover+=over;
        printf("ENTER THE NO OF RUNS GIVEN FOR %d th MATCH:",j+1);
        scanf("%d",&gnrun);
        totgiven+=gnrun;
        }
        p.economy=totgiven/totover;
        p.battingavg=0;
        }
        printf("\n>>>UPDATED SUCCESSFULLY<<<");
        fwrite(&p,sizeof(p),1,fp);
        fclose(fp);
}
void delete_player(){   //opt=6
        FILE *fp1;
        int found=0;
        char name[100];
        struct cricket p;
        printf("\nENTER THE NAME OF THE PLAYER TO BE DELETED:");
        fflush(stdin);
        gets(name);
        fp = fopen("score.txt","r");
        fp1=fopen("temp.txt","w");
        while(fread(&p,sizeof(p),1,fp)){
        if(strcmp(p.name,name)!=0){
            fwrite(&p,sizeof(p),1,fp1);
        }
        else if(strcmp(p.name,name)==0){
            found=1;
            printf("SUCCESSFULLY DELETED!");
        }
        }
        if(!found){
            printf("NAME NOT FOUND!");
        }
        fclose(fp);
        fclose(fp1);
        remove("score.txt");
        rename("temp.txt","score.txt");
}
int main()
{
int i,n,opt;
while(opt!=7){
printf("\n\t\t\t<<<<<<<<<<<<<<<<<<CRICKET SCORE SHEET>>>>>>>>>>>>>>>>>>>>");
printf("\n\t\t\t|\t\t[1]Enter Player Details          \t|\n\t\t\t|\t\t[2]Display Player Details        \t|\n\t\t\t|\t\t[3]Search Player details(By Team)\t|");
printf("\n\t\t\t|\t\t[4]Search Player details(By Name)\t|\n\t\t\t|\t\t[5]Edit Player Details\t\t\t|\n\t\t\t|\t\t[6]Delete Player Details\t\t|\n\t\t\t|\t\t[7]EXIT\t\t\t\t\t|");
printf("\n\t\t\t---------------------------------------------------------");
printf("\n\nEnter Your Choice: ");
scanf("%d",&opt);
switch(opt){
    case 1:{
        insertplayers();
        break;
    }
    case 2:{
        displayall();
        break;
    }
    case 3:{
        searchteam();
        break;
    }
    case 4:{
        searchname();
        break;
    }
    case 5:{
        update_player();
        break;
    }
    case 6:{
        delete_player();
        break;
    }
    case 7:
        printf("\n<<<<<<<<<<<<<<<<<<THANK YOU:)>>>>>>>>>>>>>>>>>>>>");
        break;
    default: printf(">>>Invalid Choice!Try Again!<<<"); break;
}
}
return 0;
}
