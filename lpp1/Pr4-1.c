#include <stdio.h>
#define BUF_SIZE 32

int checksp(int c)
{
			/* �������� */
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

		/* �s���̋󔒂����� */
		while( checksp(*p) == 1 ){
			/* �������� */	p++;
		
		}
		/* �V������������쐬���Ă��� */
		while(*p != '\0'){
			/* while�����̏������L������i�K������while���Ŏ������Ȃ��Ă��ǂ��j*/
			/* �������� */
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