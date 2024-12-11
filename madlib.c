//Author: Group 6; Alec Thai, Ammon Dold, Sheridan Nguyen
//Date: 11.26.24 -- 10.12.2024
//Purpose: Final project: Madlibs

#include <stdio.h>
#define MAXROW 100
#define MAXLEN 100
#define MADFILE "madlib2.txt"

int
ReadLib(FILE*);

void
_paragraph(char[][MAXLEN], int);

void
_punctuate(char[][MAXLEN], int);

void
madLib(char[][MAXLEN], int, FILE*);

void
_readinput(char[][MAXLEN], int);

int
main()
{
	FILE *madlibPTR;
	FILE *readlibPTR;
	
	readlibPTR = fopen(MADFILE, "r");
	madlibPTR = fopen(MADFILE, "r");
	
	if(madlibPTR == NULL || readlibPTR == NULL)
	{
		printf("Could not find file.\n");
		return 1;
	}
	
	int rows = ReadLib(readlibPTR);
	if(rows > MAXROW)
	{ rows = MAXROW; }
	fclose(readlibPTR);
	
	char lib_stor[rows][MAXLEN];

	//store	
	madLib(lib_stor, rows, madlibPTR);
	fclose(madlibPTR);
	
	//read and recieve input
	_readinput(lib_stor, rows);
	
	//display
	for(int ind = 0; ind < rows; ind++)
	{
		printf(lib_stor[ind]);
		_punctuate(lib_stor, ind);
	}
	printf("\n");
	
	return 0;
}

int
ReadLib(FILE *readlibPTR) //count number of lines
{
	int counter = 0;
	char temp[MAXLEN];
	while(fgets(temp, MAXLEN, readlibPTR))
	{ counter++; }
	
	return counter - 1;
}

void
_paragraph(char lib_stor[][MAXLEN], int rows) //delete endlines
{
	for(int ind = 0; ind < rows; ind++)
	{
		for(int jnd = 0; lib_stor[ind][jnd] != '\0'; jnd++)
		{
			if(lib_stor[ind][jnd] == '\n')
			{ lib_stor[ind][jnd] = '\0'; }
		}
	}
}

void
_punctuate(char lib_stor[][MAXLEN], int rows) //delete space before punctuation
{
	switch(lib_stor[rows + 1][0])
	{
		case '.':
		case ',':
		case ';':
		case '!':
		case '?':
		break;
		default: printf(" ");
	}
}

void
madLib(char lib_stor[][MAXLEN], int rows, FILE* madlibPTR) //store txt into 2d array
{
	int ind = 0;
	char temp[MAXLEN];
	
	while(fgets(temp, MAXLEN, madlibPTR))
	{
			int jnd = 0;
			while(temp[jnd] != '\0' && ind < rows)
		{
			lib_stor[ind][jnd] = temp[jnd];
			jnd++;
		}
		lib_stor[ind][jnd] = '\0';
		ind++;
	}
	_paragraph(lib_stor, rows);
}

void
_readinput(char lib_stor[][MAXLEN], int rows) //input where necessary
{	
	for(int ind = 0; ind < rows-1; ind++)
	{
		if (lib_stor[ind][1] == '\0')
		{
			switch(lib_stor[ind][0])
			{
				case 'A': printf("Please enter an adjective: ");
				break;
				case 'N': printf("Please enter a noun: ");
				break;
				case 'V': printf("Please enter a verb: ");
			}
			scanf("%s", lib_stor[ind]);
		}
	}
}