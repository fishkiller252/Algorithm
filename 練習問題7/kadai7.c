#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int max;
    int num;
    int front;
    int rear;
    char **que;
} StringsQueue;

int Initialize(StringsQueue *q, int max) {
    q->num = q->front = q->rear = 0;
    if ((q->que = calloc(max, sizeof(char *))) == NULL) {
        q->max = 0;
        return -1;
    }
    q->max = max;
    return 0;
}

void Terminate(StringsQueue *q) {
    int i;
    if (q->que != NULL) {
        for (i = 0; i < q->num; i++)
            free(q->que[(i + q->front) % q->max]);
        free(q->que);
        q->max = q->num = q->front = q->rear = 0;
    }
}

int Enque(StringsQueue *q, char *x) {
    int i;
    char **tmp;

    if (q->num >= q->max) {
        tmp = calloc(q->max + 7, sizeof(char *));

        for (i = 0; i < q->max; i++) {
            tmp[i] = q->que[i];
        }

        free(q->que);
        q->que = tmp;
        q->max += 7;
    }

    q->num++;
    q->que[q->rear] = calloc(81, sizeof(char));

    for (i = 0; x[i] != '\0'; i++)
        q->que[q->rear][i] = x[i];

    q->rear++;

    return 0;
}

int Deque(StringsQueue *q, char *x) {
    int i;
    char **tmp;

    if (q->num <= 0)
        return -1;
    else {
        q->num--;

        for (i = 0; q->que[q->front][i] != '\0'; i++)
            x[i] = q->que[q->front][i];

        q->que[q->front][i + 1] = '\0';
        free(q->que[q->front]);
        q->front++;

        if (q->front == q->max) q->front = 0;
    }

    if (q->max - q->num >= 15) {
        tmp = calloc(q->max - 5, sizeof(char *));

        for (i = 0; i < q->num; i++) {
            tmp[i] = q->que[(i + q->front) % q->max];
        }

        free(q->que);
        q->que = tmp;
        q->max -= 5;
        q->front = 0;
        q->rear = q->num;
    }

    return 0;
}

int Peek(const StringsQueue *q, char *x) {
    int i;

    if (q->num <= 0)
        return -1;

    for (i = 0; q->que[q->front][i] != '\0'; i++)
        x[i] = q->que[q->front][i];
    q->que[q->front][i + 1] = '\0';

    return 0;
}

int Capacity(const StringsQueue *q) {
    return q->max;
}

int Size(const StringsQueue *q) {
    return q->num;
}

void Print(const StringsQueue *q) {
    int i;

    for (i = 0; i < q->num; i++)
        printf("%s ", q->que[(i + q->front) % q->max]);
    putchar('\n');
}

char *bm_match(char *pat, char *txt) {
    char *pt;
    char *pp;
    int txt_len = strlen(txt);
    int pat_len = strlen(pat);
    int skip[UCHAR_MAX + 1];
    int i;

    for (i = 0; i <= UCHAR_MAX; i++)
        skip[i] = pat_len;
    for (pp = pat; *pp != '\0'; pp++)
        skip[*pp] = strlen(pp) - 1;
    skip[*(pp - 1)] = pat_len;

    pt = txt + pat_len - 1;
    while (pt < txt + txt_len) {
        pp = pat + pat_len - 1;
        while (*pt == *pp) {
            if (pp == pat) return pt;
            pp--;
            pt--;
        }
        pt += (skip[*pt] > strlen(pp)) ? skip[*pt] : strlen(pp);
    }
    return NULL;
}

int Count(StringsQueue *q, char *x) {
    int counter = 0;
    int i;
    char *pt;

    for (i = 0; i < q->num; i++) {
        pt = q->que[((i + q->front) % q->max)];
        while ((pt = bm_match(x, pt)) != NULL) {
            counter++;
            pt++;
        }
    }

    return counter;
}

int main(void) {
    StringsQueue que;

    if (Initialize(&que, 3) == -1) {
        puts("�L���[�̐����Ɏ��s���܂����B");
        return 1;
    }

    while (1) {
        int m, count = 0;
        char *x = calloc(81, sizeof(char));

        printf("���݂̃f�[�^���G%d/%d\n", Size(&que), Capacity(&que));
        printf("(1)�G���L���[ (2)�f�L���[ (3)�s�[�N (4)�\\�� (5)�p�^�[���v�� (0)�I���F");
        scanf("%d", &m);
        // ------------- �@

        if (m == 0) break;

        switch (m) {
            case 1:
                printf("�f�[�^�F");
                scanf("%s", x);
                if (Enque(&que, x) == -1)
                    puts("\a�G���[�G�f�[�^�̃G���L���[�Ɏ��s���܂����B");
                break;
            case 2:
                if (Deque(&que, x) == -1)
                    puts("\a�G���[�G�f�L���[�Ɏ��s���܂����B");
                else
                    printf("�f�L���[�����f�[�^��%s�ł��B\n", x);
                break;
            case 3:
                if (Peek(&que, x) == -1)
                    puts("\a�G���[�G�s�[�N�Ɏ��s���܂����B");
                else
                    printf("�s�[�N�����f�[�^��%s�ł��B\n", x);
                break;
            case 4:
                Print(&que);
                break;
            case 5:
                printf("�p�^�[���F");
                scanf("%s", x);
                count = Count(&que, x);
                if (count != 0)
                    printf("�p�^�[����%d������܂����B\n", count);
                else
                    puts("�p�^�[���͑��݂��܂���.");
            default:
                break;
        }

        free(x);
    }
    Terminate(&que);
    return 0;
}