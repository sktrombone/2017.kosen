#include <stdio.h>
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 0  /* 1:通常版，  0:番兵版   */
#define LOOP   0  /* 1:ループ版，0:再帰版   */

#define N  30000  /* 探索するレコード数 (注意：この値"だけ"を変えても、実際の検索レコード数は増えない） */ 

/* 線形探索 */
int l_search(int data[], int target)
{
    int i, count = 0;
#if NORMAL   /* 通常版 */
    for ( i = 0; i < N; i++ )
        if ( target == data[i] ) {
            return i;
        }
    return -1;
#else        /* 番兵版 */
    data[N-1] = target;
    while(data[i] != target) i++;
    if  (i == N-1) return -1;
    else return i;
#endif
}

/* クイックソート */
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

/* 二分探索 */
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

/* メイン */
int main(void)
{
    int a[N], i, target, work[N], index;
    for( i = 0; i < N; i++ ) work[i] = rand() % N;
#if LINEAR
#else
    quick(work,0,N-1);
#endif
    for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
#if LINEAR
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 )printf("○\n");
        else printf("×\n");
    }
    return 0;
}