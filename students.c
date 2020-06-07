#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include <time.h>
#include"structs.c"
#define S_STRING_SIZE 256 //����� ������ �����
#define S_CASE_SIZE 64 //����� ������ �����
#define S_MASSIVE_SIZE 4096 // ������ ������� ��������

int ViewStudents(Anketa*Base, int size){
        printf("�������:\n");
        printf("________________________________________________________________________________________\n");
        printf("����� �������� ������|    �������    |    ���   |    ��������   |���������|�������������|\n");
        for(int i=0;i<size;i++){            
               if((strcmp(Base[i].RecBook, "del"))!=0){
                printf("________________________________________________________________________________________\n");
                printf("%21s|", Base[i].RecBook);
                printf("%15s|", Base[i].Surname);
                printf("%10s|", Base[i].Name);
                printf("%15s|", Base[i].Patron);
                printf("%9s|", Base[i].Faculty);
                printf("%13s|\n", Base[i].Spec);
            }
        }
        printf("________________________________________________________________________________________\n");
}

void WriteStudents(Anketa*Base, int size,char filename[S_CASE_SIZE]){
    FILE *Basefile=fopen(filename, "r");
    char Basket[S_STRING_SIZE];
    for(int i=0;i<size;i++){
        fgets(Basket, S_STRING_SIZE, Basefile);
        strcpy(Base[i].RecBook,strtok(Basket,";"));
        strcpy(Base[i].Surname,strtok(NULL,";"));
        strcpy(Base[i].Name,strtok(NULL,";"));
        strcpy(Base[i].Patron,strtok(NULL,";"));
        strcpy(Base[i].Faculty, strtok(NULL,";"));
        strcpy(Base[i].Spec, strtok(NULL,"\n"));
    }
    fclose(Basefile);
}

int AddStudent(Anketa*Base, int NumberLine){
        printf("���������� ��������\n����� �������� ������:");
        char RecBook[S_CASE_SIZE];
        SetConsoleCP(1251);
        scanf("%s",&RecBook);
        SetConsoleCP(866);
        if(!strcmp(RecBook,"Q")){
            return 1;
        }
        int copy=0; // ��������� ����� ������� �� ����������
        for(int i=0; i<NumberLine; i++) {// �������� ���� ���� �� ����� ������� � ����
            if(!strcmp(RecBook, Base[i].RecBook)){
                printf("������� ��� ���� � ����.\n");
                copy=1;
                return 1;
            }
        }
        if(copy==0){
            char Surname[S_CASE_SIZE];
            printf("�������:");
            SetConsoleCP(1251);
            scanf("%s",&Surname);
            SetConsoleCP(866);
            if((strcmp(Surname,"Q"))==0){
                return 1;
            }
            char Name[S_CASE_SIZE];
            printf("���:");
            SetConsoleCP(1251);
            scanf("%s",&Name);
            SetConsoleCP(866);
            if((strcmp(Name,"Q"))==0){
                return 1;
            }
            char Patron[S_CASE_SIZE];
            printf("��������:");
            SetConsoleCP(1251);
            scanf("%s",&Patron);
            SetConsoleCP(866);
            if((strcmp(Patron,"Q"))==0){
                return 1;
            }
            char Faculty[S_CASE_SIZE];
            printf("���������:");
            SetConsoleCP(1251);
            scanf("%s",&Faculty);
            SetConsoleCP(866);
            if((strcmp(Faculty,"Q"))==0){
                return 1;
            }
            char Spec[S_CASE_SIZE];
            printf("�������������:");
            SetConsoleCP(1251);
            scanf("%s",&Spec);
            SetConsoleCP(866);
            if((strcmp(Spec,"Q"))==0){
                return 1;
            }
            strcpy(Base[NumberLine].RecBook,RecBook);
            strcpy(Base[NumberLine].Surname,Surname);
            strcpy(Base[NumberLine].Name,Name);
            strcpy(Base[NumberLine].Patron,Patron);
            strcpy(Base[NumberLine].Faculty,Faculty);
            strcpy(Base[NumberLine].Spec,Spec);
            printf("������� ��������\n");
            ViewStudents(Base, NumberLine+1);
            return 0;
        }
}

void DeleteStudent(Anketa*Base, int NumberLine){
                int del=0;//������������� ���������� ��������
                printf("�������� ��������\n");
                printf("������� ����� �������� ������:");
                char RecBook[S_CASE_SIZE];
                SetConsoleCP(1251);
                scanf("%s",&RecBook);
                SetConsoleCP(866);
                if((strcmp(RecBook,"Q"))==0){
                    return;
                }
                for(int p=0; p<NumberLine; p++){
                    if(strcmp(Base[p].RecBook, RecBook)==0){
                        strcpy(Base[p].RecBook,"del");
                        del=1;
                        printf("������� ������\n");
                        ViewStudents(Base, NumberLine);
                        break;
                    }
                }
                if(del==0){
                    printf("������� �� ������\n");
                }
}


