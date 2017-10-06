#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BOOL char
#define TRUE 1
#define FALSE 0
#define FSTRLEN 100
#define ELLEN 10


/* FSTRLEN represents f(x) string length */

/* describe stack by Single Linked List */
typedef struct TNodes {
	char val;
	struct TNodes* lnk;
} TNode;


void StackInit(TNode** top)
{
	*top = NULL;
}

void Push(TNode** top, char val)
{
	TNode* newNode = (TNode *)malloc(sizeof(TNode));
	newNode->val = val;
	newNode->lnk = *top;
	*top = newNode;
}

char Pop(TNode** top) {
	TNode* p;
	char popValue;
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



int Priority(char c)
{
	switch (c) {
	case '^':
		return 3;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case '+':
	case '-':
		return 1;
		break;
	case '(':
		return 0;
		break;
	default:
		return -1;
		break;
	}
}

BOOL IsValid(char* infix, char* validChars)
{
	char* opt = "+-*/^";
	int n = strlen(infix);
	int i;
	int soDauNgoacMo = 0, soDauNgoacDong = 0;

	for (i = 0; i < n - 1; i++)
	{
		if ((strchr(opt, *(infix + i)) && (*(infix + i + 1) == ')')) ||
			((*(infix + i) == '(') && strchr(opt, *(infix + i + 1))) ||
			(*(infix + i) == 'x' && *(infix + i + 1) == 'x'))
		{
			return FALSE;
		}

	}

	for (i = 0; i < n; i++)
	{

		if (!strchr(validChars, *(infix + i)))
		{
			return FALSE;
		}
	}

	for (i = 0; i < n; i++)
	{
		if (*(infix + i) == '(')
		{
			soDauNgoacMo++;
		}
		if (*(infix + i) == ')')
		{
			soDauNgoacDong++;
		}
	}
	if (soDauNgoacMo != soDauNgoacDong)
	{
		return FALSE;
	}

	return TRUE;

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

void Char2String(char subject[], char c)
{
	char buf[2] = { 0 };
	buf[1] = '\0';
	buf[0] = c;

	strcpy(subject, buf);
}

void Refine(char* infix, const char* opt)
{
	int i;
	int n;
	strcat(infix, " ");
	n = strlen(infix);
	for (i = n - 2; i >= 0; i--)
	{
		if (strchr(opt, infix[i]) || strchr(opt, infix[i + 1]))
		{
			append(infix, " ", i + 1);
		}
	}

}

char GetStackTop(TNode** top) {
	return (*top)->val;
}

void Process(char temp[], char rpn[], TNode** top)
{
	int len;
	char c = temp[0];
	char temp2[2];
	char x;
	switch (c) {
	case '(':
		Push(top, c);
		break;
	case ')':
		do {
			x = Pop(top);
			if (x != '(') {
				Char2String(temp2, x);
				strcat(rpn, temp2);

				Char2String(temp2, ' ');
				strcat(rpn, temp2);
			}
		} while (x != '(');
		break;
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		while ((*top) && Priority(c) <= Priority(GetStackTop(top))) {

			Char2String(temp2, Pop(top));
			strcat(rpn, temp2);
			Char2String(temp2, ' ');
			strcat(rpn, temp2);
		}
		Push(top, c);
		break;
	default:
		len = strlen(rpn);
		if (len > 0 && rpn[len - 1] != ' ') {
			Char2String(temp2, ' ');
			strcat(rpn, temp2);
		}
		strcat(rpn, temp);
	}

}

int main()
{
	char* validCharacters = "x0123456789()+-*/^";
	TNode* top;
	int x, len, i;
	char infix[FSTRLEN];
	char rpn[FSTRLEN] = { 0 };
	char temp[ELLEN] = { 0 };
	char temp2[2];
	FILE *f = fopen("rpn.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}


	do {
		printf("f(x) =\n");
		fgets(infix, FSTRLEN, stdin);
		len = strlen(infix);
		if (infix[len - 1] == '\n') {
			infix[len - 1] = '\0';
		}

	} while (!IsValid(infix, validCharacters));



	/*printf("Enter value of x: ");
	scanf("%d", &x);*/

	StackInit(&top); /* initialize empty stack */


	Refine(infix, "+-*/^()");
	len = strlen(infix);

	temp[0] = '\0';
	for (i = 0; i < len; i++) {
		if (infix[i] != ' ')
		{
			Char2String(temp2, infix[i]);

			strcat(temp, temp2);
		}
		else
		{
			/*printf("\n%d: %s\n", i, temp);*/
			Process(temp, rpn, &top);
			temp[0] = '\0';
		}
	}
	while (top) {
		Char2String(temp2, Pop(&top));
		strcat(rpn, temp2);
		Char2String(temp2, ' ');
		strcat(rpn, temp2);

	}






	fprintf(f, "%s\n", rpn);


	fclose(f);



	/*printf("\nYou entered: ");

	printf("%s",infix);*/

	/*printf("\nRPN     : %s", rpn);*/

	/*printf("Stack: %c", Pop(&top));*/

	return 0;
}
