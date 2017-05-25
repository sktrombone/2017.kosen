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
}