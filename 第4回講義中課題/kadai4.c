#include <stdio.h>

#include <string.h>

#include <limits.h>

/*--- Boyer-Moore �@�ɂ�镶����T�� ---*/

int bm_reverse_match(char *pat , char *txt){

    char *pt; /* txt ���Ȃ���J�[�\�� */

    char *pp; /* pat ���Ȃ���J�[�\�� */

    int txt_len = strlen(txt); /* txt �̕����� */

    int pat_len = strlen(pat); /* pat �̕����� */

    int skip[UCHAR_MAX + 1]; /* �X�L�b�v�e�[�u�� */

    int i;
    int count=0;
for (i = 0; i <= UCHAR_MAX; i++) /* �X�L�b�v�e�[�u���̍쐬 */
     skip[i] = pat_len;
       for (pp = pat; *pp != '\0'; pp++)
            
           skip[*pp] = strlen(pp) - 1;

           skip[*(pp - 1)] = pat_len; /* �p�^�[���̍Ō㕶���̈ړ������̓p�^�[���̕����� */

           pt = txt + pat_len - 1; /* pat �̖����Ɣ�r���� txt �̕��������� */

   while ( pt < txt + txt_len) { /* txt �̔�r���镶���̈ʒu�� txt �̖������z����܂� */

         pp = pat + pat_len - 1; /* pat �̍Ō�̕����ɒ��� */

           while (*pt == *pp) {
                  /*count++;
                   printf("%d\n",count);*/
                if (pp == pat)
                    
                    count++;
                    /*return (pt);*/ /* ��v�����������p�^�[���̍ŏ��̕����ɂȂ�ΏI�� */

                    pp--;

                    pt--;
               
             }
            
           pt += (skip[*pt]> strlen(pp)) ? skip[*pt] : strlen(pp);
         
        }
        
       return count;
}


int main(void){

    int s;

    char s1[80]; /* �e�L�X�g */

    char s2[80]; /* �p�^�[�� */
    
    char s3[80]={}; /* �p�^�[���̋t�� */
    
    int j;
    
    int count=0;

      printf("�e�L�X�g:");

      scanf("%s", s1);

      printf("�p�^�[��:");

      scanf("%s", s2);
      
     /*   printf("s3=%s\n",s3);*/
     
     for(j=strlen(s2)-1;j>=0;j=j-1){
       s3[count]=s2[j];
       /*printf("s3:%c s2:%c\n",s3[count],s2[j]);*/
       count++;
     }
   
     /*printf("s3=%s\n",s3);*/

             s = bm_reverse_match(s3, s1); /* ������ s1 ���當���� s2 �� Boyer-Moore �@�ŒT�� */


              printf("%d\n", s);

     return (0);

}