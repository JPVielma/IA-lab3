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

int v[9999999]={0}, sconfig[X]={1};;
int limit, n, finished=0, count, x, run=0;
int gs[N]={0, 7, 3, 1, 2, 4}, moves[4]={1, 2, -1, -2};

struct node
{
	int *state;
    int stack, move;
    struct node *ptr, *parent;
}*front,*rear,*temp,*front1;

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

/* Create an empty queue */
void create()
{
    front = rear = NULL;
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

void addNode(int st[N], int pile, int step, struct node *p){
	if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->state=duplicateArray(st, N);
    	rear->stack=pile;
    	rear->move=step;
    	rear->parent=p;
        front = rear;
    }
    else
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        temp->state=duplicateArray(st, N);
    	temp->stack=pile;
    	temp->move=step;
    	temp->parent=p;
        temp->ptr = NULL;
 
        rear = temp;
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
	if(q->move!=0){
		push(q->stack, q->move);
		getSolution(q->parent);
	}
}

void bfs(struct node *q){
	run++;
	validate(q->state);
	if(!finished){
		int i, j, k;
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
									addNode(s2, q->state[i]%x, moves[k], q);
								}
								break;
							}
						}	
					}
				}
			}
		}
		if(q->ptr)bfs(q->ptr);
	}	
	else{
		getSolution(q);
	}
}


void display ()
{
	// printf("BFS Solution Found in %i steps.\n", run);
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
	int initialState[N]={1, 3, 6, 0, 2, 11, 4, 9};
	n=6; x=3; limit=3, count=0;
	markAsVisited(initialState);
	create();
	addNode(initialState, 0, 0, NULL);
	bfs(front);
	if(!finished)printf("No solution found\n");
	else{
	printf("%i\n", getCost());
	 display();
	}
}