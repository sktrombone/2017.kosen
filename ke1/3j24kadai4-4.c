#include<stdio.h>

int binary(int n)
{
	if  (n==1) return 1;
	printf("%d",binary(n/2));
	return n%2;
}

int main()
{
	int n=0;
	printf("Please enter a number. -->");
	scanf("%d",&n);
	printf("%d(decimal) = ",n);
	printf("%d(binary)",binary(n));
	return 0;
}