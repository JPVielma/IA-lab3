
/*
• States: {[crate, position],[crate, position], [crate, position]}
• Initial state:
• Actions: 
• Transition model: 
• Goal test: 
• Path cost: 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 3
#define Y 10
#define N 20

int limit, n, finished=0, count=0, x;
int gs[N], visited[999][N], moves[4]={1, 2, -1, -2};


typedef struct node{
	struct node *next, *parent;
	int tile, step;
	int state[X*Y];
}queue;

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

int hasBeenVisited(int s[N]){//returns false if state hasn't been visited
	int i, j;
	for(i=0; i<count; i++){
		for(j=0; j<n; j++){
			if(s[j]!=visited[i][j])return 0;
		}
	}
	return 1;
}

void markAsVisited(int s[N]){
	int i;
	for (i = 0; i < n; ++i)
	{
		visited[count][i]=s[i];
	}
	count++;
	return;
}

void validate(int s[N]){
	int i;
	for(i=0; i<n; i++){
		if(s[i]!=gs[i])return;
	}
	finished=1;
	return;
}

void dfs(int state[N]){
	validate(state);
	if(!finished){
		int i, j, k;
		int *s2;
		//int correct;
		for(i=0; i<n; i++){
			if(canMove(q->state, q->state[i]+x)){//if nothing is on top
				for(k=0; k<4; k++){
					s2=duplicateArray(q->state, N);//get array copy
					if(q->state[i]%x+moves[k]<x){
						for(j=0; j<limit; j++){
							if(canMove(q->state, (q->state[i]%x+moves[k])+(x*j))){
								s2[i]=q->state[i]%x+moves[k]+(x*j);
								if(!hasBeenVisited(s2)){
									markAsVisited(s2);
									dfs(s2);
								}
								break;
							}
						}	
					}//google c break
				}
			}
		}
	}	
}

int main(){
	int initialState[N]={1,2,3,4,5,6};
	n=6; x=3; limit=4;
	gs={2,1,3,5,4,6};
	markAsVisited(initialState);
	dfs(initialState);
}