void CreateBackUp(Anketa*Base, int NumberLine)
{
    printf("�������� ������\n");    
    char date[S_STRING_SIZE];//������ ��� �������� ����
    long int s_time = time(NULL);
    struct tm *m_time = localtime(&s_time);
    strftime(date, S_STRING_SIZE, "%m_%d_(%H.%M)_%Y_", m_time);
    
    char filename[S_STRING_SIZE];//������ ��� �������� �������� ���-�� �����
    sprintf(filename, "students_%s.csv", date);
    
    FILE* Backup = fopen(filename, "w");
    if(Backup == NULL){
        printf("�� ������� ������� ���-�� ���� %s\n", filename);
        return;
    }
     for (int i = 0; i < NumberLine; i++)
    {
       fprintf(Backup,"%s;%s;%s;%s;%s;%s\n",Base[i].RecBook,Base[i].Surname,Base[i].Name,Base[i].Patron,Base[i].Faculty,Base[i].Spec);
    }
    printf("���-�� ���� ������� ������ %s\n", filename);

    fclose(Backup);
}


int CopyBackUp(Anketa*Base, int NumberLine){
    backdate date;// ��������� ���� 
    char fname[S_STRING_SIZE]="students_";// �������� ���-���
    printf("�������������� �� ������\n");
    printf("������� ���� � �����\n");
    printf(" �����:");
    scanf("%s",&date.month);
    if(!strcmp("Q",date.month)){
        return 0;
    }
    printf(" �����:");
    scanf("%s",&date.number);
    if(!strcmp("Q",date.number)){
        return 0;
    }
    printf(" ���:");
    scanf("%s",&date.hour);
    if(!strcmp("Q",date.hour)){
        return 0;
    }
    printf(" ������:");
    scanf("%s",&date.minute);
    if(!strcmp("Q",date.minute)){
        return 0;
    }
    printf(" ���:");
    scanf("%s",&date.year);
    if(!strcmp("Q",date.year)){
        return 0;
    }
    strcat(fname,date.month);
    strcat(fname,"_");
    strcat(fname,date.number);
    strcat(fname,"_(");
    strcat(fname,date.hour);
    strcat(fname,".");
    strcat(fname,date.minute);
    strcat(fname,")_");
    strcat(fname,date.year);
    strcat(fname,"_");
    strcat(fname,".csv");
    printf("%s",fname);

    FILE *Backupfile=fopen(fname, "r");
    if(Backupfile==NULL){
        printf(" - ���� �� ������.\n");
    }else{
        printf(" - ���� ������� ������\n");
        int BNumberLine=0;// ���������� ����� � ���-���
        while(!feof(Backupfile)){  //������� ���������� �����
            if((fgetc(Backupfile))=='\n'){
                BNumberLine++;
            }
        }
        fclose(Backupfile);
        printf("���������� ����� � ����� ������: %d\n",BNumberLine);
        Anketa *BackBase;             //������ ������ ���-���
        BackBase=calloc(S_MASSIVE_SIZE,sizeof(Anketa));
        WriteStudents(BackBase,BNumberLine,fname); //���������� ������ ����� ������ � BackBase

        if(BNumberLine>0){ 
            printf("������� � ����� ������:\n");
            ViewStudents(BackBase,BNumberLine);
        }
        for(int i=0; i<BNumberLine;i++){
            strcpy(Base[i].RecBook,BackBase[i].RecBook);
            strcpy(Base[i].Surname,BackBase[i].Surname);
            strcpy(Base[i].Name,BackBase[i].Name);
            strcpy(Base[i].Patron,BackBase[i].Patron);
            strcpy(Base[i].Faculty,BackBase[i].Faculty);
            strcpy(Base[i].Spec,BackBase[i].Spec);
        }
        if(BNumberLine<NumberLine){
            for(int i=BNumberLine;i<NumberLine;i++){
                strcpy(Base[i].RecBook,"del");
            }
        }
    }
}




