#include <stdio.h>
#define N 10

int main(){
	
	int i,j,temp;
	int x[N];
	printf("10ŒÂ‚Ì®”‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
	for(i=0;i<N;i++){
		printf("%dŒÂ–Ú :",i+1);
		scanf("%d",&x[i]);
	}
	for(i=0;i<N;i++){
		for(j=N-1;j>i;j--){
			if(x[j-1]>x[j]){
				temp=x[j];
				x[j]=x[j-1];
				x[j-1]=temp;
			}
		}
	}
	for(i=0;i<N;i++){
		printf(" %d",x[i]);
	}
	return 0;
}