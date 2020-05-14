#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 10
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);
void printop(void);
void duplicate_top(void);
void swap_2_top(void);
void clr_stack(void);

int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF)
	{
		switch (type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n",pop());
				break;
			default:
				printf("error: unknown command %s\n",s);
				break;
			case '~': //print the top elements of the stack
				printop();
				break;
			case '@': //duplicate the top elements of the stack
				duplicate_top();
				break;
			case '#': //swap the top two elements of the stack
				swap_2_top();
				break;
			case '$': //clear the stack
				clr_stack();
				break;
		}
	}
	return 0;
}

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n",f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

void printop(void)
{
	if (sp >0)
		printf("Top element of the stack is:%f\n",val[sp-1]);
	else
		printf("Nothing in the stack\n");
}

void duplicate_top(void)
{
	int current_index;
	
	if (sp > 0)
	{
		current_index = sp - 1;
		val[sp++] = val[current_index];
	}
	else
		printf("Nothing in the stack\n");
}

void swap_2_top(void)
{
	double mid;
	
	if( sp >= 2)
	{
		mid = val[sp-1];
		val[sp-1] = val[sp-2];
		val[sp-2] = mid;
	}
	else
		printf("No enough elements in the stack\n");
}

void clr_stack(void)
{
	while(sp > 0)
		val[--sp] = '\0';
}

int getop(char s[])
{
	int i,c;
	
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	i = 0;
	if (isdigit(c))
		while(isdigit(s[++i] = c =getch()))
			;
	if (c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void)
{
	return (bufp > 0)? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
