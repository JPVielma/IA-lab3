#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include <limits.h>

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

int hash[9999999]={0}, sconfig[X]={1};;
int limit, n, finished=0, count, x, run=0;
int gs[N]={0, 7, 3, 1, 2, 4}, moves[4]={1, 2, -1, -2};
 
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

void display ()
{
	// printf("DFS Solution Found in %i steps.\n", run);
    int i;
    if (s.top == -1)
    {
        return;
    }
    else
    {
        for (i = s.top; i >= 0; i--)
        {
        	printf ("(%d, %d)", s.stk[i], s.mv[i]+s.stk[i]);
            if (i>1)printf("; ");    
        }
    }
    printf ("\n");
}

int * duplicateArray(int const * src, size_t len){
   int * p = malloc(len * sizeof(int));
   memcpy(p, src, len * sizeof(int));
   return p;
}

int canMove(int st[N], int p){//returns false if there is a tile in postition p
	int i;
	for(i=0; i<n; i++){
		if(st[i]==p){
			return 0;
		}
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
	return hash[hashfunc(s)];
}

void markAsVisited(int s[N]){
	hash[hashfunc(s)]=1;
	return;
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

void dfs(int state[N]){
	run++;
	validate(state);
	if(!finished){
		int i, j, k;//i=crate iterator, k=moves iterator, j=height limit iterator
		int *s2;
		for(i=0; i<n; i++){
			if(canMove(state, state[i]+x)){//if nothing is on top
				for(k=0; k<4; k++){//iterate through possible actions
					s2=duplicateArray(state, N);//get array copy
					if(state[i]%x+moves[k]<x && state[i]%x+moves[k]>=0){//validate if movement is inside boundaries
						for(j=0; j<limit; j++){//iterate row heights
							if(canMove(state, (state[i]%x+moves[k])+(x*j))){//check if position is free
								s2[i]=state[i]%x+moves[k]+(x*j);
								if(!hasBeenVisited(s2)){
									markAsVisited(s2);
									dfs(s2);
									if (finished){
										push(state[i]%x, moves[k]);//store solution
										return;
									}
								}
								break;//stop iterating through different heights on same stack
							}
						}	
					}
				}
			}
		}
	}	
}


int main(){
	int initialState[N]={2, 4, 3, 1, 5, 0, 6};
	n=6; x=3; limit=3, count=0;
	markAsVisited(initialState);
	dfs(initialState);
	if(!finished)printf("No solution found\n");
	else{
	printf("%i\n", getCost());
	 display();
	}
}