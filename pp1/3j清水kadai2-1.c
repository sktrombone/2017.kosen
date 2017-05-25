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
}