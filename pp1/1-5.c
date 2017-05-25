#include<stdio.h>
#include <stdlib.h> 

FILE *fin,*fout;

int *OpenInt(int size)
{
	int *array=(int *)malloc(size*sizeof(int));
	if (array==NULL) {
		printf("** out of memory **\n");
		exit(1);
	}
	return array;
}

void PrintNum(int num[],int ct)
{
	int i;
	for (i=0;i<ct;i++){
		printf(" %3d",num[i]);
		if  ((i+1)%10==0) printf("\n");
	}
}

void OutFile(int num[],char name[],int cnt,int b)
{
	int i,x=0;

	while(name[x]!='\0'){
		x++;
	}
	name[x-3]='c';
	name[x-2]='p';
	name[x-1]='p';
	fout=fopen(name,"w");
	if  (fout==NULL){
		printf("error\n");
		exit(1);
	}
	if(b==1){
		for (i=0;i<cnt;i++){
			fprintf(fout,"%d\n",num[i]);
		}
	}else{
		for (i=cnt-1;i;i--){
			fprintf(fout,"%d\n",num[i]);
		}
	}
	fclose(fout);
}

int main()
{
	int *num,i=0,j,min,next,tmp,ret,cnt=0,tmp2,a=0,b=0;
	int counter=0;
	char fname[32];
	
	printf("入力ファイル名 > ");
	gets(fname);
	fin=fopen(fname,"r");
	if  (fin==NULL){
		printf("error\n");
		exit(1);
	}

	while(ret=fscanf(fin,"%d",&tmp2)!=EOF){
		cnt++;
	}
	num=OpenInt(cnt);
	fclose(fin);
	fin=fopen(fname,"r");
	if  (fin==NULL){
		printf("error\n");
		exit(1);
	}
	
	while(ret=fscanf(fin,"%d",&tmp2)!=EOF){
		num[i]=tmp2;
		i++;
	}
	fclose(fin);

	printf("1:バブルソート 2:選択ソート 3:挿入ソート\n");
	while(a<1 || a>3){
		printf(" -->");
		scanf("%d",&a);
	}
	printf("1:昇順 2:降順\n");
	while(b<1 || b>2){
		printf(" -->");
		scanf("%d",&b);
	}
	switch(a){
		case 1:
			for(i=cnt-1;i>0;i--){
				for(j=0;j<i;j++){
					if  (num[j]>num[j+1]){
						tmp=num[j];
						num[j]=num[j+1];
						num[j+1]=tmp;
						counter++;
					}
				}
			}
			break;
		
		case 2:
			for (i=0;i<cnt;i++){
				min=i;
				for (j=i+1;j<cnt;j++){
					if  (num[j]<num[min]) min=j;
					counter++;
				}
				tmp=num[i];
				num[i]=num[min];
				num[min]=tmp;
			}
			break;
		
		case 3:
			for(i=1;i<cnt;i++){
				next=num[i];
				for(j=i;j>=1 && num[j-1]> next;j--){
					num[j]=num[j-1];
					counter++;
				}
				num[j]=next;
			}
			break;
	}
	OutFile(num,fname,cnt,b);
	printf("入れ替えた回数：%d回\n",counter);
	printf("出力ファイル名 --> %s",fname);
	
	return 0;
}