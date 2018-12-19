/******************************/
/*  Self-Reference Structure  */
/******************************/

#include <stdio.h>
#include <stdlib.h>

struct CELL {
		int		value;
		struct	CELL	*next;};

struct CELL  *head;

/*** prototype ***/
static struct CELL *node(void);

void main(void)
{
	int		i;
	struct	CELL	*p,	*pp;
	head = NULL;

	printf("Enter Non numeric Number if you want exit\n");

	/* Input Loop */
	while(1){
		printf("Enter Integer number ");
		if(scanf("%d",&i) ==1 ){ 
			p = node(); 
			p->value = i;
			p->next = head;
			head = p;
		  }
        else{
			break;
		}
	}

	printf("Linked List(Reverse) \n");
	for( p = head; p != NULL; p = p->next)
	{
		printf("Number=%d (node %p) \n",p->value,p->next);
    }

	for( p = head; p != NULL; p = pp)
	{
		pp = p->next;
		(void)free( (void *)p );
	}
}
struct CELL *node(void)
{
    struct CELL *p = (struct CELL *)malloc( sizeof(struct CELL));

    if( p== NULL)
    {
        fprintf(stderr,"\n Lack of memory!");
        exit(-1);
    }
    return p;
}

