#include<stdio.h>
#include<stdlib.h>
struct stack
{
	int x,y,i; struct stack *next;
};
struct item
{
	int x,y,i;
};
void tostack(struct stack **s, struct item *t)
{
	struct stack *tmp = (struct stack*)malloc(sizeof(struct stack));
	tmp->x = t->x; tmp->y = t->y; tmp->i = t->i; tmp->next = (*s); (*s) = tmp;
}
void pop(struct stack **s, struct item **t)
{
	if ((*s) != NULL)
	{
		if(*t == NULL) (*t) = (struct item*)malloc(sizeof(struct item));
		(*t)->x = (*s)->x; 	(*t)->y = (*s)->y; 	(*t)->i = (*s)->i;
		struct stack *tmp = (*s); (*s) = (*s)->next; free(tmp);
	}
}
int main()
{
	struct stack *ms, *tmp; ms = NULL; tmp = NULL;
	struct item *item, *item2, *item3; item = (struct item*)malloc(sizeof(struct item)); item->i = 0;
	item2 = (struct item*)malloc(sizeof(struct item)); item2->i = 0;
	item3 = (struct item*)malloc(sizeof(struct item)); item3->i = 0;
	int x,y,px,py,fx,fy,M,N,notfound; notfound = 1;
	char c;
	x = 0; y = 0; fx = 7; fy = 2; M = 8; N = 8; int mat[M][N]; px = 0; py = 0;
	for(px = 0; px < M; px++)
	{
		for(py = 0; py < N; py++)
		{
			printf("mat[%d,%d]\n",px,py);
			scanf("%d%c",&mat[px][py],&c);
		}
	} px = x; py = y;
	while (notfound)
	{
		if(((x-1)>=0) && ((x-1) != px) && (mat[x-1][y] != 1))
		{
			if(((y+1)<M) && ((y+1) != px) && (mat[x][y+1] != 1)) item->i = 1;
			if(((x+1)<M) && ((x+1) != px) && (mat[x+1][y] != 1)) item->i = 1;
			if(((y-1)>=0) && ((y-1) != py) && (mat[x][y-1] != 1)) item->i = 1;
			px = x; py = y; item->x = x; item->y = y; tostack(&ms, item); x--;
		}
		else if(((y+1)<M) && ((y+1) != py) && (mat[x][y+1] != 1))
		{
			if(((x+1)<M) && ((x+1) != px) && (mat[x+1][y] != 1)) item->i = 1;
			if(((y-1)>=0) && ((y-1) != py) && (mat[x][y-1] != 1)) item->i = 1;
			px = x; py = y; item->x = x; item->y = y; tostack(&ms, item); y++;
		}
		else if(((x+1)<M) && ((x+1) != px) && (mat[x+1][y] != 1))
		{
			if(((y-1)>=0) && ((y-1) != py) && (mat[x][y-1] != 1)) item->i = 1;
			px = x; py = y; item->x = x; item->y = y; tostack(&ms, item); x++;
		}
		else if(((y-1)>=0) && ((y-1) != py) && (mat[x][y-1] != 1))
		{
			px = x; py = y; item->x = x; item->y = y; tostack(&ms, item);  y--;
		}
		else
		{
			item->x = x; item->y = y; tostack(&ms, item);
			pop(&ms,&item);
			while((item->i != 1) && (ms != NULL))
			{
				item2->x = item->x; item2->y = item->y; item2->i = item->i;
				pop(&ms, &item);
			}
			pop(&ms, &item3); tostack(&ms, item3); item->i = 0;
			x = item->x; y = item->y; px = item3->x; py = item3->y;
			if(((x-1)>=0) && ((x-1) != px) && (mat[x-1][y] != 1) && ((x-1) != item2->x))
			{
				px = x; py = y; item->x = x; item->y = y; tostack(&ms, item); x--;
			}
			if(((y+1)<M) && ((y+1) != py) && (mat[x][y+1] != 1) && ((y+1) != item2->y))
			{
				px = x; py = y; item->x = x; item->y = y; tostack(&ms, item); y++;
			}
			if(((x+1)<M) && ((x+1) != px) && (mat[x+1][y] != 1) && ((x+1) != item2->x))
			{
				px = x; py = y; item->x = x; item->y = y; tostack(&ms, item); x++;
			}
			if(((y-1)>=0) && ((y-1) != py) && (mat[x][y-1] != 1) && ((y-1) != item2->y))
			{
				px = x; py = y; item->x = x; item->y = y; tostack(&ms, item); y--;
			}
		}
		if ((x == fx) && (y == fy))
		{
			notfound = 0;
			item->x = x; item->y = y;
			tostack(&ms, item);
		}
		item->i = 0;
	}
	printf("the path:\n");
	tmp = ms;
	while(tmp != NULL)
	{
		printf("(%d %d)<-",tmp->x,tmp->y);
		tmp = tmp->next;
	}
	return 0;
}
