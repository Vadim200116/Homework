#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"structs.c"
#include "books.c"
#include"students.c"

#define STRING_SIZE 256  //����� ������ �����
#define CASE_SIZE 32 //����� ������ �����
#define MASSIVE_SIZE 4096 // ������ ������� ��������



int Writeusers(USER*Base,int size){
    FILE *Usersfile=fopen("users.csv", "r");
    char Basket[STRING_SIZE]; // ���������� userfile
    for(int i=0;i<size;i++){
        fgets(Basket, STRING_SIZE, Usersfile);
        strcpy(Base[i].login,strtok(Basket,";"));
        strcpy(Base[i].pass,strtok(NULL,";"));
        strcpy(Base[i].students,strtok(NULL,";"));
        strcpy(Base[i].books, strtok(NULL,"\n"));
    }
    fclose(Usersfile);
}

int main(){
    setlocale(LC_ALL,"Russian");
    FILE*Usersfile=fopen("users.csv","r");
    int NumberLine=0;
    if(Usersfile==NULL){
        printf("������, ����������� ���� � ��������������");
    }else{
        while(!feof(Usersfile)){  //������� ���������� �����
            if((fgetc(Usersfile))=='\n'){
                NumberLine++;
            }
        }
        fclose(Usersfile);
        USER*Base;
        Base=calloc(MASSIVE_SIZE,sizeof(USER));
        Writeusers(Base, NumberLine);
        printf("����� ����������!\n");
        char login[CASE_SIZE];
        char pass[CASE_SIZE];
        int found=0; // ������������� ������
        int foundp=0;//������������ ������
        int NumUs=0;//����� ������������
        int exit; //������������� ������ �� ���������
        int prog=0; //������������� ����������� � ���� ���������
         while(1){ //���� �����������
            exit=0;
            if(!found){
                printf("������� �����(Q-����� �����):");
                SetConsoleCP(1251);
                scanf("%s",&login);
                SetConsoleCP(866);
            }
            if(strcmp(login,"Q")==0){
                break;
            }
            if(!foundp){
                for(NumUs=0;NumUs<NumberLine;NumUs++){
                    if(strcmp(Base[NumUs].login,login)==0){
                        found=1;
                        printf("������� ������(Q-������ ������ �����):");
                        SetConsoleCP(1251);
                        scanf("%s",&pass);
                        SetConsoleCP(866);
                        if(strcmp(Base[NumUs].pass,pass)==0){
                            foundp=1;
                        }
                        if(!strcmp(pass,"Q")){
                            found=0;
                            foundp=0;
                            exit=1;
                        }
                        break;
                    }
                }
            }
            if(found==0&&exit==0){
                printf("������������ �� ������\n");
            }
            if(foundp==0 && found==1){
                printf("�������� ������\n");
            }
            if(foundp==1 && found==1){
                if(prog==0){
                    printf("\n� ������������, %s!\n",login);
                }
                if((strcmp(Base[NumUs].students,"1"))==0 && (strcmp(Base[NumUs].books,"1"))==0){
                    char UserButton[4];
                   if(prog==0){
                        printf("�� ������ ������� ����������, ������� ������ ���������:\n������� 1 - ����� ������� ���������� students\n������� 2 - ����� ������� ���������� books\n");
                        printf("(����� �����, ������� - Q)\n");
                   }
                    printf("admin:");
                    SetConsoleCP(1251);
                    scanf("%s",&UserButton);
                    SetConsoleCP(866);
                    if(!strcmp(UserButton,"1")){
                        students();
                        prog=1;
                    }else if(!strcmp(UserButton,"2")){
                        books();
                        prog=1;
                    }else if(!strcmp(UserButton,"Q")){
                        found=0;
                        foundp=0;
                        prog=0;
                    }else{
                        printf("������������ �������\n");
                        prog=1;
                    }
                }
                if((strcmp(Base[NumUs].students,"1"))==0 && (strcmp(Base[NumUs].books,"0"))==0){
                    printf("�� ������ �������� ������ � ����������� ���������\n");
                    students();
                    found=0;
                    foundp=0;
                }
                if((strcmp(Base[NumUs].students,"0"))==0 && (strcmp(Base[NumUs].books,"1"))==0){
                    printf("�� ������ �������� ������ � ����������� ����\n");
                    books();
                    found=0;
                    foundp=0;
                }
            }
        }
    }
}
