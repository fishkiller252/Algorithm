#include <stdio.h>

#include <string.h>

#include <limits.h>

#define NAME_LEN 20

#define String_Max 80

/*--- �g�̃f�[�^�^ ---*/

typedef struct{

double vision; /* ���� */

int height; /* �g�� */

} Body ;

/*--- �g�̌����f�[�^�^ ---*/

typedef struct{

Body body; /* �g�̃f�[�^�^ ---*/

char *name; /* ���� */

}PhysCheck;

/*--- �g�̌����f�[�^�^�X�^�b�N����������\���� ---*/

typedef struct {

int max; /* �X�^�b�N�̗e�� */

int ptr; /* �X�^�b�N�|�C���^ */

PhysCheck *stk; /* �X�^�b�N�{��*/

}PhysCheckStack;

/*--- Boyer-Moore �@�ɂ�镶����T�� ---*/

char *bm_match(char *pat , char *txt){

char *pt; /* txt ���Ȃ���J�[�\�� */

char *pp; /* pat ���Ȃ���J�[�\�� */

int txt_len = strlen(txt); /* txt �̕����� */

int pat_len = strlen(pat); /* pat �̕����� */

int skip[UCHAR_MAX + 1]; /* �X�L�b�v�e�[�u�� */

int i;

for (i = 0; i <= UCHAR_MAX; i++) /* �X�L�b�v�e�[�u���̍쐬 */

skip[i] = pat_len;

for (pp = pat; *pp != '\0'; pp++)

skip[*pp] = strlen(pp) - 1;

skip[*(pp - 1)] = pat_len; /* �p�^�[���̍Ō㕶���̈ړ������̓p�^�[���̕����� */

pt = txt + pat_len - 1; /* pat �̖����Ɣ�r���� txt �̕��������� */

while ( pt < txt + txt_len) { /* txt �̔�r���镶���̈ʒu�� txt �̖������z����܂� */

pp = pat + pat_len - 1; /* pat �̍Ō�̕����ɒ��� */

while (*pt == *pp) {

if (pp == pat) return (pt); /* ��v�����������p�^�[���̍ŏ��̕����ɂȂ�ΏI�� */

pp--;

pt--;

}

pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);

}

return (NULL);

}

/*--- �X�^�b�N�̏����� ---*/

int Initialize(PhysCheckStack *s, int max)

{

if ((s->stk = (PhysCheck *)calloc(max, sizeof(PhysCheck))) == NULL) {

s->max = 0; /* PhysCheck �̔z��̊m�ۂɎ��s */

return -1;

}

/* PhysCheck �̔z��̊m�ۂɐ��� */

s->ptr = 0;

s->max = max;

return 0;

}

/*--- �X�^�b�N�̌�n�� ---*/

void Terminate(PhysCheckStack *s){

if (s->stk != NULL){

while( --s->ptr >= 0)

free(s->stk[s->ptr].name); /* ���I�ȕ�����ۑ��p�z������ */

free(s->stk);

}

s->max = s->ptr = 0;

}

/*--- �X�^�b�N�Ƀf�[�^���v�b�V�� ---*/

int Push(PhysCheckStack *s, PhysCheck x){

if (s->ptr >= s->max) return -1; /* �X�^�b�N���t */

s->stk[s->ptr] = x;

if ((s->stk[s->ptr].name =(char *)calloc(strlen(x.name)+1, sizeof(char))) == NULL)

/* �f�[�^���R�s�[���邽�߂̓��I�ȕ�����ۑ��p�z����m�ۂ��邱�ƂɎ��s */

return -1;

strcpy(s->stk[s->ptr].name, x.name);

s->ptr++;

return 0;

}

/*--- �X�^�b�N����f�[�^���|�b�v ---*/

int Pop(PhysCheckStack *s, PhysCheck *x){

if (s->ptr <= 0) return -1; /* �X�^�b�N�͋� */

s->ptr--;

*x = s->stk[s->ptr];

strcpy(x->name, s->stk[s->ptr].name);

free(s->stk[s->ptr].name); /* �|�b�v�����̂�,���I�ȕ�����ۑ��p�z������ */

return (0);

}

/*--- �X�^�b�N����f�[�^���s�[�N ---*/

int Peek(PhysCheckStack *s, PhysCheck *x){

if (s->ptr <= 0) return -1;

*x = s->stk[s->ptr - 1];

strcpy(x->name, s->stk[s->ptr-1].name);

return 0;

}

/*--- �X�^�b�N�̗e�� ---*/

int Capacity(const PhysCheckStack *s){

return s->max;

}

/*--- �X�^�b�N�ɐς܂�Ă���f�[�^�� ---*/

int Size(const PhysCheckStack *s){

return s->ptr;

}

/*--- �X�^�b�N��1�f�[�^�̕\�� ---*/

void OneDataPrint(const PhysCheck *x){

int i;

printf("%-18.18s%4d%5.1f\n", x->name, x->body.height, x->body.vision);

}

/*--- �X�^�b�N�|�C���^�[�̒l�̃f�[�^�̕\�� ---*/

void DataPrint(PhysCheckStack *s, int pos){



OneDataPrint(s->stk + pos);

}

/*--- �X�^�b�N�̑S�f�[�^�̕\�� ---*/

void Print(const PhysCheckStack *s){

int i;



for(i = 0; i < s->ptr; i++)

OneDataPrint(s->stk+i);

putchar('\n');

}



/*--- �X�^�b�N�̃f�[�^�̒T�� ---*/

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



printf("�X�^�b�N�̑傫������͂��Ă�������");

scanf("%d", &max);

if (Initialize(&s, max)==-1){

puts("�X�^�b�N�̐����Ɏ��s���܂����B");

return 1;

}

if ((x.name = (char *)calloc(String_Max+1, sizeof(char))) == NULL){

/* �f�[�^����͗p�̓��I�ȕ�����ۑ��p�z����m�ۂ��邱�ƂɎ��s */

return 1;

}



while(1) {

int menu, pos, num;

printf("���݂̃f�[�^��:%d/%d\n",Size(&s), Capacity(&s));

printf("(1)�v�b�V�� (2)�|�b�v (3)�s�[�N (4)�\\�� (5)�T�� (0)�I��:");

scanf("%d", &menu);

if (menu == 0) break;

switch (menu) {

case 1: /* �v�b�V�� */

printf("���O: "); scanf("%s", x.name);

printf("�g��: "); scanf("%d", &(x.body.height));

printf("����: "); scanf("%lf", &(x.body.vision));

if (Push(&s, x) == -1)

puts("\a �G���[:�v�b�V���Ɏ��s���܂���.\n");

break;

case 2: /* �|�b�v */

if (Pop(&s, &x) == -1)

puts("\a �G���[:�|�b�v�Ɏ��s���܂���.\n");

else{

printf("�|�b�v�����f�[�^��,");

OneDataPrint(&x);

}

break;

case 3: /* �s�[�N */

if (Peek(&s, &x) == -1)

puts("\a �G���[:�s�[�N�Ɏ��s���܂���.\n");

else{

printf("�s�[�N�����f�[�^��,");

OneDataPrint(&x);

}

break;

case 4: /* �\�� */

Print(&s);

break;



case 5: /* �T�� */

printf("�T�����O:"); scanf("%s", x.name);

if ((pos = Search(&s, &x)) == -1)

puts("\a �G���[:������܂���ł���.\n");

else{

printf("���O����v�����f�[�^��,");

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