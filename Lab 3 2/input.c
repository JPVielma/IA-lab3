#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define N 20
#define ANY -1

int getPos(char letter, char letters[N]){
		int i;
		for (i = 0; i < N; i++){
			if (letters[i] == letter){
				return i;
			}
		}
		return N;
		
	}

int main (){

	int maxHeight;
	char input[N];
	char letters[N] = {'A','B','C','D','E','F','G','H','I','J'};
	int i, stacks = 0, posStack = 0;
	int initialState[N]={-1};

	scanf("%i", &maxHeight);
	scanf("%s", &input);

	

	for (i = 0; i < N; i++){
		if (input[i] == 59){
			stacks++;
			posStack = 0;
		}
		if (input[i] >= 65 && input[i] <= 74){
			int pos = getPos(input[i], letters);
			initialState[pos] = (posStack + stacks);	
			posStack += 3;
		}
	}

	

	for(i = 0; i < N; i++){
			printf("%i\n", initialState[i]);
	}	

	return 0;
}