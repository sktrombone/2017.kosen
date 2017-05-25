#include<stdio.h>

int main(){
	int k,j,i,l;
	unsigned char d[512];
	unsigned char b=128;
	char a;
	FILE *fp;
	
	fp=fopen("01.img","rb");
	if(fp==NULL){
		printf("can't open a file\n");
		exit(1);
	}
	for(l=0;l<20;l++){
		fread(d,512,1,fp);
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
	fclose(fp);
	return 0;
}	