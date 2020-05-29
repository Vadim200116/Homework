#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include <time.h>
#include"structs.c"
#define S_STRING_SIZE 256
#define S_CASE_SIZE 64
#define S_MASSIVE_SIZE 4096

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
        printf("����� ��������� ������� 8\n");
}

void WriteStudents(Anketa*Base, int size, char filename[S_CASE_SIZE]){
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
        if((strcmp(RecBook,"Q"))==0){
            return 1;
        }
        int copy=0;
        for(int i=0; i<NumberLine; i++) {// �������� ���� ���� �� ����� ������� � ����
            if(strcmp(RecBook, Base[i].RecBook)==0){
                printf("������� ��� ���� � ����.\n");
                copy=1;
                return 1;
            }
        }
        if(copy==1){ //���� ���� �� ������������ � ������� ����
            return 1;
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
                int del=0;
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

void SearchStudent(Anketa*Base,int NumberLine){
                printf("����� ���������� �� �������\n������� �������:");
                char Surname[S_CASE_SIZE];
                SetConsoleCP(1251);
                scanf("%s",&Surname);
                SetConsoleCP(866);
                int found=0;
                int d=0;
                if((strcmp(Surname,"Q"))==0){
                    return;
                }
                for(int m=0;m<NumberLine;m++){
                    if((strcmp(Base[m].Surname, Surname))==0){
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
                if(found==0){
                    printf("������� � ����� �������� �� ������\n");
                }
}

void ExitStudents(Anketa*Base, int NumberLine){
    FILE *Basefile=fopen("students.csv", "w"); // ��������� ���� ��� ������(��� ���� ��� ������ ���������)
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
    int NumberLineStud=0;
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
        Anketa*BaseStud;             //������� ������ BaseStud
        BaseStud=calloc(S_MASSIVE_SIZE,sizeof(Anketa));
        char filename[S_CASE_SIZE]="students.csv";
        WriteStudents(BaseStud, NumberLineStud, filename); //���������� ������ ����� � BaseStud (�� ��������� � ����� structanketa.h
        if(NumberLineStud>0){ //������� �������, ���� ��� �� ������
            ViewStudents(BaseStud,NumberLineStud);
        }
        printf("�������� ��������:(������ ������� �������)\n");
		printf("1 - ����� �������� ������ ��������\n2 - ����� ������� ��������\n5 - ����� ������� �����\n6 - ����� ��������� �����\n7 - ����� ����� ���������� � �������� �� ��� ������\n8 - ����� ����� � ����������� ���������\nQ - ����� ��������� � ���������� ���� (�������� �� ���� ����������)\n");
        
         char StudButton[4];
        strcpy(StudButton,"0");
		while((strcmp(StudButton,"0"))==0){ //������� ����
            printf("students:");
            SetConsoleCP(1251);
            scanf("%s",&StudButton);
            SetConsoleCP(866);
            printf("%s- ",StudButton);

            if((strcmp(StudButton,"0"))!=0 && (strcmp(StudButton,"1"))!=0 && (strcmp(StudButton,"2"))!=0 && (strcmp(StudButton,"5"))!=0 && (strcmp(StudButton,"6"))!=0 && (strcmp(StudButton,"7"))!=0 && (strcmp(StudButton,"8"))!=0 && (strcmp(StudButton,"Q"))!=0){
                printf("������������ �������\n");
                strcpy(StudButton,"0");
            }
// ���������:
            if((strcmp(StudButton,"Q"))==0){
                printf("������� � ������� ����\n");
                return;
            }
            if ((strcmp(StudButton,"1"))==0){    //���������� ��������
                if(AddStudent(BaseStud,NumberLineStud)!=1){
                NumberLineStud++;}
                strcpy(StudButton,"0");
            }
           if((strcmp(StudButton,"2"))==0){ //�������� ��������
                DeleteStudent(BaseStud, NumberLineStud);
                strcpy(StudButton,"0");
            }

            if((strcmp(StudButton,"5"))==0){ 
                printf("���� � ����������");
                 strcpy(StudButton,"0");
            }
            if((strcmp(StudButton,"6"))==0){ //��������� �����
                printf("���� � ����������");
                strcpy(StudButton,"0");
            }
            if((strcmp(StudButton,"7"))==0){  //����� ����������
                SearchStudent(BaseStud,NumberLineStud);
                strcpy(StudButton,"0");
            }
            if ((strcmp(StudButton,"8"))==0){	//����� �� ��������� � ����������� ���������
                ExitStudents(BaseStud, NumberLineStud);
                strcpy(StudButton,"-1");
            }
        }
    }
}    