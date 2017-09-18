#  第5回講義中課題
添付してある 授業中練習問題５を行い，その解答を答えなさい

```  
(1)
(ア)Pop

(イ)0

(ウ)-1

(2)
(ア)s.ptr =5
       s,stk[4]=83

(イ)47

(ウ)47

(3)Push:
int Push(PhysCheek *s, char x){

if (s->ptr >= s->max) return -1; /* スタック満杯 */

s->stk[s->ptr] = x;

s->ptr++;

return 0;

}

     Pop:
int Pop(PhysCheck *s, char *x){

if (s->ptr <= 0) return -1; /* スタックは空 */

s->ptr--;

*x = s->stk[s->ptr];

return (0);

}
```  
