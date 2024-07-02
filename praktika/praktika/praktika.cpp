#include "stdafx.h"//����������� ���������
#include <clocale>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>

using namespace System;
using namespace std;
using namespace System::IO;

#define ENTER 13//����������� ������
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79


int menu(int);//�������� �������� ������������ �������
void maxsrok(struct z*);
void tipisrok(struct z*);
void moskvichi(struct z*);
void alfalist(struct z*);
void vstavka(struct z*, char*);
void hard(struct z*);
void diagram(struct z*);

//char dan[7][102]={
//	"� ������ ���������� ����� ������� ����� �������� ��������?                                          ",
//	"����� ��� ����� �������, ������������ � ������������ ����?                                          ",
//	"������� ����� ������� ������� � ������������ ������?                                                ",
//	"���������� ������ ���� �����������                                                                  ",
//	"���� �� ����������, ������� ���������� ���� �������� � ����������� � ������ �������?                ",
//	"���������. ���������� ����������� ��������� �������                                                 ",
//	"�����                                                                                               "
//};//������� ������ �������� - ������� ����
//char BlankLine[ ]="                                                                                                      "; //������ ������� ��� ����
//int NC;//���������� ������� ������ ���������
struct z{
	char name[20];//��� ����������
	char tip[20];//��� ��������
	int srok;//���� ��������
	int summa;//����� ��������
	char data[11];//���� ��������
	char gorod[15];//�����
 };//������ ��������� ��� �������� ������ 
struct sp{ //������ ��� ����������� ������, ���������� �������� ��������� ������������� ������
	char name[20];
	int summa;
	struct sp* sled;//��������� �������
	struct sp* pred;//���������� �������
} *spisok;//������, ���������� �������� ��������� ������������� ������

int main(array<System::String ^> ^args){//�� ��������� ������ ������������ �������� �����, ��������� ������ �� ����� � ���������� ������ 
int i,n;
int NC;//���������� ������� ������ ���������
char BlankLine[ ]="                                                                                                      "; //������ ������� ��� ����
char dan[7][102]={
	"� ������ ���������� ����� ������� ����� �������� ��������?                                          ",
	"����� ��� ����� �������, ������������ � ������������ ����?                                          ",
	"������� ����� ������� ������� � ������������ ������?                                                ",
	"���������� ������ ���� �����������                                                                  ",
	"���� �� ����������, ������� ���������� ���� �������� � ����������� � ������ �������?                ",
	"���������. ���������� ����������� ��������� �������                                                 ",
	"�����                                                                                               "
};//������� ������ �������� - ������� ����
FILE *in;
struct z *poluchatel;

	setlocale(LC_CTYPE,"Russian");//��������� �������� ����� 
	Console::CursorVisible::set(false);//��������� ��������� ������� 
	Console::BufferHeight=Console::WindowHeight;//��������� ������� ������ �� ������
	Console::BufferWidth=Console::WindowWidth;//��������� ������� ������ �� ������

    if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������ !");//��� ��������� �������� ������� ���������:"���� �� ������!"
	    getch(); exit(1);
    }

	fscanf(in,"%d",&NC);
	poluchatel=(struct z*)malloc(NC*sizeof(struct z));//�������� ������

	for(i=0;i<NC;i++){//��������� ������ �� ������
    fscanf(in,"%s%s%d%d%s%s",poluchatel[i].name,
    poluchatel[i].tip, &poluchatel[i].srok, &poluchatel[i].summa,
    poluchatel[i].data, poluchatel[i].gorod);
	}
	for(i=0;i<NC;i++){//������� ������ �� ������ �� �����
    printf("\n%-20s %-20s %7d %7d %-11s %-15s", poluchatel[i].name,
    poluchatel[i].tip, poluchatel[i].srok, poluchatel[i].summa,
    poluchatel[i].data, poluchatel[i].gorod);
	}
	getch();
	
