#include <stdio.h>

#include <string.h>

#include <limits.h>

/*--- Boyer-Moore 法による文字列探索 ---*/

int bm_reverse_match(char *pat , char *txt){

    char *pt; /* txt をなぞるカーソル */

    char *pp; /* pat をなぞるカーソル */

    int txt_len = strlen(txt); /* txt の文字数 */

    int pat_len = strlen(pat); /* pat の文字数 */

    int skip[UCHAR_MAX + 1]; /* スキップテーブル */

    int i;
    int count=0;
for (i = 0; i <= UCHAR_MAX; i++) /* スキップテーブルの作成 */
     skip[i] = pat_len;
       for (pp = pat; *pp != '\0'; pp++)
            
           skip[*pp] = strlen(pp) - 1;

           skip[*(pp - 1)] = pat_len; /* パターンの最後文字の移動距離はパターンの文字数 */

           pt = txt + pat_len - 1; /* pat の末尾と比較する txt の文字を決定 */

   while ( pt < txt + txt_len) { /* txt の比較する文字の位置が txt の末尾を越えるまで */

         pp = pat + pat_len - 1; /* pat の最後の文字に着目 */

           while (*pt == *pp) {
                  /*count++;
                   printf("%d\n",count);*/
                if (pp == pat)
                    
                    count++;
                    /*return (pt);*/ /* 一致した文字がパターンの最初の文字になれば終了 */

                    pp--;

                    pt--;
               
             }
            
           pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);
         
        }
        
       return count;
}


int main(void){

    int s;

    char s1[80]; /* テキスト */

    char s2[80]; /* パターン */
    
    char s3[80]={}; /* パターンの逆順 */
    
    int j;
    
    int count=0;

      printf("テキスト:");

      scanf("%s", s1);

      printf("パターン:");

      scanf("%s", s2);
      
     /*   printf("s3=%s\n",s3);*/
     
     for(j=strlen(s2)-1;j>=0;j=j-1){
       s3[count]=s2[j];
       /*printf("s3:%c s2:%c\n",s3[count],s2[j]);*/
       count++;
     }
   
     /*printf("s3=%s\n",s3);*/

             s = bm_reverse_match(s3, s1); /* 文字列 s1 から文字列 s2 を Boyer-Moore 法で探索 */


              printf("%d\n", s);

     return (0);

}