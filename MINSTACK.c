#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct stack{
    int top1;
    int top2;
    int* a;
    int* b;
}stack;

void push(int a[],int b[],int val,int *t1,int *t2){
     if(*t1==-1 && *t2==-1){
         a[++(*t1)]=val;
         b[++(*t2)]=val;
     }
     else{
         int k=b[(*t1)]; 
         a[++(*t1)]=val;
         if(k>val){
           b[++(*t2)]=k;
           //printf("%d",b[(*t)]);
         }
         else{
            b[++(*t2)]=val;
         }
     }
}
void pop(int *t1,int *t2){
    if(*t1==-1 && *t2==-1){
        return;
    }
    else{
        *t2=*t2-1;
        *t1=*t1-1;
       }
}
void show(int b[],int* t){
    if(*t==-1){
        printf("Empty \n");
    }
    else{
    printf("%d \n",b[*t]);
    }
}
//void showtop(int)

int main(){
int test;
char c1='A';
char c2="R";
int num=0;
scanf("%d",&test);
while(test--){

num=num+1;
stack *s;
s=(stack*)malloc(sizeof(stack));
s->a = (int*)malloc(sizeof(int)*1000000);
s->b=(int*)malloc(sizeof(int)*10000000);
s->top1=-1;
s->top2=-1;
printf("Case %d:\n",num);
int n;

  scanf("%d", &n);
  while (n--)
  {
    char c;
    scanf("%s", c);
    if (c == c1)
    {
      int val;
      scanf("%d", &val);
      push(s->a,s->b,val,&(s->top1),&(s->top2));
   
    }
    else if (c== c2) 
    {
      pop(&(s->top1),&(s->top2));
    }
    else
    {
      show(s->b,&(s->top2));
    }
  }
}}