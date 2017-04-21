#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define X 10
#define Y 10
#define N 20
#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define ANY -1

#define MAXSIZE 9999

int v[9999999]={0}, sconfig[X]={1};
int limit, n, finished=0, count, x, run=0;
int gs[N]={0, 7, 3, 1, 2, 4}, moves[4]={1, 2, -1, -2};//{0, 4, 3, 1, 6, 2} wrong solution scenario

struct node
{
	int *state;
    int stack, move, h1, h2, h;//h1=previous moves, h2=dif(x)+abs(dif(y)) 
    struct node *next, *parent;
}*head;

struct stack
{
	int mv[MAXSIZE];
    int stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;
STACK s;
 
void push (int crate, int move)
{
    int num;
    if (s.top == (MAXSIZE - 1))
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
        s.top = s.top + 1;
        s.stk[s.top] = crate;
        s.mv[s.top]= move;
    }
    return;
}

int getCost(){
	int i, cost=0;
	for(i=1; i<=s.top;i++){
		cost+=(1+abs(s.mv[i]));
	}
	return cost;
}
 
int cnt = 0;

int * duplicateArray(int const * src, size_t len){
   int * p = malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}

int canMove(int st[N], int p){//returns false if there is a tile in postition p
	int i;
	for(i=0; i<n; i++){
		if(st[i]==p)return 0;
	} 
	return 1;
}

int hashfunc(int s[N]){
	int i, z=0;
	for (i = 0; i < n; ++i)
	{	
		z+=(s[i]*(int)pow(10,i));
	}
	return z;
}

int hasBeenVisited(int s[N]){//returns false if state hasn't been visited
	return v[hashfunc(s)];
}

void markAsVisited(int s[N]){
	v[hashfunc(s)]=1;
	return;
}

void append(int st[N], int pile, int step, struct node *p, int h1, int h2)
{
    struct node *temp,*right;
    temp= (struct node *)malloc(sizeof(struct node));
    temp->state=duplicateArray(st, N);
		    	temp->stack=pile;
		    	temp->move=step;
		    	temp->parent=p;
		    	temp->h1=h1;
		    	temp->h2=h2;
		    	temp->h=h1+h2;
    right=(struct node *)head;
    while(right->next != NULL)
    right=right->next;
    right->next =temp;
    right=temp;
    right->next=NULL;
}
 
void add(int st[N], int pile, int step, struct node *p, int h1, int h2)
{
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->state=duplicateArray(st, N);
		    	temp->stack=pile;
		    	temp->move=step;
		    	temp->parent=p;
		    	temp->h1=h1;
		    	temp->h2=h2;
		    	temp->h=h1+h2;
    if (head== NULL)
    {
    head=temp;
    head->next=NULL;
    }
    else
    {
    temp->next=head;
    head=temp;
    }
}
void addafter(int st[N], int pile, int step, struct node *p, int h1, int h2, int loc)
{
	// printf("%i\n", loc);
    int i;
    struct node *temp,*left,*right;
    right=head;
    for(i=1;i<loc;i++)
    {
    left=right;
    right=right->next;
    }
    temp=(struct node *)malloc(sizeof(struct node));

    temp->state=duplicateArray(st, N);
	temp->stack=pile;
	temp->move=step;
	temp->parent=p;
	temp->h1=h1;
	temp->h2=h2;
	temp->h=h1+h2;

    left->next=temp;
    left=temp;
    left->next=right;
    return;
}

int countf()
{
    struct node *n;
    int c=0;
    n=head;
    while(n!=NULL)
    {
    n=n->next;
    c++;
    }
    return c;
}

void addNode(int st[N], int pile, int step, struct node *p, int h1, int h2)
{
    int c=0;
    struct node *temp;
    temp=head;
    if(temp==NULL)
    {
    add(st, pile, step, p, h1, h2);
    }
    else
    {
    while(temp!=NULL)
    {
        if(temp->h<=h1+h2)
        c++;
        temp=temp->next;
    }
    if(c==0)
        add(st, pile, step, p, h1, h2);
    else if(c<countf())
        addafter(st, pile, step, p, h1, h2, ++c);
    else
        append(st, pile, step, p, h1, h2);
    }
}

