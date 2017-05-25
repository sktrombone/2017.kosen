#include <stdio.h>

#define MEM (1024*32)

#define H 64
#define W 64


void expand(char data[512],char pattern[64][64]){
	for(int i=0;i<512;i++){
		for(int j=7;j>=0;j--){
			if(data[i]&(1<<j)){
				pattern[i/8][(i%8+1)*8-j]=1;
			}else{
				pattern[i/8][(i%8+1)*8-j]=0;
			}
		}
	}
}


void printimg(unsigned char d[]){
	for(int i=0;i<512;i++){
		for(int j=7;j>=0;j--){
			if(d[i]&(1<<j)){
				printf("*");
			}else{
				printf(".");
			}
		}
		if(i%8==7 ){
			printf("\n");
		}
	}
}

void outlines(char pattern[64][64]){
	for(int i=1;i<64-1;i++){
		for(int j=1;j<64-1;j++){
			if(	pattern[i-1][j-1] && pattern[i  ][j-1] && pattern[i+1][j-1] &&
				pattern[i-1][j  ] &&					  pattern[i+1][j  ] &&
				pattern[i-1][j+1] && pattern[i  ][j+1] && pattern[i+1][j+1] ){
				pattern[i][j]=2;
			}
		}
	}
	for(int i=1;i<64-1;i++){
		for(int j=1;j<64-1;j++){
			if(pattern[i][j]==2){
				pattern[i][j]=0;
			}
		}
	}
}

void printPattern(char p[64][64],int x,int y){
	for(int i=0;i<64;i++){
		printf("%-2d",i);
		for(int j=0;j<64;j++){
			for(int k=0;k<x;k++){
				
				if(p[i][j]==1){
					printf("*");
				}else{
					printf(".");
				}
			}
		}
		printf("\n");
	}
}


void normalize(char p[H][W])
{
	int i,j;
	double x0=H,y0=W,w=0.0,h=0.0;
	char p2[H][W];
	memset(p2,0,sizeof(p2));
	
	for (i=0;i<H;i++){
		for(j=0;j<W;j++){
			if(p[i][j]==1 && j<x0) x0=j;
			if(p[i][j]==1 && j>w) w=j;
		}
	}
	for(i=0;i<H;i++){
		for(j=0;j<W;j++){
			if(p[j][i]==1 && j<y0) y0=j;
			if(p[j][i]==1 && j>h) h=j;
		}
	}
	w=w-x0+1.0;
	h=h-y0+1.0;
	
	for(j=0;j<H;j++){
		for(i=0;i<W;i++){
		p2[H-1-j][i]=p[(int)((H-1-j)*(h/H)+y0+0.5)][(int)((i)*(w/W)+x0+0.5)];
		}
	}
	printf("\n");
	printf("\n");
		printPattern(p2,1,1);
}

int main(int argc,char **argv){
	unsigned char d[MEM];
	char p[64][64];
	FILE *fp;
	char fname[128];
	for(int file=1;file<47;file++){
		for(int i=0;i<MEM;i++)	d[i]=0;
		snprintf(fname,sizeof(fname),"%02d.img",file);
		printf("input file name %s\n",fname);
		fp=fopen(fname,"rb");
		if(fp==NULL){
			printf("can't open %s",fname);
			exit(1);
		}
		for(int i=0;i<20;i++){
			fread(d,512,1,fp);

			expand(d,p);
//			outlines(p);
			printPattern(p,1,1);
			normalize(p);
			
			getchar();
		}
		fclose(fp);
	}
	return 0;

}
