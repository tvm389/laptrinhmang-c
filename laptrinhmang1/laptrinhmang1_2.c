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




typedef struct BLeafs {
	char val[ELLEN];
	struct BLeafs* lft;
	struct BLeafs* rgt;
} BLeaf;


/* describe stack by Single Linked List */
typedef struct TNodes {
	BLeaf* val;
	struct TNodes* lnk;
} TNode;


void BTreeInit(BLeaf** root) {
	*root = NULL;
}

void StackInit(TNode** top)
{
	*top = NULL;
}



void Push(TNode** top, BLeaf* val)
{
	TNode* newNode = (TNode *)malloc(sizeof(TNode));
	newNode->val = val;
	newNode->lnk = *top;
	*top = newNode;
}

BLeaf* Pop(TNode** top) {
	TNode* p;
	BLeaf* popValue;
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

void Refine(char* rpn, const char* opt)
{
	int i;
	int n;
	strcat(rpn, " ");
	n = strlen(rpn);
	for (i = n - 2; i >= 0; i--)
	{
		if (strchr(opt, rpn[i]) || strchr(opt, rpn[i + 1]))
		{
			append(rpn, " ", i + 1);
		}
	}
	n = strlen(rpn);
	for (i = n - 2; i >= 0; i--)
	{

		if (rpn[i] == ' ' && rpn[i + 1] == ' ')
		{

			del(rpn, i + 1);
		}
	}

}

BLeaf* GetStackTop(TNode** top) {
	return (*top)->val;
}


void Process(char temp[], TNode** top, int x)
{
	BLeaf* newLeaf = (BLeaf*)malloc(sizeof(BLeaf));
	char c = temp[0];
	char temp2[ELLEN] = { 0 };
	BLeaf* leaf_y;
	BLeaf* leaf_x;
	newLeaf->lft = NULL;
	newLeaf->rgt = NULL;
	if (c != 'x') {
		strcpy(newLeaf->val, temp);
	}
	else {
		sprintf(temp2, "%d", x);
		strcpy(newLeaf->val, temp2);
	}
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '^':
		leaf_y = Pop(top);
		leaf_x = Pop(top);
		newLeaf->lft = leaf_x;
		newLeaf->rgt = leaf_y;
		/* do not break here */
	default:
		Push(top, newLeaf);
		break;
	}

}

void InorderVisit(BLeaf* l, char infix[]) {
	char temp2[2];
	char opt[] = "+-*/^";
	if (l != NULL) {
		if (strchr(opt, l->val[0])) {
			Char2String(temp2, '(');
			strcat(infix, temp2);
		}

		InorderVisit(l->lft, infix);

		strcat(infix, l->val);
		Char2String(temp2, ' ');
		strcat(infix, temp2);

		InorderVisit(l->rgt, infix);

		if (strchr(opt, l->val[0])) {
			Char2String(temp2, ')');
			strcat(infix, temp2);
		}
	}
}


void PreorderVisit(BLeaf* l, char prefix[]) {
	char temp2[2];
	if (l != NULL) {

		strcat(prefix, l->val);
		Char2String(temp2, ' ');
		strcat(prefix, temp2);

		PreorderVisit(l->lft, prefix);
		PreorderVisit(l->rgt, prefix);
	}
}

double Calculate(BLeaf* l) {
	char opt[] = "+-*/^";
	double x, y;
	char c = l->val[0];
	if (!strchr(opt, c)) {
		sscanf(l->val, "%lf", &x);
		return x;
	}
	else {
		x = Calculate(l->lft);
		y = Calculate(l->rgt);
		switch (c) {
		case '+':
			return x + y;
			break;
		case '-':
			return x - y;
			break;
		case '*':
			return x*y;
			break;
		case '/':
			return x / y;
			break;
		case '^':
			return pow(x, y);
			break;
		default:
			printf("OOPS!");
			exit(1);
		}
	}
}


int main()
{
	TNode* top;
	int x, len, i;
	char rpn[FSTRLEN];
	char temp[ELLEN] = { 0 };
	char temp2[2];
	char infix[FSTRLEN + FSTRLEN] = { 0 }; /*added parentheses*/
	char prefix[FSTRLEN] = { 0 };
	double result;
	BLeaf* root;
	FILE *f = fopen("rpn.txt", "r");
	FILE *f2 = fopen("pn.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}



	fgets(rpn, FSTRLEN, f);
	len = strlen(rpn);
	if (rpn[len - 1] == '\n') {
		rpn[len - 1] = '\0';
	}
	len = strlen(rpn);



	printf("Enter value of x: ");
	scanf("%d", &x);

	StackInit(&top); /* initialize empty stack */
	BTreeInit(&root); /* initialize empty binary tree */


	Refine(rpn, "+-*/^()x");
	len = strlen(rpn);












	temp[0] = '\0';
	for (i = 0; i < len; i++) {
		if (rpn[i] != ' ')
		{
			Char2String(temp2, rpn[i]);

			strcat(temp, temp2);
		}
		else
		{
			printf("\n%d: %s\n", i, temp);
			Process(temp, &top, x);
			temp[0] = '\0';
		}
	}
	if (top) {
		root = Pop(&top);
	}

	InorderVisit(root, infix);
	PreorderVisit(root, prefix);

	fprintf(f2, prefix);
	close(f2);


	/*printf("\nYou entered: ");

	printf("\"%s\"",rpn);*/

	result = Calculate(root);
	printf("\n\n%s = %.2lf", infix, result);



	/*printf("Stack: %c", Pop(&top));*/


	close(f);
	return 0;
}
