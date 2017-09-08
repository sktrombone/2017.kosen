#include <stdio.h>
#include <stdlib.h>

#define H 64
#define W 64
#define IMGSIZE 512
#define print printf("%d\n",__LINE__)

int main()
{
	FILE *infp,*outfp;
	char in[128];
	int f[16];
	int i,j,num,cnt;
	int x,y,n,m;
	int all=0,total=0,tmp=0,min=0;
	double ave[46][16];
	double dist[46];
	
	outfp=fopen("ave.dic","r");
	
	for(i=0;i<46;i++){
		for(j=0;j<16;j++) fscanf(outfp,"%lf",&ave[i][j]);
	}
	fclose(outfp);
	
	for(i=0;i<46;i++){
		sprintf(in,"c%02d.ftr",i+1);
		infp=fopen(in,"r");
		num=0;
		cnt=0;
		while(num<200){
			num++;
			all++;
			for(x=0;x<16;x++) fscanf(infp,"%d",&f[x]);
			for(x=0;x<46;x++){
				dist[x]=0;
				for(y=0;y<16;y++) dist[x]=dist[x]+((ave[x][y]-f[y])*(ave[x][y]-f[y]));
			}
			min=0;
			for(x=0;x<46;x++){
				if(dist[min]>dist[x]) min=x;
			}
			if(min==i){
				cnt++;
				total++;
			}
		}
		fclose(infp);
		printf("%d ‚Ì”F¯—¦‚Í %d / %d ¡‚Ì•¶š %d\n",i+1,cnt,num,min+1);
	}
	printf("‘S‘Ì‚Ì”F¯—¦‚Í %d / %d\n",total,all);
	
}
