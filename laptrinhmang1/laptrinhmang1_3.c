#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BOOL char
#define TRUE 1
#define FALSE 0
#define FSTRLEN 100
#define ELLEN 10


/* FSTRLEN represents f(x) string length */


/* describe stack by Single Linked List */
typedef struct TNodes {
	double val;
	struct TNodes* lnk;
} TNode;


void StackInit(TNode** top)
{
	*top = NULL;
}


void Push(TNode** top, double val)
{
	TNode* newNode = (TNode *)malloc(sizeof(TNode));
	newNode->val = val;
	newNode->lnk = *top;
	*top = newNode;
}

double Pop(TNode** top) {
	TNode* p;
	double popValue;
	if (!*top) {
		printf("Stack is empty.\n");
	}
	else
	{
		popValue = (*top)->val;
		p = (*top)->lnk;
		free(*top);
		*top = p;
	}
	return popValue;
}


void append(char subject[], const char insert[], int pos) {
	char buf[100] = { 0 };
	int len;
	strncpy(buf, subject, pos);
	len = strlen(buf);
	strcpy(buf + len, insert);
	len += strlen(insert);
	strcpy(buf + len, subject + pos);

	strcpy(subject, buf);

}


void del(char subject[], int pos) {
	char buf[100] = { 0 };
	int len;
	strncpy(buf, subject, pos);
	len = strlen(buf);

	strcpy(buf + len, subject + pos + 1);

	strcpy(subject, buf);
}


void Char2String(char subject[], char c)
{
	char buf[2] = { 0 };
	buf[1] = '\0';
	buf[0] = c;

	strcpy(subject, buf);
}




void Refine(char* pn, const char* opt)
{
	int i;
	int n;
	append(pn, " ", 0);
	n = strlen(pn);
	if (pn[n - 1] == ' ') {
		del(pn, n - 1);
	}
	n = strlen(pn);

	for (i = n - 2; i >= 0; i--)
	{

		if (pn[i] == ' ' && pn[i + 1] == ' ')
		{

			del(pn, i + 1);
		}
	}

}


double GetStackTop(TNode** top) {
	return (*top)->val;
}


/* reverse the given null-terminated string in place*/
void inplace_reverse(char * str)
{
	if (str)
	{
		char * end = str + strlen(str) - 1;

		/*
		 * swap the values in the two given variables
		 * XXX: fails when a and b refer to same memory location
		 */
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

		 /*
		  * walk inwards from both ends of the string,
		  * swapping until we get to the middle
		  */
		while (str < end)
		{
			XOR_SWAP(*str, *end);
			str++;
			end--;
		}
#   undef XOR_SWAP
	}
}

void Process(char temp[], TNode** top) {
	char c = temp[0];
	char opt[] = "+-*/^";
	double x, y;

	inplace_reverse(temp);

	if (strchr(opt, c)) {
		x = Pop(top);
		y = Pop(top);
	}

	switch (c) {
	case '+':
		Push(top, x + y);
		break;
	case '-':
		Push(top, x - y);
		break;
	case '*':
		Push(top, x*y);
		break;
	case '/':
		Push(top, x / y);
		break;
	case '^':
		Push(top, pow(x, y));
		break;

	default:
		sscanf(temp, "%lf", &x);
		Push(top, x);
		break;
	}
}

int main()
{
	TNode* top;
	int x, len, i;
	char pn[FSTRLEN] = { 0 };
	char temp[ELLEN] = { 0 };
	char temp2[2];
	FILE *f = fopen("pn.txt", "r");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}


	fgets(pn, FSTRLEN, f);
	len = strlen(pn);

	printf("Enter value of x: ");
	scanf("%d", &x);

	StackInit(&top); /* initialize empty stack */


	Refine(pn, "+-*/^()");
	len = strlen(pn);

	temp[0] = '\0';
	for (i = len - 1; i >= 0; i--) {
		if (pn[i] != ' ')
		{
			Char2String(temp2, pn[i]);

			strcat(temp, temp2);
		}
		else
		{
			/*printf("\n%d: %s\n", i, temp);*/
			Process(temp, &top);
			temp[0] = '\0';
		}
	}
	if (top) {
		printf("Prefix Expression \"%s\"", pn);
		printf("\n=%.2lf", Pop(&top));
	}
	else {
		printf("OOPS!");
		exit(1);
	}


	return 0;
}
