#include<stdio.h>
#include <stdlib.h>
#define N 1000000

void swap(int *x, int *y)
{
	int  tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void heap( int d[], int n, int idx)
{
	int y,l2,r2;
	int l = idx*2 + 1;
	int r = idx*2 + 2;
	
	if (l >= n) return;
	
	if  (l < n && d[idx] < d[l]){
		swap( &d[idx], &d[l]);
		y = l;
		l2 = y*2 + 1;
		r2 = y*2 + 2;
		if  ((l2 < n && d[y] < d[l2]) || (r2 < n && d[y] < d[r2])) heap(d,n,y);
	}
	if  (r < n && d[idx] < d[r]){
		swap( &d[idx], &d[r]);
		y = r;
		l2 = y*2 + 1;
		r2 = y*2 + 2;
		if  ((l2 < n && d[y] < d[l2]) || (r2 < n && d[y] < d[r2])) heap(d,n,y);
	}


}

int main()
{
	FILE *fp;
	char FileName[100];
	int *d,n,k,tmp;

	d = (int *)malloc(N * sizeof(int));
	if  (d == NULL) exit(0);
	
	printf("ƒtƒ@ƒCƒ‹–¼ --> ");
	scanf("%s",FileName);
	if  (fp = fopen(FileName,"r"));
	if  (fp == NULL){
		printf("error\n");
		exit(1);
	}

	for (k=0; k<N; k++){
		fscanf(fp,"%d\n",&d[k]);
	}
	n = N;
	for(k=n-1; k>=0; k--){
		heap(d,n,k);
	}

	while(n > 1){
		tmp = d[0];
		d[0] = d[n-1];
		d[n-1] = tmp;
		n--;
		heap(d,n,0);
	}
	
	for (k=0; k<N; k++){
		printf("%d\n",d[k]);
	}
	return 0;
}