#include <stdio.h>
#define N 10
int main(){

	int i, j, k, min, temp;
	int x[N];
	printf("10ŒÂ‚Ì®”‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
	for(i=0;i<N;i++){
		printf("%dŒÂ–Ú :",i+1);
		scanf("%d",&x[i]);
	}
	for(i=0;i<N;i++){
		min=x[i];
		k=i;
		for(j=i+1;j<N;j++){
			if(x[j]<min){
				min=x[j];
				k=j;
			}
		}
		temp=x[i];
		x[i]=x[k];
		x[k]=temp;
	}
	for(i=0;i<N;i++){
		printf(" %d",x[i]);
	}
	return 0;
}