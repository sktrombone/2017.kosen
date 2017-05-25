#include<stdio.h>

#define N 100


int main()
{
	int num[N];
	int i,cnt=0,left=0,right=N-1,tmp;
	
	FILE *fp;
	fp=fopen("kadai-1-3.txt","r");
	if(fp==NULL){
		printf("can't open this a file.\n");
		exit(1);
	}

	for(i=0;i<N;i++){
		fscanf(fp,"%d",&num[i]);
	}
		
	while(left<right){
		for (i=left;i<right;i++){
			if  (num[i]>num[i+1]){
				tmp=num[i];
				num[i]=num[i+1];
				num[i+1]=tmp;
				cnt=i;
			}
		}
		right=cnt;
		cnt=0;
		for (i=right;i>=left;i--){
			if  (num[i]>num[i+1]){
				tmp=num[i];
				num[i]=num[i+1];
				num[i+1]=tmp;
				cnt=i;
			}
		}
		left=cnt;
		cnt=0;
	}
	
	for (i=0;i<N;i++){
		printf("%3d ",num[i]);
		if(i%10==9) printf("\n");
	}
	fclose(fp);

	return 0;
}