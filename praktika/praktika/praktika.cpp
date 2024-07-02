#include "stdafx.h"//подключение библиотек
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

#define ENTER 13//обозначение кнопок
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79


int menu(int);//указание шаблонов используемых функций
void maxsrok(struct z*);
void tipisrok(struct z*);
void moskvichi(struct z*);
void alfalist(struct z*);
void vstavka(struct z*, char*);
void hard(struct z*);
void diagram(struct z*);

//char dan[7][102]={
//	"У какого получателя самое большое время ожидания доставки?                                          ",
//	"Какой тип имеют посылки, доставленные в определенный срок?                                          ",
//	"Сколько людей получат посылку в определенном городе?                                                ",
//	"Алфавитный список всех получателей                                                                  ",
//	"Есть ли получатели, имеющие одинаковый срок доставки и находящиеся в разных городах?                ",
//	"Диаграмма. Процентное соотношение стоимости посылок                                                 ",
//	"Выход                                                                                               "
//};//задание списка вопросов - пунктов меню
//char BlankLine[ ]="                                                                                                      "; //пустая строчка для меню
//int NC;//количество позиций задано глобально
struct z{
	char name[20];//ФИО получателя
	char tip[20];//Тип доставки
	int srok;//Срок доставки
	int summa;//Сумма доставки
	char data[11];//Дата доставки
	char gorod[15];//Город
 };//шаблон структуры для исходных данных 
struct sp{ //шаблон для алфавитного списка, глобальное описание структуры двустороннего списка
	char name[20];
	int summa;
	struct sp* sled;//следующий элемент
	struct sp* pred;//предыдущий элемент
} *spisok;//шаблон, глобальное описание структуры двустороннего списка

int main(array<System::String ^> ^args){//на локальном уровне осуществляем открытие файла, считываем данные из файла в выделенную память 
int i,n;
int NC;//количество позиций задано глобально
char BlankLine[ ]="                                                                                                      "; //пустая строчка для меню
char dan[7][102]={
	"У какого получателя самое большое время ожидания доставки?                                          ",
	"Какой тип имеют посылки, доставленные в определенный срок?                                          ",
	"Сколько людей получат посылку в определенном городе?                                                ",
	"Алфавитный список всех получателей                                                                  ",
	"Есть ли получатели, имеющие одинаковый срок доставки и находящиеся в разных городах?                ",
	"Диаграмма. Процентное соотношение стоимости посылок                                                 ",
	"Выход                                                                                               "
};//задание списка вопросов - пунктов меню
FILE *in;
struct z *poluchatel;

	setlocale(LC_CTYPE,"Russian");//поддержка русского языка 
	Console::CursorVisible::set(false);//отключаем видимость курсора 
	Console::BufferHeight=Console::WindowHeight;//установка размера буфера по высоте
	Console::BufferWidth=Console::WindowWidth;//установка размера буфера по ширине

    if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт !");//при неудачном открытии выводим сообщение:"Файл не открыт!"
	    getch(); exit(1);
    }

	fscanf(in,"%d",&NC);
	poluchatel=(struct z*)malloc(NC*sizeof(struct z));//выделяем память

	for(i=0;i<NC;i++){//считываем данные из списка
    fscanf(in,"%s%s%d%d%s%s",poluchatel[i].name,
    poluchatel[i].tip, &poluchatel[i].srok, &poluchatel[i].summa,
    poluchatel[i].data, poluchatel[i].gorod);
	}
	for(i=0;i<NC;i++){//выводим данные из списка на экран
    printf("\n%-20s %-20s %7d %7d %-11s %-15s", poluchatel[i].name,
    poluchatel[i].tip, poluchatel[i].srok, poluchatel[i].summa,
    poluchatel[i].data, poluchatel[i].gorod);
	}
	getch();
	
