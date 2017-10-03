#include <stdio.h>
#include <time.h>
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 0  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 1  /* 1:�ʏ�ŁC  0:�ԕ���   */
#define LOOP   0  /* 1:���[�v�ŁC0:�ċA��   */

#define N  30000  /* �T�����郌�R�[�h�� (���ӁF���̒l"����"��ς��Ă��A���ۂ̌������R�[�h���͑����Ȃ��j */ 

/* ���`�T�� */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* �ʏ�� */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* �ԕ��� */
    data[N-1] = target;
    while(data[i] != target) i++;
    if  (i == N-1) return -1;
    else return i;
    /* �������� */
    /* data�̈�ԍŌ�ɔԕ���ǉ����� */
    /* ���[�v�ɔ�r�����͕s�v�i�f�[�^���Ɍ����L�[�������Ă������Ă��Ō�ɔԕ��͌����邩��j */
    /* �݂������烋�[�v�𔲂��� */
    /* �ԕ������݂���Ȃ�������-1��Ԃ� */
    /* �f�[�^���݂�������break�����Ƃ��̓Y�����̒l��Ԃ� */
#endif
}

/* �N�C�b�N�\�[�g */
void quick(int d[], int a, int b)
{
    int pivot,tmp,i,j;
    i=a;
    j=b;
    pivot=d[a];
    while(1){
        while(d[a]<pivot)a++;
        while(d[b]>pivot)b--;
        if(a>=b)break;
        tmp=d[a];
        d[a]=d[b];
        d[b]=tmp;
        a++;
        b--;
    }
	
	if(a-i>=2)quick(d,i,a-1);
	if(j-b>=2)quick(d,b+1,j);

    /* �O���ō쐬����quick�֐����ė��p����(�ė��p�ɂ������ďC�����K�v�Ȃ�A�C����ɍė��p����) */
    /* �N�C�b�N�\�[�g���܂��������Ă��Ȃ��ꍇ�͊��ɂł��Ă�����̂ōł������\�[�g��p���Ă悢 */
}

/* �񕪒T�� */
int b_search(int data[], int low, int high, int target)
{
    int m;
#if LOOP 
	
	while(low<=high){
	m=(low+high)/2;
	if(data[m]==target)return m;
	if(data[m]>target)high=m-1;
	if(data[m]<target)low=m+1;
	}
	return -1;
    /* ���[�v�o�[�W���� */
    /* �������� */
    /* low <= high �̊Ԃ̓��[�v�ilow > high�Ȃ猩����Ȃ������j */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[m] ��� target ����������� high �� m-1 �� */
    /* data[m] ��� target ���傫����� low �� m+1 �� */
    /* data[m] == target �������烋�[�v�𔲂��� */
    /* ���������Ȃ� m ��Ԃ� */
    /* ������Ȃ������Ȃ� -1 ��Ԃ� */
#else

	m=(low+high)/2;
	
	if(data[m]==target)return m;
	if(low>high)return -1;
	else if(data[m]<target)return b_search(data,m+1,high,target);
	else if(data[m]>target)return b_search(data,low,m-1,target);
	else return -1;
	/* �ċA�o�[�W���� */
    /* �������� */
    /* low > high �Ȃ猩����Ȃ������Ƃ������Ƃ� -1 ��Ԃ� */
    /* mid �� low �� high �̒��Ԓl���Z�b�g */
    /* data[mid] ��� target ����������ΑO�������ōċA */
    /* data[mid] ��� target ���傫����Ό㔼�����ōċA */
    /* data[mid] == target �������猩�������Ƃ������Ƃ� mid ��Ԃ� */
#endif
}

/* ���C�� */
int main(void)
{
	clock_t start,end;
	start=clock();
	
    int a[N], i, target, work[N], index;
    for( i = 0; i < N; i++ ) work[i] = rand() % N;
#if LINEAR
#else
    quick(work,0,N-1);
#endif
    for( target = N/2-500; target < N/2+500; target++ ) {  // �������R�[�h����ς���ɂ́A���̕ӂ���C������K�v������
#if LINEAR
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 )
            printf("��\n");
        else
            printf("�~\n");
    }
    
    end=clock();
    printf("�������ԁ� %d [ms]\n",end-start);
    
    scanf("i");
    
    return 0;
}