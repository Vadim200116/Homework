#include<Windows.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"structs.c"
#define STRING_SIZE 256  //����� ������ �����
#define CASE_SIZE 32 //����� ������ �����
#define MASSIVE_SIZE 4096 // ������ ������� ��������

void WriteBooks(BOOK*Base, int size){
    FILE *Basefile=fopen("books.csv", "r");
    char Basket[STRING_SIZE];
    for(int i=0;i<size;i++){
        fgets(Basket, STRING_SIZE, Basefile);
        Base[i].ISBN=atoll(strtok(Basket,";"));
        strcpy(Base[i].NameSP,strtok(NULL,";"));
        strcpy(Base[i].BookName,strtok(NULL,";"));
        strcpy(Base[i].Number,strtok(NULL,";"));
        strcpy(Base[i].Avail, strtok(NULL,"\n"));
    }
    fclose(Basefile);
}

int ViewBooks(BOOK*Base, int size){
        printf("�������:\n");
        printf("________________________________________________________________________________________\n");
        printf("   ����� ISBN  |    � �.�.������    |            ��������          |���-��|������.���-��|\n");
        for(int i=0;i<size;i++){
            if(Base[i].ISBN){
                printf("________________________________________________________________________________________\n");
                printf("%15lli|%20s|%30s|%6s|%13s|\n", Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
            }
        }
        printf("________________________________________________________________________________________\n");
        printf("����� ��������� ������� 12\n");
}

void StrSwap(BOOK*Base,int left,int right){ 
    BOOK*Basket;
    Basket=calloc(MASSIVE_SIZE,sizeof(BOOK));
    Basket[left]=Base[left];
    Base[left]=Base[right];
    Base[right]=Basket[left];
}

void QuickSort(BOOK *Base, int left, int right){ 
  int startleft = left;
  int startright = right;
  long long int pivot = Base[left].ISBN;
  while (left < right){
    while (Base[right].ISBN >= pivot && left < right)
      right--;
        if(left != right){
            StrSwap(Base,left,right);
            left++;
        }
    while (Base[left].ISBN <= pivot && left < right)
        left++;
        if (left != right){
            StrSwap(Base,right,left);
            right--;
        }
  }
  pivot=left;
  left=startleft;
  right=startright;
  if (left<pivot)
    QuickSort(Base, left, pivot - 1);
  if (right>pivot)
    QuickSort(Base, pivot + 1, right);
}


int AddBook(BOOK*Base, int NumberLine){ 
        printf("���������� �����(������ �������� ������������ �������)\n����� ISBN:");
        char StrISBN[CASE_SIZE];
        scanf("%s",&StrISBN);
        if((strcmp(StrISBN,"Q"))==0){
            return 1;
        }
        long long int ISBN=atoll(StrISBN);
        int copy=0;
        for(int i=0; i<NumberLine; i++) {
            if(Base[i].ISBN==ISBN){
                printf("����� ��� ���� � ����.\n");
                copy=1;
                return 1;
            }
        }
        if(copy==1){ 
            return 1;
        }
        if(copy==0){
            char NameSP[CASE_SIZE];
            printf("�.�.�. ������:");
            SetConsoleCP(1251);
            scanf("%s",&NameSP);
            SetConsoleCP(866);
            if(!strcmp(NameSP,"Q")){
                return 1;
            }
            char BookName[CASE_SIZE];
            printf("��������:");
            SetConsoleCP(1251);
            scanf("%s",&BookName);
            SetConsoleCP(866);
            if(!strcmp(BookName,"Q")){
                return 1;
            }
            char Number[CASE_SIZE];
            printf("����������:");
            SetConsoleCP(1251);
            scanf("%s",&Number);
            SetConsoleCP(866);
            if(!strcmp(Number,"Q")){
                return 1;
            }
            char Avail[CASE_SIZE];
            printf("��������� ����������:");
            SetConsoleCP(1251);
            scanf("%s",&Avail);
            SetConsoleCP(866);
            if(!strcmp(Avail,"Q")){
                return 1;
            }
            Base[NumberLine].ISBN = ISBN;                           
            strcpy(Base[NumberLine].NameSP,NameSP);
            strcpy(Base[NumberLine].BookName,BookName);
            strcpy(Base[NumberLine].Number,Number);
            strcpy(Base[NumberLine].Avail,Avail);
            printf("����� ���������\n");
            ViewBooks(Base, NumberLine+1);
            return 0;
    }
}

void DeleteBook(BOOK*Base, int NumberLine){
                int del=0;
                printf("�������� �����\n");
                printf("������� ����� ISBN:");
                char StrISBN[CASE_SIZE];
                scanf("%s",&StrISBN);
                if(!strcmp(StrISBN,"Q")){
                    return;
                }
                long long int ISBN=atoll(StrISBN);
                for(int p=0; p<NumberLine; p++){
                    if(Base[p].ISBN == ISBN){
                        Base[p].ISBN=0;
                        del=1;
                        printf("����� �������\n");
                        ViewBooks(Base, NumberLine);
                        return;
                    }
                }
                if(del==0){
                    printf("����� �� �������\n");
                }

}


void SearchBook(BOOK*Base,int NumberLine){
                printf("����� ���������� �� ISBN\n������� ISBN:");
                int d=0;
                char StrISBN[CASE_SIZE];
                scanf("%s",&StrISBN);
                if((strcmp(StrISBN,"Q"))==0){
                    return;
                }
                long long int ISBN=atoll(StrISBN);
                int found=0;
                for(int i=0;i<NumberLine;i++){
                    if(Base[i].ISBN==ISBN){
                        if(d==0){
                        printf("________________________________________________________________________________________\n");
                        printf("   ����� ISBN  |    � �.�.������    |            ��������          |���-��|������.���-��|\n");
                        printf("________________________________________________________________________________________\n");
                        }
                        d=1;
                        printf("%15lli|%20s|%30s|%6s|%13s|\n", Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
                        printf("________________________________________________________________________________________\n");
                        found=1;
                    }
                }
                if(found==0){
                    printf("����� � ����� ������� ISBN �� �������\n");
                }
}

float ExitBooks(BOOK*Base, int NumberLine){
                FILE *Basefile=fopen("books.csv", "w");
                for(int i=0;i<NumberLine;i++){
                    if(Base[i].ISBN){
                        fprintf(Basefile,"%lli;%s;%s;%s;%s\n",Base[i].ISBN,Base[i].NameSP,Base[i].BookName,Base[i].Number,Base[i].Avail);
                    }
                }
                printf("���� ��������\n");
                fclose(Basefile);
                free(Base);
}


void books(){
    setlocale(LC_ALL,".1251");
    int NumberLineBooks=0;// ���������� �������
	FILE *BooksFile=fopen("books.csv", "r");
	if(BooksFile==NULL){
        printf("���� �� ������.");
    }else{
        printf("���� ��������\n");
        while(!feof(BooksFile)){  
            if((fgetc(BooksFile))=='\n'){
                NumberLineBooks++;
            }
        }
        printf("���������� �����: %d\n",NumberLineBooks);
        fclose(BooksFile);
        BOOK*Basebooks;             //������ ���� 
        Basebooks=calloc(MASSIVE_SIZE,sizeof(BOOK));
        WriteBooks(Basebooks, NumberLineBooks); //���������� ������ ����� � Basebooks 
        if(NumberLineBooks>0){ 
            ViewBooks(Basebooks,NumberLineBooks);
        }


        printf("�������� ��������:(������ ������� �������)\n");
		printf("1 - ����� �������� ����� �����\n2 - ����� ������� �����\n3 - ����� ����� ����� �� ISBN\n4 - ����� ������������� ������� �� ����������� ISBN\n12 - ����� ����� � ����������� ���������\nQ - ����� ��������� � ���������� ���� (�������� �� ���� ����������)\n");

        char BooksButton[4];
        strcpy(BooksButton,"-1");
		while(!strcmp(BooksButton,"-1")){ //������� ����
            printf("books:");
            SetConsoleCP(1251);
            scanf("%s",&BooksButton);
            SetConsoleCP(866);
            printf("%s- ",BooksButton);

            if((strcmp(BooksButton,"Q")) && (strcmp(BooksButton,"0")) && (strcmp(BooksButton,"1")) && (strcmp(BooksButton,"2")) && (strcmp(BooksButton,"3")) && (strcmp(BooksButton,"4")) && (strcmp(BooksButton,"12"))){
                printf("������������ �������\n");
                strcpy(BooksButton,"-1");
            }
            // ���������:
            if(!strcmp(BooksButton,"Q")){
                printf("������� � ������� ����\n");
                return;
            }
            if (!strcmp(BooksButton,"1")){    //���������� �����
                if(AddBook(Basebooks,NumberLineBooks)!=1){
                NumberLineBooks++;
                }
                strcpy(BooksButton,"-1");
            }
            if(!strcmp(BooksButton,"2")){ //�������� �����
                DeleteBook(Basebooks, NumberLineBooks);
                strcpy(BooksButton,"-1");
            }

            if(!strcmp(BooksButton,"3")){  //����� ����������
                SearchBook(Basebooks,NumberLineBooks);
                strcpy(BooksButton,"-1");
            }

            if(!strcmp(BooksButton,"4")){  //���������� �� ISBN
                QuickSort(Basebooks,0,NumberLineBooks-1);
                ViewBooks(Basebooks,NumberLineBooks);
                strcpy(BooksButton,"-1");
            }
            if (!strcmp(BooksButton,"12")){	//����� �� ��������� � ����������� ���������
                ExitBooks(Basebooks, NumberLineBooks);
                strcpy(BooksButton,"0");
            }

        }
    }
}    