void outline(char p[64][64])
{
	int i,j;
	char p2[64][64];

	for (i=0;i<64;i++){
		for (j=0;j<64;j++){
			p2[i][j]=p[i][j];
		}
	}

	for (i=1;i<63;i++){
		for (j=1;j<63;j++){
			if(p[i][j-1]==1 && p[i][j+1]==1 && p[i-1][j]==1 && p[i+1][j]==1){
				p2[i][j]=0;
			}
		}
	}

	for (i=0;i<64;i++){
		for (j=0;j<64;j++){
			p[i][j]=p2[i][j];
		}
	}
}
