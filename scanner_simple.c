#include <stdio.h>
#include <string.h>
#include <time.h>


#define MAX_NUM 16
#define MAX_KEYWORDS_NUM 16

#define DIGIT 1
#define ID 2
#define KEYWORDS 3


int rowNumber = 1;
char ch;
char token[MAX_NUM];
FILE *fp;

const char keywords[MAX_KEYWORDS_NUM][8] = {"main", "if", "else", "while", "int", "void"};

#if 0
void testCode(void)
{
    int a,b,x,y,max;
    a = 10;
    b = 10;
    while( a+2 > b+1)
    {
        a = (a-1)*(a+1);
        b = a + a*b;
    };
    if(x > y) max = x;
    else max =y;
}
#endif

int initToken(void)
{
	int loop;
	for(loop = 0; loop < MAX_NUM; loop++)
	{
		token[loop] = NULL;
	}
	return 0;
}

int IsAlpha(char ch)
{
	int result = 0;
	if((ch >= 'a' && ch <= 'z' ) || (ch >= 'A' && ch <= 'Z'))
		result = 1;
	return result;
}

int IsDigit(char ch)
{
	int result = 0;
	if(ch >= '0' && ch <= '9')
		result = 1;
	return result;
}

int IsSpace(char ch)
{
	int result = 0;
	if(ch == '\n')
		rowNumber++;
	if(ch == ' ' || ch == '\t' || ch == '\n')
		result = 1;
	return result;
}


int judgeChar()
{
	int charNum = 0;
	int loop;
	int value = 100;

	while(IsSpace(ch))
	{
		ch = getc(fp);
	}

	if(IsAlpha(ch))
	{
		while(IsAlpha(ch) || IsDigit(ch))
		{
			token[charNum++] = ch;
			ch = getc(fp);
		}
		token[charNum++] = '\0';
		for(loop = 0; loop < MAX_KEYWORDS_NUM; loop++)
		{
			if(0 == strcmp(token, keywords[loop]))
				return KEYWORDS;
		}
		return ID;
	}
	else if(IsDigit(ch))
	{
		while(IsDigit(ch))
		{
			token[charNum++] = ch;
			ch = getc(fp);
		}
		token[charNum++] = '\0';
		return DIGIT;
	}
	else
	{
		token[charNum++] = ch;
		switch(ch)
		{
			case '(':
				value = 16;
				ch = getc(fp);
				break;
			case ')':
				value = 17;
				ch = getc(fp);
				break;
			case '{':
				value = 33;
				ch = getc(fp);
				break;
			case '}':
				value = 34;
				ch = getc(fp);
				break;
			case ';':
				value = 27;
				ch = getc(fp);
				break;
			case ',':
				value = 35;
				ch = getc(fp);
				break;
			case EOF:
				value = -1;
				ch = getc(fp);
				break;
			case '+':
				ch = getc(fp);
				if(ch == '+')
				{
					token[charNum++] = ch;
					value = 29;
				}
				else
					value = 18;
				break;
			case '-':
				ch = getc(fp);
				if(ch == '-')
				{
					token[charNum++] = ch;
					value = 30;
				}
				else
					value = 18;
				break;
			case '*':
				value = 20;
				ch = getc(fp);
				break;
			case '/':
				value = 21;
				ch = getc(fp);
				break;
			case '=':
				ch = getc(fp);
				if(ch == '=')
				{
					token[charNum++] = ch;
					value = 42;
				}
				else
					value = 22;
				break;
			case '>':
				ch = getc(fp);
				if(ch == '=')
				{
					token[charNum++] = ch;
					value = 24;
				}
				else
					value = 23;
				break;
			case '<':
				ch = getc(fp);
				if(ch == '=')
				{
					token[charNum++] = ch;
					value = 26;
				}
				else
					value = 25;
				break;
			default:
				value = 100;
				ch = getc(fp);
				break;
		}
		token[charNum++] = '\0';
		return value;
	}
}


int main(void)
{
	int value;
	clock_t start, finish;

	fp = fopen("test.txt","r");
	ch = getc(fp);
	initToken();
	start = clock();
	do{
		value = judgeChar();
		if(100 == value)
		{
			printf("error happened in %d line!\n", rowNumber);
			break;
		}
		printf("<%d, %s>,\n",value, token);
	}
	while(-1 != value);
	finish = clock() - start;
	printf("time = %d ms\n", finish);
	fclose(fp);
	printf("hello world!");
	return 0;
}
