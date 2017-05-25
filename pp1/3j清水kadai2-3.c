void compress(char data[512],char pattern[64][64])
{
	int i,j,k,tmp=0;

	for(k=0;k<64;k++){
		for(j=0;j<8;j++){
			for(i=0;i<8;i++){
				tmp+=pattern[k][j*8+i]*(int)pow(2.0,(double)7-i);
			}
			data[k*8+j]=tmp;
			tmp=0;
		}
	}
}