while(1)//� ����� ������� ������� ��� �������� � ������ � � ��������� ����� 
{
	 Console::ForegroundColor=ConsoleColor::Cyan;//������������� ��� ���� ���� � ��������� ��� �������
	 Console::BackgroundColor=ConsoleColor::Gray;
	 Console::Clear();
	 Console::ForegroundColor=ConsoleColor::Black;
	 Console::BackgroundColor=ConsoleColor::Cyan;
	 Console::CursorLeft=10;//������ �����, ������ ����� ����������� ������� ����
	 Console::CursorTop=4;
	 printf(BlankLine);
for(i=0;i<7;i++)//���������� ��������
{
	Console::CursorLeft=10;//��������� �����, ��� ����� ������������� ���������� ������� ��� ����
	Console::CursorTop=i+5;
	printf(" %s ",dan[i]);
}
	Console::CursorLeft=10;
	Console::CursorTop=12;
	printf(BlankLine);
	n = menu(7);//����� ������� � ����
switch(n) {
    case 1: maxsrok(poluchatel); break;
    case 2: tipisrok(poluchatel); break;
    case 3: moskvichi(poluchatel); break;
    case 4: alfalist(poluchatel); break;
    case 5: hard(poluchatel); break;
    case 6: diagram(poluchatel); break;
    case 7: exit(0);
}
}
return 0;
}
int menu(int n)//n = 7
{
	char dan[7][102]={
	"� ������ ���������� ����� ������� ����� �������� ��������?                                          ",
	"����� ��� ����� �������, ������������ � ������������ ����?                                          ",
	"������� ����� ������� ������� � ������������ ������?                                                ",
	"���������� ������ ���� �����������                                                                  ",
	"���� �� ����������, ������� ���������� ���� �������� � ����������� � ������ �������?                ",
	"���������. ���������� ����������� ��������� �������                                                 ",
	"�����                                                                                               "
};//������� ������ �������� - ������� ����
	int y1=0,y2=n-1;//������������� ��������� ��� �������
	char c=1;
	while (c!=ESC)//��� ������� ������ ESC ���� ���������
{
switch(c) {
    case DOWN: y2=y1; y1++; break;//���������������� ������ DOWN,������� ��������� ������������ ���� �� ����
    case UP: y2=y1; y1--; break;//���������������� ������ UP, ������� ��������� ���������� ����� �� ����
    case ENTER: return y1+1;//���������������� ������ ENTER, ������� ��������� ������� ������ 
    case HOME: y2 = y1; y1 = 0; break;//���������������� ������ HOME, ������� ��������� ������� ������ ������
    case END: y2 = y1; y1 = n - 1; break;//���������������� ������ END, ������� ��������� ������� ��������� ������
}
	if(y1>n-1){y2=n-1;y1=0;}//�������, ����� ����������� ������ DOWN
	if(y1<0) {y2=0;y1=n-1;}//�������, ����� ����������� ������ UP
	Console::ForegroundColor=ConsoleColor::Black;//��� ������ ������� ����� ������������ � ������ ����
	Console::BackgroundColor=ConsoleColor::White;//��� ������ ������� ������ ��� ������������ � ����� ����
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Cyan;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
} 
exit(0);
}
void maxsrok(struct z* poluchatel)//������� ������ ��������� (������������ ����� �������� ��������)
{
	int i=0; 
	int NC;
	FILE *in;//��������� ������ �� ����� � ���������� ������
	if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������!");//��� ��������� �������� ������� ���������� ����� �� ������!�
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	struct z best;
	strcpy(best.name,poluchatel[0].name);//� ���������� ��������� ���������� ������� �������
	best.srok=poluchatel[0].srok;
	for(i=1;i<NC;i++)
		if (poluchatel[i].srok>best.srok)//������� ��� ������ ������������� ������� ��������
		{
			strcpy(best.name,poluchatel[i].name);
			best.srok=poluchatel[i].srok;
		}
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("������������ ����� �������� ������� %d ���� ",best.srok);//����� ������
	printf("����� ���������� %s",best.name);
	getch();
}
void tipisrok(struct z* poluchatel)//������������ ������ � �������� (��� �������, ������������ � ������������ ����)
{
    int i;
    char b;
	int NC;//���������� ������� ������ ��������
	FILE *in;//��������� ������ �� ����� � ���������� ������
	if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������!");//��� ��������� �������� ������� ���������� ����� �� ������!�
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	Console::ForegroundColor = ConsoleColor::Black;
	Console::BackgroundColor = ConsoleColor::White;
    Console::CursorLeft = 10;
    Console::CursorTop = 15;
    Console::CursorVisible::set(true);
    printf("������� ���� ��������:");
    Console::CursorLeft = 10;
    Console::CursorTop = 16;
    scanf("%d", &b);
    Console::CursorLeft = 10;
    Console::CursorTop = 17;
    for (i = 1; i < NC; i++) {
        if (poluchatel[i].srok == b) {
            Console::CursorLeft = 10;
			printf("��� ��������:");
            printf("%-20s", poluchatel[i].tip);
            Console::CursorTop += 1;
            Console::CursorVisible::set(false);
        }
    }
    getch();
}
void moskvichi(struct z* poluchatel)//���� ������ � ���������� (����� ����������� �� �������)
{
	int i,k=0;
	int NC;
	char s[80];
	FILE *in;//��������� ������ �� ����� � ���������� ������
	if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������!");//��� ��������� �������� ������� ���������� ����� �� ������!�
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	Console::BackgroundColor=ConsoleColor::White;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	Console::CursorVisible::set(true);
	printf("������� �����:");
	Console::CursorLeft = 10;
    Console::CursorTop = 16;
	SetConsoleCP(1251);
	gets(s);
	SetConsoleCP(866);
	for(i=0;i<NC;i++){
		if (strcmp(poluchatel[i].gorod, s)==0){
			k++;
		}
	}
	Console::CursorLeft=10;
	Console::CursorTop=17;
printf("���������� �����, � ������� �������� � ������ ������: %d \n", k);
getch();
}
void alfalist(struct z* poluchatel)//���������� ������
{
 int i,x;
 int NC;//���������� ������� ������ ��������
	FILE *in;//��������� ������ �� ����� � ���������� ������
	if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������!");//��� ��������� �������� ������� ���������� ����� �� ������!�
		getch();exit(1);}
	fscanf(in,"%d",&NC);
 struct sp* nt,*z;
 x = 3;
 Console::ForegroundColor = ConsoleColor::DarkCyan;
 Console::BackgroundColor = ConsoleColor::White;
 Console::Clear();
 printf("\n ���������� ������ �����������");
 printf("\n=================================================================\n");
 if (!spisok)//�������� ������������� ������
 for (i = 0; i < NC; i++)
	vstavka(poluchatel, poluchatel[i].name);//��������� ������� ������� ��� ���������� ����������� ������
 for (nt = spisok; nt != 0; nt = nt->sled)
 {
 Console::CursorLeft = 0;
 Console::CursorTop = x + 1;
 printf(" %-20s %ld", nt->name, nt->summa);
 x += 1;
 }
 x = 3;
 Console::CursorLeft = 40;
 Console::CursorTop = 1;
 printf("�������� ���������� ������");
 for (nt = spisok; nt != 0; z = nt, nt = nt->sled);
 for (nt = z, i = 0; nt != 0; i++, nt = nt->pred)
 {
 Console::CursorLeft = 40;
 Console::CursorTop = x + 1;
 printf(" %-20s %ld", nt->name, nt->summa);
 x += 1;
 }
 getch();
}void vstavka(struct z* poluchatel, char* name)//������� � ���������� ������
{
 int i;
 int NC;//���������� ������� ������ ��������
	FILE *in;//��������� ������ �� ����� � ���������� ������
	if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������!");//��� ��������� �������� ������� ���������� ����� �� ������!�
		getch();exit(1);}
	fscanf(in,"%d",&NC);
 struct sp* nov, * nt, * z = 0;
 for (nt = spisok; nt != 0 && strcmp(nt->name, name) < 0; z = nt, nt = nt->sled);
 if (nt && strcmp(nt->name, name) == 0) return;
 nov = (struct sp*)malloc(sizeof(struct sp));//�������� ������ ��� ����� ���
 strcpy(nov->name, name);
 nov->sled = nt;
 nov->pred = z;
 nov->summa = 0;
 for (i = 0; i < NC; i++)
 if (strcmp(poluchatel[i].name, name) == 0)
 nov->summa += poluchatel[i].summa;
 if (!z) spisok = nov;
 if (z) z->sled = nov;
 if (nt) nt->pred = nov;
 return;
}void hard(struct z *poluchatel)//������� ������ (����� ����������)
{
int i,x,n=0;
int NC;//���������� ������� ������ ��������
	FILE *in;//��������� ������ �� ����� � ���������� ������
	if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������!");//��� ��������� �������� ������� ���������� ����� �� ������!�
		getch();exit(1);}
	fscanf(in,"%d",&NC);
