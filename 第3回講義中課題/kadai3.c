
#include <stdio.h>
#define  VMAX 21 /* 視力の最大値2.1 ×10 */
#define  HMAX 200/* 身長の最大値2m*/
/*---身体データ型---*/
typedef struct{
    double vision;  /* 視力*/
    int height;  /* 身長*/
}Body;
/*---身体検査データ型---*/
typedef struct{
    char name[20];/* 氏名*/
    Body body;  /* 身体データ型 */
}PhysCheck;
/*---身長の平均値を求める---*/
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
/*---視力の分布を求める---*/
void dist_vision(PhysCheck *dat, int dist[]){
   int vision;
   /*int count=0;*/
   while((vision=(int)(10*((dat++)->body.vision)+0.5))>0){
       if (vision < VMAX)
           ++*(dist+ vision);
           dat++;
           /*count+=1;*/
       }
        /* printf("%d回\n",count);*/
  }

/*身長の分布を求める*/
void dist_height(PhysCheck *dat,int dist[]){ 
int  height; // 計算中の身長
 
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
 {"",{0,0.0}}/*フラグ*/
 };
int *z, vdist[VMAX]={}; /* 視力の分布*/
int *w, hdist[HMAX]={};/* 身長の分布*/
puts("身体検査一覧表\");
puts("氏名 身長 視力");
puts("----------------------------");

for(y = x; y->body.height > 0; y++)
  printf("%-18.18s%4d%5.1f\n", y->name, y->body.height, y->body.vision);
  printf("\n平均身長：%5.1fcm\n", ave_height(x));
  dist_vision(x, vdist); /* 視力の分布を求める*/
   printf("\n視力の分布\n");

for(z= vdist ; z< vdist+ VMAX ; z++)
   if (*z> 0)
  printf("%3.1f～：%2d人\n", (z -vdist)/1.0, *z);
 

  dist_height(x,hdist);/*身長の分布を求める*/
  printf("\n 身長の分布\n");

 int i=100;
 int count=0;
 for(i;i<=200;i=i+5){
  for(w=hdist;w<hdist+HMAX;w++){
  	
    /*if(((w-hdist)/1.0>100)&&(*w!=0))
     
     printf("%1.0f～：%4d 人\n",(w-hdist)/1.0,*w);*/
     
    if((i<=(w-hdist))&&((w-hdist)<i+5)&&(*w!=0))
    count++;
    
     }
      if(count!=0)
     printf("%d～ :%d 人\n",i,count);
    count=0;
  }
  return (0);
}


