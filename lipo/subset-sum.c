#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int arr[1000], subset[1000], n, target;




int main(){
	char in[2005];
	n = 0;
	scanf("%[^\n]",in);
	scanf("%d",&target);
	char* tok = strtok(in, " ,()");
	while(tok!=NULL){
		arr[n++] = atoi(tok);
		tok = strtok(NULL, " ,()");
	}
	for(int i=0;i<=n;i++)printf("%d\t",arr[i]);
	return 0;
}
