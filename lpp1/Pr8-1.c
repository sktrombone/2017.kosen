/* Pr8-1.c */
/* s15097 3J24 清水景太 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define TRUE      1
#define FALSE     0
#define MAX_SIZE 11

typedef struct character {
	int no;
	char name;
	struct character *next_addr;
}CELL;

char *graph_data[] = {
	"CI",           /* A : C I */
	"DGH",          /* B : D G H */
	"ADG",          /* C : A D G */
	"BCHIJ",        /* D : B C H I J */
	"FHJ",          /* E : F H J */
	"EGK",          /* F : E G K */
	"BCF",          /* G : B C F */
	"BDEJ",         /* H : B D E J */
	"AD",           /* I : A D */
	"DEHK",         /* J : D E H K */
	"FJ"            /* K : F J */
};

CELL *adjacent[MAX_SIZE]; /* 隣接リスト */
int visited[MAX_SIZE];
int path[MAX_SIZE];

/* リスト構造で並んでいる様子を表示する */
void disp(void) {
	int i = 0;
	CELL *current_addr;
	printf("隣接リスト:\n");
	for (i = 0; i < MAX_SIZE; i++) {
		if (adjacent[i] != NULL) {
			current_addr = adjacent[i];
			do {
				printf("-|%c|-", current_addr->name);
				current_addr = current_addr->next_addr;
			} while (current_addr != NULL);
		}
		printf("\n");
	}
}

/* データの追加 */
void add(int parent, int child) {
	CELL *p;
	CELL *q;
	p = (CELL *)malloc(sizeof(CELL));
	p->no = child;
	p->name = 'A' + child;
	p->next_addr = NULL;
	q = adjacent[parent];
	while (q->next_addr != NULL) {
		q = q->next_addr;
	}
	q->next_addr = p;
}

/* グラフの初期化 */
void init_graph(void) {

	int i, j;

	/*visitedの初期化*/
	for (i = 0; i < MAX_SIZE; i++) visited[i] = false;
	/*adjacentの初期化*/
	for (i = 0; i < MAX_SIZE; i++) {
		CELL *p;
		p = (CELL *)malloc(sizeof(CELL));
		p->no = i;
		p->name = 'A' + i;
		p->next_addr = NULL;
		adjacent[i] = p;
	}

	for (i = 0; i < MAX_SIZE; i++) {
		for (j = 0; graph_data[i][j] != '\0'; j++) {
			add(i, graph_data[i][j] - 'A');
		}
	}

	disp();
}

/* 経路の表示 */
void print_path(int num) {
	int i;
	for (i = 0; i <= num; i++) printf("%c ", path[i] + 'A');
	printf("\n");
}

/* 経路の探索（深さ優先探索） */
void search(int num, int now, int end) {

	CELL *p;
	int i;

	visited[now] = true; // 訪れたことを記録
	path[num] = now; // 経路を記録
	if (now == end) print_path(num);
	else {
		p = adjacent[now];
		num++;
		while (p->next_addr != NULL) {
			p = p->next_addr;
			if (visited[p->no] == false) search(num, p->no, end);
		}
	}
	visited[now] = false;
	num--;
}

/* メイン関数 */
int main(void) {
	init_graph();
	search(0, 0, 10);             /* A(0) から K(10) の経路 */
	return 0;
}