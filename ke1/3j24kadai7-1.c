#include<stdio.h>
#include <stdlib.h>
int temp[1000000];


void msort(int data[],int left,int right){
	int i,j,k;
	int m=(right+left)/2;
	if(right<=left) return;
	msort(data,left,m);
	msort(data,m+1,right);
	for(i=left;i<=m;i++) temp[i]=data[i];
	for(i=m+1,j=right;i<=right;i++,j--) temp[i]=data[j];
	i=left;
	j=right;
	for(k=left;k<=right;k++){
		if(temp[i]<=temp[j]) data[k]=temp[i++];
		else data[k]=temp[j--];
	}
}

int main(){
	char str[100];
	FILE *fp;
	int *num,lines=0,size=0;
	
	fp=fopen("kadai-5-1.txt","r");
	if(fp==NULL){
		printf("file can't open\n");
		exit(1);
	}

	while ( fgets(str,80,fp) ) lines++;
	
	rewind(fp);
	num=(int*)malloc(sizeof(int)*lines);
	if(num==NULL){
		printf("can not malloc\n");
		exit(1);
	}
	while(fscanf(fp,"%d",&num[size++])!=EOF);
	msort(num,0,lines);
	for(int i=0;i<lines;i++)
		printf("%d\n",num[i]);
}

