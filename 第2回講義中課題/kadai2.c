
 /*�N���̌o�ߓ��������߂�*/
#include  <stdio.h>
/*-�e���̓���-*/
int mdays[][13] = {
{1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{-1, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
/*---����year�N�̃J�����_�[---*/
int *calendar(int year){
if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
return (int *)mdays+ 13;/* (int *)�����I�Ɍ^�ϊ����閽��*/
else
return (int *)mdays ;
}
/*---����y�Nm��d���̔N���̌o�ߓ��������߂�---*/
int dayofyear(int y, int m, int d){
int *i;
int days= d;
/* ����*/
if(y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
for (i = calendar(y)+m -1; *i != -1; i--){
   days += *i ;
}
else
for (i = calendar(y)+m -1; *i != 1; i--){
   days += *i ;
 }
return (days);
}
int main(void){
int year, month, day; /* �N�E���E��*/
int retry;/* ������x�H*/
do {
printf("�N�F");  scanf("%d", &year);
printf("���F");  scanf("%d", &month);
printf("���F");  scanf("%d", &day);
printf("�N����%d���ڂł��B\n", dayofyear(year, month, day));
printf("������x���܂����i1�c�͂��^0�c�������j�F");
scanf("%d", &retry);
} while (retry == 1);
}