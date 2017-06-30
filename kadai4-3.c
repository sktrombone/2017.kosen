#include <stdio.h>
#include <stdlib.h>

#define H 64
#define W 64
#define SS 128
#define IMGSIZE 512
#define DIM 16

//‚½‚É‚Þ‚ç
void expand(char data[512],char pattern[64][64]){
	unsigned int mask;
	int i,j,k;
	for(i=0;i<64;i++){
		for(j=0;j<8;j++){
			mask=0x80;
			for(k=0;k<8;k++){
				if(data[i*8+j]&mask) pattern[i][j*8+k]=1;
				else pattern[i][j*8+k]=0;
				
				mask=mask>>1;
			}
		}
	}
}

//‚½‚©‚Â
void outline(char p [64][64]){
	int i,j,k,mask;
	mask = 1;
	for(i=1;i<64;i++){
		for(j=1;j<64;j++){
			if(i>=1 && j>=1){
			
				if(p[i][j-1]==mask && p[i][j+1]==mask && p[i-1][j]==mask && p[i+1][j]==mask){
					p[i][j]=0;
					
				}
			}
		}
	}
}

//‚Î‚½‚Î‚½

void normalize(char p[64][64]){
	int i,j,x0=64,y0=64,x1=0,y1=0;
	double x,y;
	char p2[64][64];
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			if(p[j][i]==1){//if(p[y][x]==0)continue;  xleft=0;xright=64;
				x0=min(x0,i);//if(x<xleft)xleft=x;    ytop=0;ybot=64;
				y0=min(y0,j);//if(y<ytop)ytop=y;
				x1=max(x1,i);//if(x<xleft)xleft=x;
				y1=max(y1,j);//if(y<ybot)ybot=y;
			}
		}
	}	
	//printf("x0=%d y0=%d\nx1=%d y1=%d\n",x0,y0,x1,y1);
	double w=x1-x0+1.0;
	double h=y1-y0+1.0;
	//printf("w=%f h=%f\n",w,h);
	
	/*	x0=12  y0= 5
		x1=50  y1=58
		w =39  h =54	*/
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			p2[j][i]=p[(int)(j*(h/H)+y0+0.5)][(int)(i*(w/W)+x0+0.5)];

			//	p[j][i]=p[(int)(j*(h/H)+y0+0.5)][(int)(i*(w/W)+x0+0.5)];
		}
	}
	for(j=0;j<64;j++){
		for(i=0;i<64;i++){
			p[j][i]=p2[j][i];
		}
	}
	
}
void LabelSearch(char p[H][W],int labelnum,int h,int w)
{
	int i;
	p[h][w]=labelnum;
	if  (p[h][w+1]==1) LabelSearch(p,labelnum,h,w+1);
	if  (p[h+1][w]==1) LabelSearch(p,labelnum,h+1,w);
	if  (p[h][w-1]==1) LabelSearch(p,labelnum,h,w-1);
	if  (p[h-1][w]==1) LabelSearch(p,labelnum,h-1,w);
}


int Label(char p[H][W])
{
	int i,j,n=2;
	for (j=0;j<H;j++){
		for (i=0;i<W;i++){
			if  (p[j][i]==1){
				LabelSearch(p,n,j,i);
				n++;
				if  (n>=255) return 1;
			}
		}
	}
	return 0;
}

void noise(char p[H][W],int size)
{
	int i,j,k,ct;
	for (k=2;k<257;k++){
		ct=0;
		for (j=0;j<H;j++){
			for (i=0;i<W;i++){
				if  (p[j][i]==k) ct++;
			}
		}
		if  (ct<size){
			for (j=0;j<H;j++){
				for (i=0;i<W;i++){
					if  (p[j][i]==k) p[j][i]=0;
				}
			}
		}
	}
	for (j=0;j<H;j++){
		for (i=0;i<W;i++){
			if  (p[j][i]>1) p[j][i]=1;
		}
	}
}

void extract(char p[H][W],int f[DIM])
{
	int i,j;
	for(i=0;i<DIM;i++){
		f[i]=0;
	}
	for(i=0;i<H;i++){
		for(j=0;j<W;j++){
			if(p[i][j]==1){
				f[(i/DIM)*4+(j/DIM)]++;
			}
		}
	}
}

void printImg(char d[IMGSIZE])
{
	int x,y,i,z;
	unsigned char b=128;
	char a;
	
	for(y=0;y<H;y++){
		for(x=0;x<8;x++){
			b=128;
			for(i=0;i<8;i++){
				if((d[8*y+x]&b)==0){
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

void compress(char data[512],char pattern[64][64])
{
	int k,j,i,tmp=0;

	for(k=0; k<64; k++){
		for(j=0; j<8; j++){
			for(i=0; i<8; i++){
				if(pattern[k][j*8+i]){
					tmp+= 1 << (7-i);
				}
			}
			data[k*8+j]=tmp;
			tmp=0;
		}
	}
}

int main()
{
	
	FILE *infp,*outfp;
	char in[SS],out[SS];
	char p[H][W];
	char img[IMGSIZE];
	int i,j;
	int f[16];
	
	
	for(i=0;i<46;i++){
		sprintf(in,"%02d.img",i+1);
		sprintf(out,"%02d.ftr",i+1);
		
		infp=fopen(in,"rb");
		outfp=fopen(out,"w");
		
		while(fread(img,IMGSIZE,1,infp)==1){
			expand(img,p);
			noise(p,15);
			normalize(p);
			outline(p);
			extract(p,f);
			
			for(j=0;j<DIM;j++){
				fprintf(outfp,"%d\n",f[j]);
			}
		}
		
		fclose(infp);
		fclose(outfp);
	}
	printf("\n");
	printf("Success");
	printf("\n");

}

