#include <stdio.h>
/* dev-c++�R���p�C���ł́C��L��"<"��">"��"stdio.h"�Ƃ̊ԂɃX�y�[�X�������
   �R���p�C�����ɕs����������邱�Ƃ�����̂ŁC�X�y�[�X�͓���Ȃ��悤�� */

#define LINEAR 0  /* 1:���`�T���C0:�񕪒T�� */
#define NORMAL 0  /* 1:�ʏ�ŁC  0:�ԕ���   */
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
#endif
}

/* �N�C�b�N�\�[�g */
void quick( int d[N], int left, int right)
{
	int pivot,tmp,l,r;
	
	l=left;
	r=right;
	if(left==right) return;
	pivot=d[left];
	
	while(1){
		while(d[l]<pivot) left++;
		while(d[r]>pivot) right--;
		if(left>right) break;
		tmp=d[left];
		d[left]=d[right];
		d[right]=tmp;
		left++;
		right--;
	}
	if (left-l>1) quick(d,l,left-1);
	if (right-r<1) quick(d,right+1,r);
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
#else

	m=(low+high)/2;
	
	if(data[m]==target)return m;
	if(low>high)return -1;
	else if(data[m]<target)return b_search(data,m+1,high,target);
	else if(data[m]>target)return b_search(data,low,m-1,target);
	else return -1;
#endif
}

/* ���C�� */
int main(void)
{
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
        if ( index != -1 )printf("��\n");
        else printf("�~\n");
    }
    return 0;
}