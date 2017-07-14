#include <stdio.h>


void msort(int data[],int left,int right)
{
	int m,i,j,next;
	if(left>=right)return;
	m=(left+right)/2;
	msort(data,left,m);
	msort(data,m+1,right);
	for(i=left;i<right;i++){
		next=data[i];
		for(j=i;j>=1&&data[j-1]>next;j--){
			data[j]=data[j-1];
		}
		data[j]=next;
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