void validate(int s[N]){
	int i;
	for(i=0; i<n; i++){
		if(((s[i]!=gs[i]) && (gs[i]!=ANY))||((gs[i]==ANY) && (sconfig[i%x]==1))){
			return;
		}
	}
	finished=1;
	// printf("FINISHED\n");
	return;
}

void getSolution(struct node *q){
	if(q->parent){
		push(q->stack, q->move);
		getSolution(q->parent);
	}
}

void  displayQueue(struct node *r)
{
    r=head;
    if(r==NULL)
    {
    return;
    }
    while(r!=NULL)
    {
    printf("%d ",r->h);
    r=r->next;
    }
    printf("\n");
}

int isBlocking(int p){
	int i;
	for(i=0; i<n; i++){
		if(gs[i]==p)return 1;
	}
	return 0;
}

void removeNode(int hash)
{
    struct node *temp, *prev;
    temp=head;
    while(temp!=NULL)
    {
    if(hashfunc(temp->state)==hash)
    {
        if(temp==head)
        {
        head=temp->next;
        return;
        }
        else
        {
        prev->next=temp->next;
        return;
        }
    }
    else
    {
        prev=temp;
        temp= temp->next;
    }
    }
    return;
}

int getH2(int st[N]){
	int h2=0, i, aux;
	for(i=0; i<n; i++){
		if(gs[i]!=ANY){
			h2+=abs((gs[i]%x)-(st[i]%x));
		}
		else if(isBlocking(st[i])) h2+=2;
	}

	return h2;
}

void aStar(struct node *q){
	// printf("aStar h=%i h1=%i h2=%i\n", q->h, q->h1, q->h2);
	run++;
	validate(q->state);
	if(!finished){
		int i, j, k, h2=0, h1=0;
		int *s2;
		for(i=0; i<n; i++){
			if(canMove(q->state, q->state[i]+x)){//if nothing is on top
				for(k=0; k<4; k++){
					s2=duplicateArray(q->state, N);//get array copy
					if(q->state[i]%x+moves[k]<x && q->state[i]%x+moves[k]>=0){
						for(j=0; j<limit; j++){
							if(canMove(q->state, (q->state[i]%x+moves[k])+(x*j))){
								s2[i]=q->state[i]%x+moves[k]+(x*j);
								if(!hasBeenVisited(s2)){
									markAsVisited(s2);
									h2=getH2(s2);
									h1=q->h1+abs(moves[k])+1;
									if ((h1+h2)<q->h)
									{
										printf("Warning %i inserted %i\n", q->h, h1+h2);
									}
									addNode(s2, q->state[i]%x, moves[k], q, h1, h2);
								}
								break;
							}
						}	
					}
				}
			}
		}
		removeNode(hashfunc(q->state));
		if(head)aStar(head);
	}		
	else{
		getSolution(q);
	}
}

void display ()
{
	// printf("A* Solution Found in %i steps.\n", run);
    int i;
    if (s.top == -1)
    {
        return;
    }
    else
    {
        for (i = s.top; i > 0; i--)
        {
            printf ("(%d, %d)", s.stk[i], s.mv[i]+s.stk[i]);
            if (i>1)printf("; ");
        }
    }
    printf ("\n");
}

int main(){
	n=6;
	struct node *no;
    head=NULL;
	int initialState[N]={2, 4, 3, 1, 5, 0, 6};
	x=3; limit=3, count=0;
	markAsVisited(initialState);
	int h2=0;
	addNode(initialState, 0, 0, NULL, 0, 0);
	aStar(head);
	if(!finished)printf("No solution found\n");
	else{
	printf("%i\n", getCost());
	 display();
	}
}