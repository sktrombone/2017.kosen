#include<stdio.h>

int sum(int n)
{
	if(n==1) return 1;
	return n+sum(n-1);
}

int main()
{
	int n=0;
	printf("Please enter a number. -->");
	scanf("%d",&n);
	printf("sum = %d\n",sum(n));
	return 0;
}