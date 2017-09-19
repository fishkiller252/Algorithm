
#include <stdio.h>
#define  VMAX 21 /* ���͂̍ő�l2.1 �~10 */
#define  HMAX 200/* �g���̍ő�l2m*/
/*---�g�̃f�[�^�^---*/
typedef struct{
    double vision;  /* ����*/
    int height;  /* �g��*/
}Body;
/*---�g�̌����f�[�^�^---*/
typedef struct{
    char name[20];/* ����*/
    Body body;  /* �g�̃f�[�^�^ */
}PhysCheck;
/*---�g���̕��ϒl�����߂�---*/
double ave_height(PhysCheck *dat){
int n=0;
double sum = 0.0;

while(dat->body.height > 0){

sum += (dat++)->body.height;
n++;
dat++;

}
return (sum/n);
}
/*---���͂̕��z�����߂�---*/
void dist_vision(PhysCheck *dat, int dist[]){
   int vision;
   /*int count=0;*/
   while((vision=(int)(10*((dat++)->body.vision)+0.5))>0){
       if (vision < VMAX)
           ++*(dist+ vision);
           dat++;
           /*count+=1;*/
       }
        /* printf("%d��\n",count);*/
  }

/*�g���̕��z�����߂�*/
void dist_height(PhysCheck *dat,int dist[]){ 
int  height; // �v�Z���̐g��
 
while((height=(int)(((dat++)->body.height)))>0){
  if(height<HMAX) 
  ++*(dist + height);
 /* printf("%d\n",height);*/
 }
}

int main(void){

 PhysCheck *y, x[] = {
 {"AKASAKA Tadao",{162, 0.3}},
 {"KATOH Tomiaki",{173, 0.7}},
 {"SAITOH Syouji",{175, 2.0}},
 {"TAKEDA Shinya",{171, 1.5}},
 {"NAGAHAMA Masaki",{168, 0.4}},
 {"HAMADA Tetsuaki",{174, 1.2}},
 {"MATSUTOMI Akio",{169, 0.8}},
 {"",{0,0.0}}/*�t���O*/
 };
int *z, vdist[VMAX]={}; /* ���͂̕��z*/
int *w, hdist[HMAX]={};/* �g���̕��z*/
puts("�g�̌����ꗗ�\\");
puts("���� �g�� ����");
puts("----------------------------");

for(y = x; y->body.height > 0; y++)
  printf("%-18.18s%4d%5.1f\n", y->name, y->body.height, y->body.vision);
  printf("\n���ϐg���F%5.1fcm\n", ave_height(x));
  dist_vision(x, vdist); /* ���͂̕��z�����߂�*/
   printf("\n���͂̕��z\n");

for(z= vdist ; z< vdist+ VMAX ; z++)
   if (*z> 0)
  printf("%3.1f�`�F%2d�l\n", (z -vdist)/1.0, *z);
 

  dist_height(x,hdist);/*�g���̕��z�����߂�*/
  printf("\n �g���̕��z\n");

 int i=100;
 int count=0;
 for(i;i<=200;i=i+5){
  for(w=hdist;w<hdist+HMAX;w++){
  	
    /*if(((w-hdist)/1.0>100)&&(*w!=0))
     
     printf("%1.0f�`�F%4d �l\n",(w-hdist)/1.0,*w);*/
     
    if((i<=(w-hdist))&&((w-hdist)<i+5)&&(*w!=0))
    count++;
    
     }
      if(count!=0)
     printf("%d�` :%d �l\n",i,count);
    count=0;
  }
  return (0);
}


