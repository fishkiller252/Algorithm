#include <stdio.h>

#include <string.h>

#include <limits.h>

#define NAME_LEN 20

#define String_Max 80

/*--- 身体データ型 ---*/

typedef struct{

double vision; /* 視力 */

int height; /* 身長 */

} Body ;

/*--- 身体検査データ型 ---*/

typedef struct{

Body body; /* 身体データ型 ---*/

char *name; /* 氏名 */

}PhysCheck;

/*--- 身体検査データ型スタックを実現する構造体 ---*/

typedef struct {

int max; /* スタックの容量 */

int ptr; /* スタックポインタ */

PhysCheck *stk; /* スタック本体*/

}PhysCheckStack;

/*--- Boyer-Moore 法による文字列探索 ---*/

char *bm_match(char *pat , char *txt){

char *pt; /* txt をなぞるカーソル */

char *pp; /* pat をなぞるカーソル */

int txt_len = strlen(txt); /* txt の文字数 */

int pat_len = strlen(pat); /* pat の文字数 */

int skip[UCHAR_MAX + 1]; /* スキップテーブル */

int i;

for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成 */

skip[i] = pat_len;

for (pp = pat; *pp != '\0'; pp++)

skip[*pp] = strlen(pp) - 1;

skip[*(pp - 1)] = pat_len; /* パターンの最後文字の移動距離はパターンの文字数 */

pt = txt + pat_len - 1; /* pat の末尾と比較する txt の文字を決定 */

while ( pt < txt + txt_len) { /* txt の比較する文字の位置が txt の末尾を越えるまで */

pp = pat + pat_len - 1; /* pat の最後の文字に着目 */

while (*pt == *pp) {

if (pp == pat) return (pt); /* 一致した文字がパターンの最初の文字になれば終了 */

pp--;

pt--;

}

pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);

}

return (NULL);

}

/*--- スタックの初期化 ---*/

int Initialize(PhysCheckStack *s, int max)

{

if ((s->stk = (PhysCheck *)calloc(max, sizeof(PhysCheck))) == NULL) {

s->max = 0; /* PhysCheck の配列の確保に失敗 */

return -1;

}

/* PhysCheck の配列の確保に成功 */

s->ptr = 0;

s->max = max;

return 0;

}

/*--- スタックの後始末 ---*/

void Terminate(PhysCheckStack *s){

if (s->stk != NULL){

while( --s->ptr >= 0)

free(s->stk[s->ptr].name); /* 動的な文字列保存用配列を解放 */

free(s->stk);

}

s->max = s->ptr = 0;

}

/*--- スタックにデータをプッシュ ---*/

int Push(PhysCheckStack *s, PhysCheck x){

if (s->ptr >= s->max) return -1; /* スタック満杯 */

s->stk[s->ptr] = x;

if ((s->stk[s->ptr].name =(char *)calloc(strlen(x.name)+1, sizeof(char))) == NULL)

/* データをコピーするための動的な文字列保存用配列を確保することに失敗 */

return -1;

strcpy(s->stk[s->ptr].name, x.name);

s->ptr++;

return 0;

}

/*--- スタックからデータをポップ ---*/

int Pop(PhysCheckStack *s, PhysCheck *x){

if (s->ptr <= 0) return -1; /* スタックは空 */

s->ptr--;

*x = s->stk[s->ptr];

strcpy(x->name, s->stk[s->ptr].name);

free(s->stk[s->ptr].name); /* ポップしたので,動的な文字列保存用配列を解放 */

return (0);

}

/*--- スタックからデータをピーク ---*/

int Peek(PhysCheckStack *s, PhysCheck *x){

if (s->ptr <= 0) return -1;

*x = s->stk[s->ptr - 1];

strcpy(x->name, s->stk[s->ptr-1].name);

return 0;

}

/*--- スタックの容量 ---*/

int Capacity(const PhysCheckStack *s){

return s->max;

}

/*--- スタックに積まれているデータ数 ---*/

int Size(const PhysCheckStack *s){

return s->ptr;

}

/*--- スタックの1つデータの表示 ---*/

void OneDataPrint(const PhysCheck *x){

int i;

printf("%-18.18s%4d%5.1f\n", x->name, x->body.height, x->body.vision);

}

/*--- スタックポインターの値のデータの表示 ---*/

void DataPrint(PhysCheckStack *s, int pos){



OneDataPrint(s->stk + pos);

}

/*--- スタックの全データの表示 ---*/

void Print(const PhysCheckStack *s){

int i;



for(i = 0; i < s->ptr; i++)

OneDataPrint(s->stk+i);

putchar('\n');

}



/*--- スタックのデータの探索 ---*/

int Search(PhysCheckStack *s, PhysCheck *x){

int pos = s-> ptr;

while(--pos >= 0)

if (bm_match(x->name, s->stk[pos].name) != NULL) return pos;



return -1;

}

int main(void){

PhysCheckStack s;

int max, count;

PhysCheck x;



printf("スタックの大きさを入力してください");

scanf("%d", &max);

if (Initialize(&s, max)==-1){

puts("スタックの生成に失敗しました。");

return 1;

}

if ((x.name = (char *)calloc(String_Max+1, sizeof(char))) == NULL){

/* データを入力用の動的な文字列保存用配列を確保することに失敗 */

return 1;

}



while(1) {

int menu, pos, num;

printf("現在のデータ数:%d/%d\n",Size(&s), Capacity(&s));

printf("(1)プッシュ (2)ポップ (3)ピーク (4)表\示 (5)探索 (0)終了:");

scanf("%d", &menu);

if (menu == 0) break;

switch (menu) {

case 1: /* プッシュ */

printf("名前: "); scanf("%s", x.name);

printf("身長: "); scanf("%d", &(x.body.height));

printf("視力: "); scanf("%lf", &(x.body.vision));

if (Push(&s, x) == -1)

puts("\a エラー:プッシュに失敗しました.\n");

break;

case 2: /* ポップ */

if (Pop(&s, &x) == -1)

puts("\a エラー:ポップに失敗しました.\n");

else{

printf("ポップしたデータは,");

OneDataPrint(&x);

}

break;

case 3: /* ピーク */

if (Peek(&s, &x) == -1)

puts("\a エラー:ピークに失敗しました.\n");

else{

printf("ピークしたデータは,");

OneDataPrint(&x);

}

break;

case 4: /* 表示 */

Print(&s);

break;



case 5: /* 探索 */

printf("探す名前:"); scanf("%s", x.name);

if ((pos = Search(&s, &x)) == -1)

puts("\a エラー:見つかりませんでした.\n");

else{

printf("名前が一致したデータは,");

DataPrint(&s, pos);

puts("\n");

}

}

}

/* Terminate(&s);

if (x.name != NULL) free(x.name);

return 0;
*/
}