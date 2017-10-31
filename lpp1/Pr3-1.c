#include <stdio.h>
#define BF 1
#define KMP 1
#define BM 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 256
int next[PATN_LENGTH];
/* テキストとパターンの不一致が見つかったときにどれだけずらすかを示す表 */
int skip[PATN_LENGTH];

#define uchar unsigned char
#define max(a,b) ((a)>(b)?a:b) /* 二つの数a,bのうち大きい方を返すマクロ */

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
    int i = 0; /* 注目しているテキストの位置 */
    int j = 0; /* 注目しているパターンの位置 */
    int text_len, patn_len,a;
    text_len = strlen(text);    /* テキストの長さをセット */
    patn_len = strlen(pattern); /* パターンの長さをセット */
    printf("%c",pattern[j]);
      while ( i < text_len && j < patn_len ) {
        if(text[i]==pattern[j]){
            i++;
            j++;
	    printf("%c",pattern[j]);
        }else{
	    printf("・・・failure\n");
            i=i-j+1;
            j=0;
	    for(a=0;a<i;a++){
		printf(" ");
	    }
	    printf("%c",pattern[j]);
	}
    }
    if(j=patn_len ){
	printf("・・・success\n");
        return i-j;
    }else{
    return -1;
    }
}

/* ずらし表を作成する */
void init_next(char pattern[])
{
	int j,m,k,patn_len;
	patn_len = strlen(pattern); /* パターンの長さをセット */
	for ( j = 0; j < patn_len; j++ ) {
	    if ( j < 1 ){
	        next[j] = 1;
	    }else {
	        for ( k = 1; k < j; k++ ) {
	            for ( m = k; m < j && pattern[m] == pattern[m-k]; m++ ) ;
	            if ( m == j )
	                break;
	        }
	        next[j] = k;
	    }
	printf("%c: next[%2d] = %d\n",pattern[j],j,next[j]);
	}
}

int kmp_search(char text[], char pattern[])
{
    int i = 0; /* 注目しているテキストの位置 */
    int j = 0; /* 注目しているパターンの位置 */
    int text_len, patn_len,a;
    text_len = strlen(text);   
    patn_len = strlen(pattern); 
    printf("%c",pattern[j]);
    while ( i < text_len && j < patn_len ) {
        if(text[i]==pattern[j]){
            i++;
            j++;
	    printf("%c",pattern[j]);
        }else{
	    printf("・・・failure\n");
            j=j-next[j];
	    if(j<0){
		i++;
		j++;
	    }
	    for(a=0;a<i;a++){
		printf(" ");
	    }
	    printf("%c",pattern[j]);
	}
     }
    if(j=patn_len ){
	printf("・・・success\n");
        return i-j;
    }else{
    return -1;
    }
}

/* BM法用のずらし表を作成する */
void init_skip(uchar pattern[])
{

    int i;
    int patn_len=strlen(pattern);
    for(i=0;i<PATN_LENGTH;i++)skip[i]=patn_len;
    for(i=0;i<patn_len;i++)skip[pattern[i]]=patn_len-i-1;
    for(i=0;i<patn_len;i++)printf("%c:skip[%3d]=%d\n",pattern[i],pattern[i],skip[pattern[i]]);
}


/* 文字列textから文字列patternを検索する(BM法) */
int bm_search(uchar text[], uchar pattern[]) {

    int i; /* 注目しているテキストの位置 */
    int j; /* 注目しているパターンの位置 */
    int text_len, patn_len,k;

    text_len = strlen(text);
    patn_len = strlen(pattern);


    i = patn_len - 1;

    while( i < text_len ) {
        j = patn_len - 1;
        for (k=0; k<i; k++) printf(">");
        printf("%c",pattern[j]);
        while( text[i] == pattern[j] ) {
            if  (j==0){
                printf(" ...success\n");
                return i;
            }
            i--;
            j--;
            printf("\n");
            for (k=0; k<i; k++) printf(" ");
            printf("%c",pattern[j]);
        }
        printf(" ...failuer\n");
        if  (skip[text[i]] > (patn_len - j)) i += skip[text[i]];
        else i += patn_len - j;
    }
    return -1;

}


int main(void)
{
    uchar text[TEXT_LENGTH+1];
    uchar pattern[PATN_LENGTH+1];
    int position;
    strcpy(text,"aabbabcabc");
    strcpy(pattern,"abcab");

#if BF
    printf("--- B F ---\n");
    printf("%s\n",text);
    position = brute_force_search(text, pattern);
    printf("position=%d\n",position);
#endif

#if KMP
    printf("--- KMP ---\n");
    init_next(pattern);
    printf("%s\n",text);
    position = kmp_search(text, pattern);
    printf("position=%d\n",position);
#endif


#if BM
    printf("--- B M ---\n");
    init_skip(pattern);
    printf("%s\n",text);
    position = bm_search(text, pattern);
    printf("position=%d\n",position);
#endif

return 0;
}