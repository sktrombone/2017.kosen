#include <stdio.h>
#include <stdlib.h>

void printimg(char d[512])
{
	int k,j,i;
	unsigned char b=128;
	char a;
	
	for(j=0;j<64;j++){
		for(k=0;k<8;k++){
			b=128;
			for(i=0;i<8;i++){
				if((d[8*j+k]&b)==0){
					printf(".");
				}else{
					printf("*");
				}
				b=b>>1;
			}
		}
		printf("\n");
	}
	scanf("%c",&a);
}

void printimg2(char p[64][64])
{
	char a;
	for(int i=0;i<64;i++){
		for(int j=0;j<64;j++){
			if(p[i][j]==0) printf(".");
			else printf("*");
		}
		printf("\n");
	}
	scanf("%c",&a);
}

void expand(char data[512],char pattern[64][64])
{
	int k,j,i;
	unsigned char b;

	for(k=0;k<64;k++){
		for(j=0;j<8;j++){
			b=128;
			for(i=0;i<8;i++){
				if((data[k*8+j]&b)==0){
					pattern[k][j*8+i]=0;
				}else{
				pattern[k][j*8+i]=1;
				}
				b=b>>1;
			}
		}
	}
	printimg2(pattern);
}


int main()
{
	char fname[128];
	char a;
	unsigned char d[512];
	unsigned char p[64][64];
	FILE *fp;
	
	printf("Please enter a filename.\n");
	printf("filename :");
	gets(fname);

	if((fp=fopen(fname,"rb"))==NULL){
		printf("can't open a file.\n");
		exit(1);
	}
	
	for(int l=0;l<20;l++){
		fread(d,512,1,fp);
		printf("printimg‚Æexpand‚Ì‚Ç‚¿‚ç‚ðŽg‚¢‚Ü‚·‚©H\n");
		printf("‚Ç‚¿‚ç‚©‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢\n");
		scanf("%c",&a);
		if(a[]=='expand') expand(d,p);
		else printimg(d);
	}
	fclose(fp);
}