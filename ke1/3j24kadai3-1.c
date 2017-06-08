#include<stdio.h>
#include<stdlib.h>

#define N 100

int main()
{


	FILE *fp;
	int num[N];
	int i=0,j,h=1,next;
	char fname[32];
	
	printf("Please enter a file's name.\n");
	gets(fname);
	
	fp=fopen(fname,"r");
	if(fp==NULL){
		printf("can't open a file.\n");
		exit(1);
	}
	
	while(fscanf(fp,"%d",&num[i])==1)	i++;
	
	while(h<=N) h=3*h+1;
	
	while(h!=1){
		h=h/3;
		for(int k=0;k<h;k++){
			for(i=h+k;i<N;i+=h){
				next=num[i];
				for(j=i; j>=h && num[j-h]>next; j-=h){
					num[j]=num[j-h];
				}
				num[j]=next;
			}
		}
	}
	
	for(i=0;i<100;i++){
		printf(" %4d",num[i]);
		if(i%10==9)printf("\n");
	}
	fclose(fp);

	return 0;
}