for(i=0;i<NC;i++){
	for(x=1;x<NC;x++){
		if ((poluchatel[i].srok==poluchatel[x].srok) && (strcmp(poluchatel[i].gorod,poluchatel[x].gorod)!=0)){
			Console::BackgroundColor=ConsoleColor::White;
			Console::ForegroundColor=ConsoleColor::Black;
			Console::CursorLeft=10;
			Console::CursorTop=15;
			printf("������� %s � %s ����� ���������� ���� ��������: %d ",poluchatel[i].name,poluchatel[x].name,poluchatel[x].srok);
			Console::CursorLeft=10;
			Console::CursorTop=16;
			printf("� ��������� � ������ �������: %s � %s",poluchatel[i].gorod,poluchatel[x].gorod);
			n=1;
			break;
		}
	}
	if(n==1)
		break;
}
if(n!=1){
	Console::BackgroundColor=ConsoleColor::White;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("���������� ���!");
}
getch();
}void diagram(struct z* poluchatel)//���������, ������������ ����������� ��������� �������
{
	struct sp *nt;//���������� ��� ������ �� �������
	int NC;//���������� ������� ������ ��������
	FILE *in;//��������� ������ �� ����� � ���������� ������
	if((in=fopen("spisok.txt","r"))==NULL){//������� ������� ����
		printf("\n���� spisok.txt �� ������!");//��� ��������� �������� ������� ���������� ����� �� ������!�
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	int len, i, NColor;//i-��� ������ ������
	long sum = 0;//�����-100%
	char str1[20];//���������� ��� �����
	char str2[20];//���������� ��� ���������
	System::ConsoleColor Color;//����� ���������, ������� ���������� �������� ���� � ���� ���� �������
	Console::ForegroundColor = ConsoleColor::Green;//���� ������
	Console::BackgroundColor = ConsoleColor::White;//���� ����
	Console::Clear();
    for (i = 0; i < NC; i++)
		sum = sum + poluchatel[i].summa;
			if (!spisok)//���� ������ �� ���������� �� ������� ���
				for (i = 0; i < NC; i++)
					vstavka(poluchatel, poluchatel[i].name);
					Color=ConsoleColor::Black;
					NColor = 0;// ������������� ���������� ����� �� 0 (������)
	for (nt = spisok, i = 0; nt != 0; nt = nt->sled, i++)
 {
		 sprintf(str1,"%s", nt->name);//���������� � ������ ���������� ���
		 sprintf(str2, " %3.1f%%", (nt->summa * 100./ sum));//�� ������ ���������� ���������� �������
		 Console::ForegroundColor = ConsoleColor::DarkCyan;
		 Console::BackgroundColor = ConsoleColor::White;
		 Console::CursorLeft = 5;//������������� ��������� ������� � ������� ���
		 Console::CursorTop = i + 1;
		 printf(str1);
		 Console::CursorLeft = 20;
		 printf("%s", str2);
		 Console::BackgroundColor = ++Color; NColor++;
		 Console::CursorLeft = 30;
	for (len = 0; len < nt->summa * 100 / sum; len++) printf(" ");
		if (NColor == 14)//���� ���� ������� �����, �� ������������� �� ������
		{
			Color = ConsoleColor::Black;
			NColor = 0;
			}
	}
 getch();
 return;
 }
