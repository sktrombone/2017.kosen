#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_SIZE 13
#define TRUE     1
#define FALSE    0
#define IMAX     10000 /* �z�肵����ő�R�X�g�����傫���l��ݒ� */

 /* �f�[�^�i�אڍs��j */
int adjacent[MAX_SIZE][MAX_SIZE] = {
		{   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  0: ����
		{  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  1: ���
		{IMAX,  90,   0,IMAX,IMAX, 110, 330,240,IMAX,IMAX,IMAX,IMAX,IMAX},      //  2: �Q�n
		{  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  3: ��t
		{IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  4: ���
		{IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},     //  5: �Ȗ�
		{IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},     //  6: ����
		{IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},     //  7: �V��
		{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},     //  8: �R�`
		{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},     //  9: �{��
		{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},     // 10: �H�c
		{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},     // 11: ���
		{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}      // 12: �X
};

char *graph_data[] = {  // ��L�אڍs���0?12�Ԗڂ̊e�v�f�ɑΉ�
		"Tokyo",
		"Saitama",
		"Gunma",
		"Chiba",
		"Ibaraki",
		"Tochigi",
		"Fukushima",
		"Niigata",
		"Yamagata",
		"Miyagi",
		"Akita",
		"Iwate",
		"Aomori"
};


int d[MAX_SIZE][MAX_SIZE];           /* ���_�Ԃ̍ŏ��R�X�g */
int pre_vertex[MAX_SIZE][MAX_SIZE];  /* �ŒZ�o�H */

/* d��pre_vertex�������� */
void init(void)
{
	int i, j;

	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; j < MAX_SIZE; j++) {
			d[i][j] = adjacent[i][j];
			pre_vertex[i][j] = i;
		}
	}
}

/* ���ׂĂ̒��_�Ԃ̍ŒZ�o�H��T���i�t���C�h�@�j */
void search(void)
{
	int i, j , k;
	for (k = 0; k < MAX_SIZE; k++) {
		for (i = 0; i < MAX_SIZE; i++) {
			for (j = 0; j < MAX_SIZE; j++) {
				if (d[i][j] > d[i][k] + d[k][j]) {
					d[i][j] = d[i][k] + d[k][j];
					pre_vertex[i][j] = pre_vertex[k][j];
				}
			}
		}
	}
}

/* �o�H��\���i�t���j */
void print_path(int p, int q)
{
	int x = q;
	printf("-|%s|-",graph_data[x]);
	do{
		x = pre_vertex[p][x];
		printf("-|%s|-",graph_data[x]);
	}while(x != p);
	
	printf("\n�R�X�g��%d�ł��B",d[p][q]);
}


int main(void)
{
	int h,begin,end,flag;
	char start[10],destination[10];
	init();
	begin = -1;
	while (begin == -1) {
		printf("�o���s�s����͂��ĉ������D�F");
		scanf("%s", &start);
		for(h=0;h<MAX_SIZE;h++){
			if(!strcmp(start,graph_data[h])){
				begin=h;
				break;
			}
		}
		if(h==MAX_SIZE){
			printf("�s�s�������݂��܂���B������x\n");
			begin=-1;
		}
	}
	end = -1;
	while (end == -1) {
		printf("�����s�s����͂��ĉ������D�F");
		scanf("%s", &destination);
		for(h=0;h<MAX_SIZE;h++){
			if(!strcmp(destination,graph_data[h])){
				end=h;
				break;
			}
		}
		if(h==MAX_SIZE){
			printf("�s�s�������݂��܂���B������x\n");
			end=-1;
		}
	}

	/* �T�� */
	search();

	/* �\�� */
	print_path(begin, end);   // ���s�̈��

	return 0;
}