#include <stdio.h>
#define BUF_SIZE 32

int checksp(int c)
{
			/* 実装せよ */
			if (c == ' ') {
				return 1;
			}else if (c == '\t') {
				return 1;
			}else if (c == '\n') {
				return 1;
			}else{
				return -1;
			}
}

void compress(char *s)
{
		char *p;
		int i,j;
		int chSpace = 0;

		p = s;

		/* 行頭の空白を消去 */
		while( checksp(*p) == 1 ){
			/* 実装せよ */	p++;
		
		}
		/* 新しい文字列を作成していく */
		while(*p != '\0'){
			/* while文内の条件を記入せよ（必ずしもwhile文で実装しなくても良い）*/
			/* 実装せよ */
			if(checksp(*p) == 1 && (*(p+1) == ',' || *(p+1) == '.')){
				chSpace = 1;
				s--;
				p++;
			}else if (checksp(*p) == 1) {
				if (chSpace == 0) {
					chSpace = 1;
					*s = ' ';
					s++;
					p++;
				}else{
					chSpace = 1;
					p++;
				}
			}else{
				chSpace = 0;
				*s = *p;
				s++;
				p++;
			}

		}
		*s = '\0';
}

int main(void)
{
	char s[] = "     Nice to \n meet \t you    ,  Jack !\n     I'm      Mike \n\t\t .    ";

	printf("Before = \"%s\"\n",s);
	compress(s);

	printf("After  = \"%s\"\n",s);

	return 0;
}