void SearchStudent(Anketa*Base,int NumberLine){
                printf("����� ���������� �� �������\n������� �������:");
                char Surname[S_CASE_SIZE];
                SetConsoleCP(1251);
                scanf("%s",&Surname);
                SetConsoleCP(866);
                int found=0;//���������� �� ������� � ����� ��������
                int d=0;//����� ����� ������
                if(!strcmp(Surname,"Q")){
                    return;
                }
                for(int m=0;m<NumberLine;m++){
                    if(!strcmp(Base[m].Surname, Surname)){
                        if(d==0){printf("________________________________________________________________________________________\n");
                        printf("����� �������� ������|    �������    |    ���   |    ��������   |���������|�������������|\n");
                        printf("________________________________________________________________________________________\n");
                        }
                        d=1;
                        printf("%21s|%15s|%10s|%15s|%9s|%13s|\n",Base[m].RecBook,Base[m].Surname,Base[m].Name,Base[m].Patron,Base[m].Faculty,Base[m].Spec);
                        printf("________________________________________________________________________________________\n");
                        found=1;
                    }
                }
                if(!found){
                    printf("������� � ����� �������� �� ������\n");
                }
}

void ExitStudents(Anketa*Base, int NumberLine){
    FILE *Basefile=fopen("students.csv", "w");
    for(int i=0;i<NumberLine;i++){
        if((strcmp(Base[i].RecBook, "del"))!=0){
            fprintf(Basefile,"%s;%s;%s;%s;%s;%s\n",Base[i].RecBook,Base[i].Surname,Base[i].Name,Base[i].Patron,Base[i].Faculty,Base[i].Spec);
        }
    }
    printf("���� ��������\n");
    fclose(Basefile);
    free(Base);
}




void students(){
        setlocale(LC_ALL,"Russian");
    unsigned int NumberLineStud=0;//���������� ����
	FILE *StudFile=fopen("students.csv", "r");
	if(StudFile==NULL){
        printf("���� �� ������.");
    }else{
        printf("���� ��������\n");
        while(!feof(StudFile)){  //������� ���������� �����
            if((fgetc(StudFile))=='\n'){
                NumberLineStud++;
            }
        }
        printf("���������� �����: %d\n",NumberLineStud);
        fclose(StudFile);
        Anketa*BaseStud;             //������ ���������
        BaseStud=calloc(S_MASSIVE_SIZE,sizeof(Anketa));
        char filename[S_CASE_SIZE]="students.csv";
        WriteStudents(BaseStud, NumberLineStud,filename); //��������� ������ ����� � BaseStud 
        if(NumberLineStud>0){ //������� �������, ���� ��� �� ������
            ViewStudents(BaseStud,NumberLineStud);
        }
        printf("�������� ��������:(������ ��� �������)\n");
		printf("1 - ����� �������� ������ ��������\n2 - ����� ������� ��������\n5 - ����� ������� ���-��\n6 - ����� ��������� ���-��\n7 - ����� ����� ���������� � �������� �� ��� �������\n8 - ����� ����� � ����������� ���������\nQ - ����� ��������� � ���������� ���� (�������� �� ���� ����������)\n");
        
         char StudButton[4]; // ������� ������������
        strcpy(StudButton,"0");
		while(!strcmp(StudButton,"0")){ //������� ����
            printf("students:");
            SetConsoleCP(1251);
            scanf("%s",&StudButton);
            SetConsoleCP(866);
            printf("%s- ",StudButton);

            if((strcmp(StudButton,"0")) && (strcmp(StudButton,"1")) && (strcmp(StudButton,"2")) && (strcmp(StudButton,"5")) && (strcmp(StudButton,"6")) && (strcmp(StudButton,"7")) && (strcmp(StudButton,"8")) && (strcmp(StudButton,"Q"))){
                printf("������������ �������\n");
                strcpy(StudButton,"0");
            }
// ���������:
            if(!strcmp(StudButton,"Q")){
                printf("������� � ������� ����\n");
                return;
            }
            if (!strcmp(StudButton,"1")){    //���������� ��������
                if(AddStudent(BaseStud,NumberLineStud)!=1){
                NumberLineStud++;
                }
                strcpy(StudButton,"0");
            }
           if(!strcmp(StudButton,"2")){ //�������� ��������
                DeleteStudent(BaseStud, NumberLineStud);
                strcpy(StudButton,"0");
            }

            if(!strcmp(StudButton,"5")){ //������� �����
                CreateBackUp(BaseStud,NumberLineStud);
                strcpy(StudButton,"0");
            }
            if(!strcmp(StudButton,"6")){ //��������� �����
                CopyBackUp(BaseStud, NumberLineStud);
                strcpy(StudButton,"0");
            }
            if(!strcmp(StudButton,"7")){  //����� ����������
                SearchStudent(BaseStud,NumberLineStud);
                strcpy(StudButton,"0");
            }
            if (!strcmp(StudButton,"8")){	//����� �� ��������� � ����������� ���������
                ExitStudents(BaseStud, NumberLineStud);
                return;
            }
        }
    }
}    