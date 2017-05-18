#include <stdio.h>

#define H 64
#define W 64

void Normalize(char p[H][W])
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
}
