//������� ������ ����������� �������, ����������� � ����� � ���������� �� ����� ��. 
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h> 

//#define YES 1
//#define NO 0

#define MAXLEN 1000 // ������������ ����� ������ 
#define NLINES 1000  // ������������ ����� ����� 

void out_interface(char**, int);

void main(void)
{
	FILE *fp;
	//char *first_word;
	int nlines = 0;//���������� ����� � �����
	char **lines_ptr = NULL;  // ��������� �� ������������ ������
	int npointers;    // ����� ���������� � ������������ ������� 
	int i;


	fp = fopen("test.txt", "rt"); // ������� ���� ��� ������
	if (fp == NULL)
		return;    // ������ ��� �������� �����

	lines_ptr = (char**)calloc(NLINES, sizeof(char*)); //����������� ��������� �� ����� � ������ ��� NULL  � ������ ������
	for (i = 0; i < NLINES; i++)
	{
		lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));
	}
	npointers = NLINES;




	while (!feof(fp))
	{
		char line[MAXLEN];
		char *ptr = fgets(line, MAXLEN, fp); // ������ ������   
		int len;

		if (ptr == NULL)
			break; // ���� �������� 
				   // ���������� ����� ������ 

		if (nlines == npointers)
		{
			// ������������ ������ ��������   
			npointers += NLINES;// ��������� ����� ���������� � ������� 

								// ������������ ������ ��� ������� ����������     
			lines_ptr = (char**)realloc(npointers, sizeof(char*));
			for (i = NLINES; i < npointers; i++)
			{
				lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));
			}

			// �������� ����� ����� ������� ���������   
			memset(&lines_ptr[nlines], 0, MAXLEN * sizeof(char*));
		}

		//lines_ptr[nlines] = (char*)malloc(len + 1);// �������� �  ������   ����� ��� ������  ���� ���� ����     
		strcpy(lines_ptr[nlines], line); // ��������� ������ �  ������������ �������, �������� line  � lines_ptr[nlines]
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