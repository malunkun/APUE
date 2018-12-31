#include <stdio.h>
#include <stdlib.h>
int valimag = 2;
typedef struct Node
{
	int val;
	struct Node *next;
}*PtrToNode;
typedef PtrToNode List;
void create_link(List head,List tail,int n)
{
	printf("start the create_link() now!\n");
	List p;
	printf("list tail,p!\n");
	for(int i=1;i<n;i++)
	{
		p = (List)malloc(sizeof(struct Node));
		printf("the address for p is:%p!\n",p);
		if(!p)
		{
			printf("malloc fail!\n");
			exit(1);
		}
		head->next = p;
		p->next    = tail;
		tail->next = head;
		p->val     = valimag;
		valimag ++ ;
		printf("create list%d successful!\n",(valimag-1));
	}
}
void print_link(List head,int m)
{
	List beforep;
	beforep = head;
	for(int i=1;i<m;i++)
	{
		beforep = beforep->next;
		if (beforep == beforep->next)
		{
			break;
		}
	}
	printf("NO.%d get out!\n",beforep->val);
}
int main ()
{
	List head = (List)malloc(sizeof(struct Node));
	head->next = NULL;
	head->val  = 1;
	List tail  =(List)malloc(sizeof(struct Node));
	create_link(head,tail,10);
	printf("head:%d!\n",head->val);
	print_link(head,4);
	return 0;
}
