#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>

#include <string.h>

#include <malloc.h>

#include <stdlib.h> 




#define MAXLEN 1000 // ìàêñèìàëüíàÿ äëèíà ñòðîêè 

#define NLINES 1000  // ìàêñèìàëüíîå ÷èñëî ñòðîê 



void out_interface(char**, int);



void main(void)

{

	FILE *fp;

	//char *first_word;

	int nlines = 0;//êîëè÷åñòâî ñòðîê â ôàéëå

	char **lines_ptr = NULL;  // óêàçàòåëü íà äèíàìè÷åñêèé ìàññèâ

	int npointers;    // ÷èñëî óêàçàòåëåé â äèíàìè÷åñêîì ìàññèâå 

	int i;





	fp = fopen("test.txt", "rt"); // îòêðûòü ôàéë äëÿ ÷òåíèÿ

	if (fp == NULL)

		return;    // îøèáêà ïðè îòêðûòèè ôàéëà



	lines_ptr = (char**)calloc(NLINES, sizeof(char*)); //âîâçâðàùàåò óêàçàòåëü íà ìåñòî â ïàìÿòè èëè NULL  â ñëó÷àå îøèáêè

	for (i = 0; i < NLINES; i++)

	{

		lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));

	}

	npointers = NLINES;









	while (!feof(fp))

	{

		char line[MAXLEN];

		char *ptr = fgets(line, MAXLEN, fp); // ÷òåíèå ñòðîêè   

		int len;



		if (ptr == NULL)

			break; // ôàéë èñ÷åðïàí 

				   // îïðåäåëèòü äëèíó ñòðîêè 



		if (nlines == npointers)

		{

			// äèíàìè÷åñêèé ìàññèâ èñ÷åðïàí   

			npointers += NLINES;// óâåëè÷èòü ÷èñëî óêàçàòåëåé â ìàññèâå 



								// ïåðåçàêàçàòü ïàìÿòü äëÿ ìàññèâà óêàçàòåëåé     

			lines_ptr = (char**)realloc(npointers, sizeof(char*));

			for (i = NLINES; i < npointers; i++)

			{

				lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));

			}



			// îáíóëèòü íîâóþ ÷àñòü ìàññèâà óêàçàòåëå   

			memset(&lines_ptr[nlines], 0, MAXLEN * sizeof(char*));

		}



		//lines_ptr[nlines] = (char*)malloc(len + 1);// çàêàçàòü â  ïàìÿòè   ìåñòî äëÿ ñòðîêè  ïëþñ îäèí áàéò     

		strcpy(lines_ptr[nlines], line); // ñîõðàíèòü ñòðîêó â  äèíàìè÷åñêîì ìàññèâå, êîïèðóåò line  â lines_ptr[nlines]

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
	char *ptr;
	char line[100];
	for (i = 0; i < n; i++)
	{ 
		ptr = lines[i];
		if (strstr(lines[i], ")") && !strstr(lines[i], ");") && !strstr(lines[i], ";") && !strstr(lines[i], "for")

			&& !strstr(lines[i], "while") && !strstr(lines[i], "if") && !strstr(lines[i], "switch"))
		{
			
			int g = 0;
			int counter = 0;
			while (*ptr) 
			{
				if (*ptr == '(')
				{ 
					counter++; 
					line[g++] = *ptr++;
				}
				else if (*ptr == ')' )
			    {
				     	counter--;
						line[g++] = *ptr++;
						if (counter == 0) {
						line[g] = '\0';
						 break;
				    	}
				}
				else line[g++] = *ptr++;
			}
			
			line[g] = '\0';
			printf("%s\n", line);
		}
	}
}