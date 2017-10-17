#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BF 1
#define KMP 1
#define TEXT_LENGTH 64
#define PATN_LENGTH 16
int next[PATN_LENGTH];

/* 文字列textから文字列patternを検索する(力まかせ法) */
int brute_force_search(char text[], char pattern[])
{
	int i = 0;
    int j = 0;
    int k;
    int o_i = 0;
    int patn_len,text_len;

    patn_len = strlen(pattern);
    text_len = strlen(text);

    while ( i < text_len && j < patn_len ) {
        if  (text[o_i + i] == pattern[j]){
            i++;
            j++;
        } else {
            for (k=0; k<o_i; k++) printf(" ");
            for (k=0; k<j+1; k++) printf("%c",pattern[k]);
            printf(" ...failure\n");
            o_i++;
            i = 0;
            j = 0;
        }
    }
    if  (j == patn_len){
        for (k=0; k<o_i; k++) printf(" ");
        printf("%s ...success\n",pattern);
        return o_i;
    } else {
        return -1;
    }
}

/* ずらし表を作成する */
void init_next(char pattern[])
{
	int i,j,k,m;
    int patn_len;

    patn_len = strlen(pattern);

    for ( j = 0; j < patn_len; j++ ){
        if ( j < 1 )
            next[j] = 1;
        else {
            for ( k = 1; k < j; k++ ){
                for ( m = k; m < j && pattern[m] == pattern[m-k]; m++ );
                if ( m == j ) break;
            }
            next[j] = k;
        }
    }
}

/* 文字列textから文字列patternを検索する(KMP法) */
int kmp_search(char text[], char pattern[])
{
	int i = 0;
    int j = 0;
    int k;
    int text_len, patn_len;
    text_len = strlen(text);
    patn_len = strlen(pattern);
    
    for (i=0; i<patn_len; i++){
        printf("%c: next[%2d] = %d\n",pattern[i],i,next[i]);
    }
    puts(text);
    i = 0;
    while ( i < text_len && j < patn_len ) {
        printf("%c",pattern[j]);
        if  (text[i] == pattern[j]){
            i++;
            j++;
        } else {
            printf(" ...failure\n");
            j -= next[j];
            if  (j < 0){
                i++;
                j++;
            }
            for (k=0; k<i; k++) printf(" ");
        }
    }
    if  (j == patn_len){
        printf(" ...success\n");
        return i-j;
    } else {
        return -1;
    }
}

int main(void)
{
    char text[TEXT_LENGTH+1];
    char pattern[PATN_LENGTH+1];
    int position;

printf("xxxtartartayxからtartayを検索する過程\n");

    strcpy(text,"xxxtartartayx");
    strcpy(pattern,"tartay");

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

printf("FIN\n\n");
printf("pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyokoからpyokopyokomuを検索する過程\n");

　　strcpy(text,"pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko");
　　strcpy(pattern,"pyokopyokomu");

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

printf("FIN\n");

    return 0;
}
