
//2015-18525 김세훈
//csapp-2017summer-student09



#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct cacheLine{
	int valid;
	int order;
	long tag;
} CacheLine;



void simulate(CacheLine** cache, int S, int E, int B, int lineNum, int opt, long address, int size, int* hit, int* miss, int* evict, int w_opt){
	long index;
	long tag;
	int i;
	int LRU_order, LRU_index;

	address = address / B;
	index = address % S;
	tag = address / S;
	
	for(i = 0; i<E; i++){
		
		//valid
		if(cache[i][index].tag == tag && cache[i][index].valid==1){
			cache[i][index].order = lineNum;
			(*hit)++;
			if(opt==0){
				(*hit)++;
				if(w_opt) printf("hit ");
			}
			if(w_opt) printf("hit\n");
			return;
		}
	}
	
	//if miss!
	
	if(opt==2){
		if(w_opt) printf("miss ");
		(*miss)++;

		//find LRU index
		LRU_index = 0;
		LRU_order = cache[0][index].order;

		for(i=0; i<E; i++){
			if(LRU_order>cache[i][index].order){
				LRU_index = i;
				LRU_order = cache[i][index].order;
			}
		}
	
		if(cache[LRU_index][index].valid==1){
			if(w_opt) printf("eviction ");
			(*evict)++;
		}

	
		//update
		cache[LRU_index][index].valid = 1;	
		cache[LRU_index][index].order = lineNum;
		cache[LRU_index][index].tag = tag;
		
		if(w_opt) printf("\n");
		
		return;
	}

	//find LRU index
	LRU_index = 0;
	LRU_order = cache[0][index].order;

	for(i=0; i<E; i++){
		if(LRU_order>cache[i][index].order){
			LRU_index = i;
			LRU_order = cache[i][index].order;
		}
	}
	if(w_opt) printf("miss ");
	(*miss)++;

	if(cache[LRU_index][index].valid==1){
		if(w_opt) printf("evict ");
		(*evict)++;
	}

	if(opt==0){
		if(w_opt) printf("hit");
		(*hit)++;
	}
	
	if(w_opt) printf("\n");

	//update
	cache[LRU_index][index].valid = 1;	
	cache[LRU_index][index].order = lineNum;
	cache[LRU_index][index].tag = tag;

}

int main(int argc, char* argv[])
{
	int i, j;
	
	const char* string_s = "-s";
	const char* string_E = "-E";
	const char* string_b = "-b";
	const char* string_t = "-t";
	const char* string_v = "-v";	
	int s, E, b;
	int S, B;
	char* t;
	
	int miss = 0;
	int hit = 0;
	int evict = 0;

	FILE* fp;
	char buf[255];
	char* token;

	int option; // 0:M, 1:L, 2:S
	long address;
	int size;
	int lineNum;
	int w_opt = 0;

	/////////////////parse cmd line args/////////////////////

	for(i=0; i<argc; i++){
		printf("%s ", argv[i]);
	}
	printf("\n");
	
	i=1;

	while(i<argc){
			
		if(strcmp(argv[i], string_s)==0){
			i++;
			s = atoi(argv[i]);
			if(s==0){
				printf("wrong input\n");
				return 0;
			}
			i++;
		}
		else if(strcmp(argv[i], string_E)==0){
			i++;
			E = atoi(argv[i]);
			if(E==0){
				printf("wrong input\n");
				return 0;
			}
			i++;
		}
		else if(strcmp(argv[i], string_b)==0){
			i++;
			b = atoi(argv[i]);
			if(b==0){
				printf("wrong input\n");
				return 0;
			}	
			i++;
		}
		else if(strcmp(argv[i], string_t)==0){
			i++;
			if(argv[i]==NULL){
				printf("wrong input\n");
				return 0;
			}
			t = argv[i];	
			i++;
		}
		else if(strcmp(argv[i], string_v)==0){
			i++;
			w_opt = 1;
		}
		else{
			printf("wrong input\n");
			return 0;
		}
	}

	
	fp = fopen(t, "r");
	if(fp==NULL){
		printf("wrong input\n");
		return 0;
	}
	

	/////////////////////////make cache////////////////////////
	
	S = 1<<s;
	B = 1<<b;
	
	//associativity
	CacheLine** cache;
	cache = (CacheLine**)malloc(sizeof(CacheLine*)*E);
	
	//cache per each associativity
	for(i=0; i<E; i++){
		cache[i] = (CacheLine*)malloc(sizeof(CacheLine)*S);
		
		//initialization
		for(j=0; j<S; j++){
			cache[i][j].valid = 0;
			cache[i][j].order = 0;
			cache[i][j].tag = 0;
		}
	}
	
	///////////////////read from file input////////////////////
	
	lineNum = 0;

	while(fgets(buf, sizeof(buf), fp)){
		lineNum++;
		
		token = strtok(buf, " ");
		
		if(buf[0]!=' ') continue;
		if(w_opt) printf("%s ",token);
				
		if(strcmp(token, "M")==0) option = 0;
		else if(strcmp(token, "L")==0) option = 1;
		else option = 2;
		
		token = strtok(NULL, ",");
		if(w_opt) printf("%s, ",token);
		address = (long)strtol(token, NULL, 16);
		token = strtok(NULL, "\n");
		if(w_opt) printf("%s ",token);
		size = atoi(token);

		simulate(cache, S, E, B, lineNum, option, address, size, &hit, &miss, &evict, w_opt);
	}



	///////////////////////////////////////////////////////////

	printf("hits:%d misses:%d evictions:%d\n", hit, miss, evict);
	
	
    printSummary(hit, miss, evict);
    return 0;
}
