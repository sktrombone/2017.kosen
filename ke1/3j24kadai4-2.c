#include<stdio.h>

int fact(int n)
{
	if  (n==0||n==1) return 1;
	return n*fact(n-1);
}

int main()
{
	int n=0;
	printf("Please enter a number. -->");
	scanf("%d",&n);
	if(n<0){
		printf("\nSorry.\n");
		printf("It can't be defined by this number.\n");
	}else{
		printf("\n%d! = %d\n",n,fact(n));
	}
	return 0;
}