while(1)//в цикле создаем область для вопросов и красим её в указанные цвета 
{
	 Console::ForegroundColor=ConsoleColor::Cyan;//устанавливаем для букв цвет и подсветку для вопроса
	 Console::BackgroundColor=ConsoleColor::Gray;
	 Console::Clear();
	 Console::ForegroundColor=ConsoleColor::Black;
	 Console::BackgroundColor=ConsoleColor::Cyan;
	 Console::CursorLeft=10;//первая точка, откуда будем закрашивать область меню
	 Console::CursorTop=4;
	 printf(BlankLine);
for(i=0;i<7;i++)//размещение вопросов
{
	Console::CursorLeft=10;//последняя точка, где будет заканчиваться выделенная область под меню
	Console::CursorTop=i+5;
	printf(" %s ",dan[i]);
}
	Console::CursorLeft=10;
	Console::CursorTop=12;
	printf(BlankLine);
	n = menu(7);//выбор вопроса в меню
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
	"У какого получателя самое большое время ожидания доставки?                                          ",
	"Какой тип имеют посылки, доставленные в определенный срок?                                          ",
	"Сколько людей получат посылку в определенном городе?                                                ",
	"Алфавитный список всех получателей                                                                  ",
	"Есть ли получатели, имеющие одинаковый срок доставки и находящиеся в разных городах?                ",
	"Диаграмма. Процентное соотношение стоимости посылок                                                 ",
	"Выход                                                                                               "
};//задание списка вопросов - пунктов меню
	int y1=0,y2=n-1;//устанавливаем выделение для строчки
	char c=1;
	while (c!=ESC)//при нажатии кнопки ESC меню закроется
{
switch(c) {
    case DOWN: y2=y1; y1++; break;//программирование кнопки DOWN,которая позволяет перемещаться вниз по меню
    case UP: y2=y1; y1--; break;//программирование кнопки UP, которая позволяет перещаться вверх по меню
    case ENTER: return y1+1;//программирование кнопки ENTER, которая позволяет выбрать вопрос 
    case HOME: y2 = y1; y1 = 0; break;//программирование кнопки HOME, которая позволяет выбрать первый вопрос
    case END: y2 = y1; y1 = n - 1; break;//программировнаие кнопки END, которая позволяет выбрать последний вопрос
}
	if(y1>n-1){y2=n-1;y1=0;}//условие, когда срабатывает кнопка DOWN
	if(y1<0) {y2=0;y1=n-1;}//условие, когда срабатывает кнопка UP
	Console::ForegroundColor=ConsoleColor::Black;//при выборе вопроса буквы окрашиваются в черный цвет
	Console::BackgroundColor=ConsoleColor::White;//при выборе вопроса задний фон окрашивается в белый цвет
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
void maxsrok(struct z* poluchatel)//функция поиска максимума (максимальное время ожидания доставки)
{
	int i=0; 
	int NC;
	FILE *in;//считываем данные из файла в выделенную память
	if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт!");//при неудачном открытии выводим соообщение “Файл не открыт!”
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	struct z best;
	strcpy(best.name,poluchatel[0].name);//в переменную структуры записываем нулевой элемент
	best.srok=poluchatel[0].srok;
	for(i=1;i<NC;i++)
		if (poluchatel[i].srok>best.srok)//условие для поиска максимального времени ожидания
		{
			strcpy(best.name,poluchatel[i].name);
			best.srok=poluchatel[i].srok;
		}
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Максимальное время ожидания посылки %d дней ",best.srok);//вывод данных
	printf("имеет покупатель %s",best.name);
	getch();
}
void tipisrok(struct z* poluchatel)//формирование списка с условием (тип посылок, доставленных в определенный срок)
{
    int i;
    char b;
	int NC;//количество позиций задано локально
	FILE *in;//считываем данные из файла в выделенную память
	if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт!");//при неудачном открытии выводим соообщение “Файл не открыт!”
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	Console::ForegroundColor = ConsoleColor::Black;
	Console::BackgroundColor = ConsoleColor::White;
    Console::CursorLeft = 10;
    Console::CursorTop = 15;
    Console::CursorVisible::set(true);
    printf("Введите срок доставки:");
    Console::CursorLeft = 10;
    Console::CursorTop = 16;
    scanf("%d", &b);
    Console::CursorLeft = 10;
    Console::CursorTop = 17;
    for (i = 1; i < NC; i++) {
        if (poluchatel[i].srok == b) {
            Console::CursorLeft = 10;
			printf("Тип доставки:");
            printf("%-20s", poluchatel[i].tip);
            Console::CursorTop += 1;
            Console::CursorVisible::set(false);
        }
    }
    getch();
}
void moskvichi(struct z* poluchatel)//ввод строки с клавиатуры (поиск получателей по городам)
{
	int i,k=0;
	int NC;
	char s[80];
	FILE *in;//считываем данные из файла в выделенную память
	if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт!");//при неудачном открытии выводим соообщение “Файл не открыт!”
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	Console::BackgroundColor=ConsoleColor::White;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	Console::CursorVisible::set(true);
	printf("Введите город:");
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
printf("Количество людей, у которых доставка в данном городе: %d \n", k);
getch();
}
void alfalist(struct z* poluchatel)//алфавитный список
{
 int i,x;
 int NC;//количество позиций задано локально
	FILE *in;//считываем данные из файла в выделенную память
	if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт!");//при неудачном открытии выводим соообщение “Файл не открыт!”
		getch();exit(1);}
	fscanf(in,"%d",&NC);
 struct sp* nt,*z;
 x = 3;
 Console::ForegroundColor = ConsoleColor::DarkCyan;
 Console::BackgroundColor = ConsoleColor::White;
 Console::Clear();
 printf("\n Алфавитный список получателей");
 printf("\n=================================================================\n");
 if (!spisok)//проверка существования списка
 for (i = 0; i < NC; i++)
	vstavka(poluchatel, poluchatel[i].name);//применяем функцию вставка для заполнения алфавитного списка
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
 printf("Обратный алфавитный список");
 for (nt = spisok; nt != 0; z = nt, nt = nt->sled);
 for (nt = z, i = 0; nt != 0; i++, nt = nt->pred)
 {
 Console::CursorLeft = 40;
 Console::CursorTop = x + 1;
 printf(" %-20s %ld", nt->name, nt->summa);
 x += 1;
 }
 getch();
}void vstavka(struct z* poluchatel, char* name)//вставка в алфавитный список
{
 int i;
 int NC;//количество позиций задано локально
	FILE *in;//считываем данные из файла в выделенную память
	if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт!");//при неудачном открытии выводим соообщение “Файл не открыт!”
		getch();exit(1);}
	fscanf(in,"%d",&NC);
 struct sp* nov, * nt, * z = 0;
 for (nt = spisok; nt != 0 && strcmp(nt->name, name) < 0; z = nt, nt = nt->sled);
 if (nt && strcmp(nt->name, name) == 0) return;
 nov = (struct sp*)malloc(sizeof(struct sp));//выделяем память под новое имя
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
}void hard(struct z *poluchatel)//сложный вопрос (поиск совпадения)
{
int i,x,n=0;
int NC;//количество позиций задано локально
	FILE *in;//считываем данные из файла в выделенную память
	if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт!");//при неудачном открытии выводим соообщение “Файл не открыт!”
		getch();exit(1);}
	fscanf(in,"%d",&NC);
