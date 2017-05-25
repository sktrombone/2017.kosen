#include<stdio.h>

#define N 100

int main(){

	int i,j,next;
	int a[N+10];
	
	FILE *fp;
	fp=fopen("kadai-1-3.txt","r");
	if(fp==NULL){
		printf("can't open this a file.\n");
		exit(1);
	}
	for(i=0;i<N;i++){
		fscanf(fp,"%d",&a[i]);
	}
	for(i=1;i<N;i++){
		next=a[i];
		for(j=i;j>=1&&a[j-1]>next;j--){
			a[j]=a[j-1];
		}
		a[j]=next;
	}
	for(i=0;i<N;i++) printf("%3d\n",a[i]);
	
	fclose(fp);
	return 0;
}