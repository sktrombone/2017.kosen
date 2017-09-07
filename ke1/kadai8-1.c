#include <stdio.h>
#include <stdlib.h>

#define N 10000000

int binarysearch(int data[],int left,int right,int search)
{
	int m=(left+right)/2;
	
	if(data[m]==search)return m;
	if(left==right)return -1;
	else if(data[m]<search)return binarysearch(data,m+1,right,search);
	else if(data[m]>search)return binarysearch(data,left,m-1,search);
	else return -1;
}

int main()
{
	FILE *fp;
	int *num,i,data,re;
	num=(int*)calloc(N,sizeof(int));
	
	fp=fopen("sorted.dat","r");
	if(fp==NULL){
		printf("can't open a file.\n");
		exit(1);
	}
	
	for(i=0;i<N;i++){
		fscanf(fp,"%d\n",&num[i]);
	}
	
	printf("どのデータをお求めですか？");
	scanf("%d",&data);
	
	re=binarysearch(num,0,N-1,data);
	
	if(re==-1)printf("お探しのデータは存在しませんでした．");
	else printf("お探しのデータは%d番目にありました．",re);
	
	fclose(fp);
	return 0;
}