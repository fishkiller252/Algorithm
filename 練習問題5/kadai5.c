#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX 10


typedef struct {
	char name[20];
	int height;
	double vision;
} PhysCheck;

typedef struct {
	int max;
	int ptr;
	PhysCheck stk[MAX];
} PhysCheckStack;

void Initialize(PhysCheckStack *s, int max) {
	s->max = max;
	s->ptr = 0;
}

int Push(PhysCheckStack *s, PhysCheck *p) {
	if (s->max <= s->ptr) return -1;
	s->stk[s->ptr++] = *p;
	return 0;
}

int Pop(PhysCheckStack *s, PhysCheck *p) {
	if (s->ptr <= 0) return -1;
	*p = s->stk[--s->ptr];
	return 0;
}

int Peek(PhysCheckStack *s, PhysCheck *p) {
	if (s->ptr <= 0) return -1;
	*p = s->stk[s->ptr - 1];
	return 0;
}

int Capacity(const PhysCheckStack *s) {
	return s->max;
}

int Size(const PhysCheckStack *s) {
	return s->ptr;
}

void Print(const PhysCheckStack *s) {
	int i;
	for (i = 0; i < s->ptr; i++) {
		printf("名前：%-20s ", s->stk[i].name);
		printf("身長：%3d ", s->stk[i].height);
		printf("視力：%0.2lf ", s->stk[i].vision);
		putchar('\n');
	}
}

/* 探索のための関数
* PhysCheckStack *s : データをスタックする構造体を参照
* PhysCheck *x : 結果を保存するための構造体を参照
*/
int Search(PhysCheckStack *s, PhysCheck *x) {
	char *pt;
	char *pp;
	int nameLength;
	int patLength = strlen(x->name);
	int skipTable[UCHAR_MAX + 1];
	int i;
	int check = -1;

	/* スキップテーブルの値を設定 */
	for (i = 0; i <= UCHAR_MAX; i++) skipTable[i] = patLength;
	for (pp = x->name; *pp != '\0'; pp++) skipTable[*pp] = strlen(pp) - 1;
	skipTable[*(pp - 1)] = patLength;

	/* スタックされたデータ内からパターンを検出 */
	for (i = s->ptr -1; i >= 0; i--) { // 頂上から底に線形探索
		nameLength = strlen(s->stk[i].name);
		pt = s->stk[i].name + patLength - 1;

		while (pt < s->stk[i].name + nameLength) {
			pp = x->name + patLength - 1;

			while (*pt == *pp) {
				if (pp == x->name) {
					*x = s->stk[i];
					return 0;
				}
				pp--;
				pt--;
			}

			pt += (skipTable[*pt] > strlen(pp)) ? skipTable[*pt] : strlen(pp);
		}
	}

	return check;
}

int main(void) {
	PhysCheckStack s;

	Initialize(&s, MAX);
	while (1) {
		int menu;
		PhysCheck x;

		printf("現在のデータ数：%d/%d\n", Size(&s), Capacity(&s));
		printf("(1) プッシュ (2) ポップ (3) ピーク (4) 表\示 (5) 探索 (0) 終了：");
		scanf("%d", &menu);
		putchar('\n'); // 表示が見やすいように改行

		if (menu == 0) break;

		switch (menu)
		{
		case 1:
			printf("名前(char[])：");
			scanf("%s", x.name);

			printf("身長(int)：");
			scanf("%d", &x.height);

			printf("視力(double)：");
			scanf("%lf", &x.vision);

			if (Push(&s, &x) == -1) puts("\aエラー：プッシュに失敗しました。");
			break;
		case 2:
			if (Pop(&s, &x) == -1) puts("\aエラー：ポップに失敗しました。");
			else printf("(ポップ) 名前：%s 身長：%d 視力：%0.2lf\n", x.name, x.height, x.vision);
			break;
		case 3:
			if (Peek(&s, &x) == -1) puts("\aエラー：ピークに失敗しました。");
			else printf("(ピーク) 名前：%s 身長：%d 視力：%0.2lf\n", x.name, x.height, x.vision);
			break;
		case 4:
			Print(&s);
			break;
		case 5:
			printf("パターン：");
			scanf("%s", x.name);
			if (Search(&s, &x) == -1) puts("パターンは存在しません");
			else printf("名前：%s 身長：%d 視力：%0.2f\n", x.name, x.height, x.vision);
			break;
		}
		putchar('\n'); // 表示が見やすいように改行
	}
	return 0;
}