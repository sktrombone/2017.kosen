#include <stdio.h>
#include <stdlib.h>

#define N 10000000

int binarySearch(int data[],int left,int right,int search)
{
	int mid=(left+right)/2;
	
	if(data[mid]==search)return mid;
	if(left==right)return 0;
	else if(data[mid]<search)return binarySearch(data,mid+1,right,search);
	else if(data[mid]>search)return binarySearch(data,left,mid-1,search);
	else return 0;
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
	
	for(i=0;i<N;i++) fscanf(fp,"%d\n",&num[i]);
	
	printf("What kind of data are you looking for?==>");
	scanf("%d",&data);
	
	re=binarySearch(num,0,N-1,data);
	
	if(re==0)printf("The data you are looking for did not exist.");
	else printf("The data you are looking for was at the %dth.",re);
	
	fclose(fp);
	return 0;
}