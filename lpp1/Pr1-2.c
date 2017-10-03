#include <stdio.h>
#include <time.h>
/* dev-c++コンパイラでは，上記の"<"や">"と"stdio.h"との間にスペースを入れると
   コンパイル時に不具合が発生することがあるので，スペースは入れないように */

#define LINEAR 0  /* 1:線形探索，0:二分探索 */
#define NORMAL 1  /* 1:通常版，  0:番兵版   */
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
    /* 実装せよ */
    /* dataの一番最後に番兵を追加する */
    /* ループに比較条件は不要（データ中に検索キーがあっても無くても最後に番兵は見つかるから） */
    /* みつかったらループを抜ける */
    /* 番兵しかみつからなかったら-1を返す */
    /* データがみつかったらbreakしたときの添え字の値を返す */
#endif
}

/* クイックソート */
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

    /* 前期で作成したquick関数を再利用する(再利用にあたって修正が必要なら、修正後に再利用する) */
    /* クイックソートがまだ完成していない場合は既にできているもので最も速いソートを用いてよい */
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
    /* ループバージョン */
    /* 実装せよ */
    /* low <= high の間はループ（low > highなら見つからなかった） */
    /* mid に low と high の中間値をセット */
    /* data[m] より target が小さければ high を m-1 に */
    /* data[m] より target が大きければ low を m+1 に */
    /* data[m] == target だったらループを抜ける */
    /* 見つかったなら m を返す */
    /* 見つからなかったなら -1 を返す */
#else

	m=(low+high)/2;
	
	if(data[m]==target)return m;
	if(low>high)return -1;
	else if(data[m]<target)return b_search(data,m+1,high,target);
	else if(data[m]>target)return b_search(data,low,m-1,target);
	else return -1;
	/* 再帰バージョン */
    /* 実装せよ */
    /* low > high なら見つからなかったということで -1 を返す */
    /* mid に low と high の中間値をセット */
    /* data[mid] より target が小さければ前半部分で再帰 */
    /* data[mid] より target が大きければ後半部分で再帰 */
    /* data[mid] == target だったら見つかったということで mid を返す */
#endif
}

/* メイン */
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
    for( target = N/2-500; target < N/2+500; target++ ) {  // 検索レコード数を変えるには、この辺りを修正する必要がある
#if LINEAR
        index = l_search(work,target);
#else
        index = b_search(work,0,N-1,target);
#endif
        printf("TARGET=%d: ", target);
        if ( index != -1 )
            printf("○\n");
        else
            printf("×\n");
    }
    
    end=clock();
    printf("処理時間→ %d [ms]\n",end-start);
    
    scanf("i");
    
    return 0;
}