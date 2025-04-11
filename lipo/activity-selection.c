#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	int start;
	int end;
}activ;

int cmp(const void* a, const void* b){
	return ((activ*)a)->end - ((activ*)b)->end;
}

int* parseArr(char* inp, int* out){
	inp = strchr(inp, '[') + 1;
	char* tok = strtok(inp, " =[],");
	int* arr = (int*)calloc(100, sizeof(int));
	
	int n = 0;
	while(tok != NULL){
		arr[n++]=atoi(tok);
		tok = strtok(NULL, " =[],");
	}
	*out = n;
	return arr;
}

int main(){
	char in1[100];
	char in2[100];
	scanf(" %[^\n]", in1);
	scanf(" %[^\n]", in2);

	int n;
	int m;
	int* start = parseArr(in1, &n);
	int* end = parseArr(in2, &m);
	if(m!=n)return -1;
	activ acts[n];
	for(int i=0;i<n;i++){
		(acts+i)->start = start[i];
		(acts+i)->end = end[i];
	}
	qsort(acts, n, sizeof(activ), cmp);

	int t=0;
	activ ret[n];
	ret[0] = acts[0];

	for(int i = 1;i<n;i++)if(acts[i].start >= ret[t].end)ret[++t] = acts[i];
	
	for(int i=0;i<=t;i++)printf("(%d, %d)\n", ret[i].start, ret[i].end);
	return 0;
}
