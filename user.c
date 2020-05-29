#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"structsnew.c"
#include "books.c"
#include"students.c"

int Writeusers(USER*Base,int size){
    FILE *Usersfile=fopen("users.csv", "r");
    char Basket[STRING_SIZE];
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
        /*if(NumberLine>0){ //������� �������, ���� ��� �� ������
            viewusers(Base,NumberLine);
        }*/
        printf("����� ����������!\n");
        char login[CASE_SIZE];
        char pass[CASE_SIZE];
        int found=0;
        int foundp=0;
        int NumUs=0;
        int exit;
        int uncor=0;
         while(1){ //���� �����������
            exit=0;
            if(found==0){
                printf("������� �����(Q-����� �����):");
                SetConsoleCP(1251);
                scanf("%s",&login);
                SetConsoleCP(866);
            }
            if(strcmp(login,"Q")==0){
                break;
            }
            if(foundp==0){
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
                        if(strcmp(pass,"Q")==0){
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
                if(uncor==0){
                    printf("\n� ������������, %s!\n",login);
                }
                if((strcmp(Base[NumUs].students,"1"))==0 && (strcmp(Base[NumUs].books,"1"))==0){
                    char UserButton[4];
                   if(uncor==0){
                        printf("�� ������ ������� ����������, ������� ������ ���������:\n������� 1 - ����� ������� ���������� students\n������� 2 - ����� ������� ���������� books\n");
                        printf("(����� �����, ������� - Q)\n");
                   }
                    printf("admin:");
                    SetConsoleCP(1251);
                    scanf("%s",&UserButton);
                    SetConsoleCP(866);
                    if((strcmp(UserButton,"1"))==0){
                        students();
                        uncor=1;
                    }else if((strcmp(UserButton,"2"))==0){
                        books();
                        uncor=1;
                    }else if((strcmp(UserButton,"Q"))==0){
                        found=0;
                        foundp=0;
                        uncor=0;
                    }else{
                        printf("������������ �������\n");
                        uncor=1;
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
