//Создать список интерфейсов функций, определённых в файле с программой на языке Си. 
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h> 

//#define YES 1
//#define NO 0

#define MAXLEN 1000 // максимальная длина строки 
#define NLINES 1000  // максимальное число строк 

void out_interface(char**, int);

void main(void)
{
	FILE *fp;
	//char *first_word;
	int nlines = 0;//количество строк в файле
	char **lines_ptr = NULL;  // указатель на динамический массив
	int npointers;    // число указателей в динамическом массиве 
	int i;


	fp = fopen("test.txt", "rt"); // открыть файл для чтения
	if (fp == NULL)
		return;    // ошибка при открытии файла

	lines_ptr = (char**)calloc(NLINES, sizeof(char*)); //вовзвращает указатель на место в памяти или NULL  в случае ошибки
	for (i = 0; i < NLINES; i++)
	{
		lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));
	}
	npointers = NLINES;




	while (!feof(fp))
	{
		char line[MAXLEN];
		char *ptr = fgets(line, MAXLEN, fp); // чтение строки   
		int len;

		if (ptr == NULL)
			break; // файл исчерпан 
				   // определить длину строки 

		if (nlines == npointers)
		{
			// динамический массив исчерпан   
			npointers += NLINES;// увеличить число указателей в массиве 

								// перезаказать память для массива указателей     
			lines_ptr = (char**)realloc(npointers, sizeof(char*));
			for (i = NLINES; i < npointers; i++)
			{
				lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));
			}

			// обнулить новую часть массива указателе   
			memset(&lines_ptr[nlines], 0, MAXLEN * sizeof(char*));
		}

		//lines_ptr[nlines] = (char*)malloc(len + 1);// заказать в  памяти   место для строки  плюс один байт     
		strcpy(lines_ptr[nlines], line); // сохранить строку в  динамическом массиве, копирует line  в lines_ptr[nlines]
		nlines++;
	}
	fclose(fp);

	out_interface(lines_ptr, npointers);

	if (lines_ptr != NULL)
	{
		for (i = 0; i < npointers; i++)
		{
			free(lines_ptr[i]);
		}
		free(lines_ptr);
	}
	getchar();
	system("pause");
}

void out_interface(char **lines, int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (strstr(lines[i], ")") && !strstr(lines[i], ");") && !strstr(lines[i], ";") && !strstr(lines[i], "for")
			&& !strstr(lines[i], "while") && !strstr(lines[i], "if") && !strstr(lines[i], "switch"))
			printf("%s\n", lines[i]);
}