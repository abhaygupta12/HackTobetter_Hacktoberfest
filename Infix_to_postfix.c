/*Conversion of infix to postfix*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string.h>
char infix_st[20], postfix_st[20];
int top;
int stack[20];
int pop ();
int pre (char symbol);
int isempty ();
void infix_to_postfix ();
int check_space (char symbol);
void push (long int symbol);
int main ()
{
int C, L;
char temp;
top = -1;
scanf ("%s", infix_st);
infix_to_postfix ();
printf ("%s\n", postfix_st);
return 0;
}

void infix_to_postfix ()
{

unsigned int C, temp = 0;

char next;

char symbol;

for (C = 0; C < strlen (infix_st); C++)

{

symbol = infix_st[C];

if (!check_space (symbol))

{

switch (symbol)

{

case '(':
push (symbol);

break;

case ')':

while ((next = pop ()) != '(')

{

postfix_st[temp++] = next;

}

break;

case '+':

case '-':

case '*':

case '/':

case '%':

case '^':

while (!isempty () && pre (stack[top]) >= pre (symbol))

postfix_st[temp++] = pop ();

push (symbol);

break;

default:

postfix_st[temp++] = symbol;

}

}

}

while (!isempty ())

{

postfix_st[temp++] = pop ();

}

postfix_st[temp] = '\0';

}

int pre (char symbol)
{

switch (symbol)

{

case '(':
return 0;

case '+':

case '-':

return 1;

case '*':

case '/':

case '%':

return 2;

case '^':

return 3;

default:

return 0;

}

}

int check_space (char symbol)
{

if (symbol == '\t' || symbol == ' ')

{

return 1;

}

else

{

return 0;

}

}

void push (long int symbol)
{

if (top > 20)

{

exit (1);

}

top = top + 1;

stack[top] = symbol;

}

int isempty ()
{

if (top == -1)

{

return 1;

}

else

{

return 0;

}

}

int pop ()
{

if (isempty ())

{

exit (1);

}

return (stack[top--]);

}
