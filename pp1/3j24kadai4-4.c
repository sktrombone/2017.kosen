#include <stdio.h>
#include <stdlib.h>

#define H 64
#define W 64
#define IMGSIZE 512
#define print printf("%d\n",__LINE__)

int main()
{
	FILE *infp,*outfp;
	char in[128],out[128];
	char p[H][W];
	char img[IMGSIZE];
	double ave[16];
	int i,j,num,count;
	int file[16];
	
	outfp=fopen("ave.dic","w");
	for(i=0;i<46;i++){
		sprintf(in,"%02d.ftr",i+1);
		infp=fopen(in,"r");
		for(j=0;j<16;j++){
			ave[j]=0.0;
		}
		num=0;
		count=0;
		while(count<255){
			for(j=0;j<16;j++){
				fscanf(infp,"%d",&file[j]);
				ave[j]+=file[j];
			}
			count++;
			num++;
		}
		for(j=0;j<16;j++){
			ave[j]/=count;
			fprintf(outfp,"%f\n",ave[j]);
		}
		fclose(infp);
	}
	fclose(outfp);
	
}