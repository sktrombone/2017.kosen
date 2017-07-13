#include<stdio.h>
#include <stdlib.h>

#define N 1000000

void Qsort( int d[N], int left, int right)
{
	int pivot,tmp,l,r;
	
	l=left;
	r=right;
	if(left==right) return;
	pivot=d[left];
	
	while(1){
		while(d[l]<pivot) left++;
		while(d[r]>pivot) right--;
		if(left>right) break;
		tmp=d[left];
		d[left]=d[right];
		d[right]=tmp;
		left++;
		right--;
	}
	if (left-l>1) Qsort(d,l,left-1);
	if (right-r<1) Qsort(d,right+1,r);
}


int main()
{
	FILE *fp;
	int *num,i;
	num = (int *)calloc(N ,sizeof(int));
	
	fp = fopen("kadai-5-1.txt","r");
	if  (fp == NULL){
		printf("error\n");
		exit(0);
	}
	
	for (i=0; i<N; i++){
		fscanf(fp,"%d\n",&num[i]);
	}

	Qsort( num, 0, N-1);
	
	printf("ƒ\[ƒgŒã\n");
	for (i=0;i<N;i++) printf("%d\n",num[i]);
	
	fclose(fp);
	return 0;
}