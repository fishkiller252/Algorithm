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
		printf("���O�F%-20s ", s->stk[i].name);
		printf("�g���F%3d ", s->stk[i].height);
		printf("���́F%0.2lf ", s->stk[i].vision);
		putchar('\n');
	}
}

/* �T���̂��߂̊֐�
* PhysCheckStack *s : �f�[�^���X�^�b�N����\���̂��Q��
* PhysCheck *x : ���ʂ�ۑ����邽�߂̍\���̂��Q��
*/
int Search(PhysCheckStack *s, PhysCheck *x) {
	char *pt;
	char *pp;
	int nameLength;
	int patLength = strlen(x->name);
	int skipTable[UCHAR_MAX + 1];
	int i;
	int check = -1;

	/* �X�L�b�v�e�[�u���̒l��ݒ� */
	for (i = 0; i <= UCHAR_MAX; i++) skipTable[i] = patLength;
	for (pp = x->name; *pp != '\0'; pp++) skipTable[*pp] = strlen(pp) - 1;
	skipTable[*(pp - 1)] = patLength;

	/* �X�^�b�N���ꂽ�f�[�^������p�^�[�������o */
	for (i = s->ptr -1; i >= 0; i--) { // ���ォ���ɐ��`�T��
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

		printf("���݂̃f�[�^���F%d/%d\n", Size(&s), Capacity(&s));
		printf("(1) �v�b�V�� (2) �|�b�v (3) �s�[�N (4) �\\�� (5) �T�� (0) �I���F");
		scanf("%d", &menu);
		putchar('\n'); // �\�������₷���悤�ɉ��s

		if (menu == 0) break;

		switch (menu)
		{
		case 1:
			printf("���O(char[])�F");
			scanf("%s", x.name);

			printf("�g��(int)�F");
			scanf("%d", &x.height);

			printf("����(double)�F");
			scanf("%lf", &x.vision);

			if (Push(&s, &x) == -1) puts("\a�G���[�F�v�b�V���Ɏ��s���܂����B");
			break;
		case 2:
			if (Pop(&s, &x) == -1) puts("\a�G���[�F�|�b�v�Ɏ��s���܂����B");
			else printf("(�|�b�v) ���O�F%s �g���F%d ���́F%0.2lf\n", x.name, x.height, x.vision);
			break;
		case 3:
			if (Peek(&s, &x) == -1) puts("\a�G���[�F�s�[�N�Ɏ��s���܂����B");
			else printf("(�s�[�N) ���O�F%s �g���F%d ���́F%0.2lf\n", x.name, x.height, x.vision);
			break;
		case 4:
			Print(&s);
			break;
		case 5:
			printf("�p�^�[���F");
			scanf("%s", x.name);
			if (Search(&s, &x) == -1) puts("�p�^�[���͑��݂��܂���");
			else printf("���O�F%s �g���F%d ���́F%0.2f\n", x.name, x.height, x.vision);
			break;
		}
		putchar('\n'); // �\�������₷���悤�ɉ��s
	}
	return 0;
}