for(i=0;i<NC;i++){
	for(x=1;x<NC;x++){
		if ((poluchatel[i].srok==poluchatel[x].srok) && (strcmp(poluchatel[i].gorod,poluchatel[x].gorod)!=0)){
			Console::BackgroundColor=ConsoleColor::White;
			Console::ForegroundColor=ConsoleColor::Black;
			Console::CursorLeft=10;
			Console::CursorTop=15;
			printf("Клиенты %s и %s имеют одинаковый срок доставки: %d ",poluchatel[i].name,poluchatel[x].name,poluchatel[x].srok);
			Console::CursorLeft=10;
			Console::CursorTop=16;
			printf("и находятся в разных городах: %s и %s",poluchatel[i].gorod,poluchatel[x].gorod);
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
	printf("Совпадений нет!");
}
getch();
}void diagram(struct z* poluchatel)//диаграмма, показывающая соотношение стоимости посылок
{
	struct sp *nt;//переменная для работы со списком
	int NC;//количество позиций задано локально
	FILE *in;//считываем данные из файла в выделенную память
	if((in=fopen("spisok.txt","r"))==NULL){//попытка открыть файл
		printf("\nФайл spisok.txt не открыт!");//при неудачном открытии выводим соообщение “Файл не открыт!”
		getch();exit(1);}
	fscanf(in,"%d",&NC);
	int len, i, NColor;//i-для номера строки
	long sum = 0;//число-100%
	char str1[20];//переменная для имени
	char str2[20];//переменная для процентов
	System::ConsoleColor Color;//задаёт константы, которые определяют основной цвет и цвет фона консоли
	Console::ForegroundColor = ConsoleColor::Green;//цвет текста
	Console::BackgroundColor = ConsoleColor::White;//цвет фона
	Console::Clear();
    for (i = 0; i < NC; i++)
		sum = sum + poluchatel[i].summa;
			if (!spisok)//если список не существует то создаем его
				for (i = 0; i < NC; i++)
					vstavka(poluchatel, poluchatel[i].name);
					Color=ConsoleColor::Black;
					NColor = 0;// устанавливаем переменную цвета на 0 (чёрный)
	for (nt = spisok, i = 0; nt != 0; nt = nt->sled, i++)
 {
		 sprintf(str1,"%s", nt->name);//записываем в первую переменную имя
		 sprintf(str2, " %3.1f%%", (nt->summa * 100./ sum));//во вторую переменную записываем процент
		 Console::ForegroundColor = ConsoleColor::DarkCyan;
		 Console::BackgroundColor = ConsoleColor::White;
		 Console::CursorLeft = 5;//устанавливаем положение курсора и выводим имя
		 Console::CursorTop = i + 1;
		 printf(str1);
		 Console::CursorLeft = 20;
		 printf("%s", str2);
		 Console::BackgroundColor = ++Color; NColor++;
		 Console::CursorLeft = 30;
	for (len = 0; len < nt->summa * 100 / sum; len++) printf(" ");
		if (NColor == 14)//если цвет курсора белый, то устанавливаем на черный
		{
			Color = ConsoleColor::Black;
			NColor = 0;
			}
	}
 getch();
 return;
 }
