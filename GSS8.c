#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
typedef long long ll;
int N, Q, root, cal[12][12], total;
unsigned int a[200007][12];
#define repp(i,n) for(int i=0;i<n;i++)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define read(n) scanf("%d", &n)
unsigned int array[200007];

int add(int a, int b){
  return a+b;
}

typedef struct node
{
  int ff;
  int size;
  int  ch[2];
  unsigned int val[11], here;
}node;
node t[200007];
void push(int rt)
{
  int lc ;int rc;
  lc = t[rt].ch[0];
  rc = t[rt].ch[1];
  t[rt].size = add(t[lc].size,t[rc].size) + 1;
  int i;
  for (i = 0; i <= 10; i++)
  {
    t[rt].val[i] =add(t[lc].val[i],t[rt].here * a[t[lc].size + 1][i]);
    int j;
    for (j = 0; j <= i; j++){
      ll temp1;
      temp1=cal[i][j] * a[t[lc].size + 1][i - j] * t[rc].val[j];
      t[rt].val[i]=add(t[rt].val[i], temp1);
  }}
}
void treesplaytree(int rt, int l, int r)
{
  if (l > r)
    return;
  int middle = (l + r)>>1;
  t[rt].ch[middle > rt] = middle;
  t[middle].ff = rt;
  t[middle].size = 1;
  t[middle].here = array[middle];
  if (l == r)
  {
    int i;
    for (i = 0; i <= 10; i++)
      t[middle].val[i] = array[middle];
    return;
  }
  treesplaytree(middle, l, middle - 1);
  treesplaytree(middle, middle + 1, r);
  ll temp3;
  temp3=  add(t[t[middle].ch[1]].size,t[t[middle].ch[0]].size)  + 1;
  t[middle].size = temp3 ;
  push(middle);
}
void Rotate(int x)
{
  int y;
  int z;
  int k;
   y = t[x].ff;
   k = t[y].ch[1]== x;
    z = t[y].ff;
  t[z].ch[t[z].ch[1] == y] = x;
  t[x].ff = z;
  t[y].ch[k] = t[x].ch[k ^ 1];
  t[t[x].ch[k ^ 1]].ff = y;
  t[x].ch[k ^ 1] = y;
  t[y].ff = x;
  push(y);
  push(x);
}
void treesplay(int x, int goal)
{
  while (t[x].ff != goal)
  {
    int y;
    int z;
     y = t[x].ff;
     z = t[y].ff;
    if (z != goal)
      if((t[z].ch[0] == y) ^ (t[y].ch[0] == x)) 
       Rotate(x); 
       else
       Rotate(y);
    Rotate(x);
  }
  if (!goal)
    root = x;
}
int Kth(int x)
{
  int u;
   u = root;
  if (x > t[u].size)
    return -1;
  while (1)
  {
    int y;
    y = t[u].ch[0];
    if (x > t[y].size + 1)
    {
      x -= t[y].size + 1;
      u = t[u].ch[1];
    }
    else
    {
      if (t[y].size >= x)
        u = y;
      else
        return u;
    }
  }
}
void Entery(int x, int y)
{
  int last;
  int next;
  last = Kth(x);
  next = Kth(x + 1);
  treesplay(last, 0);
  treesplay(next, last);
  t[next].ch[0] = ++total;
  t[total].ff = next;
  t[total].size = 1;
  t[total].here = y;
  int i;
  for ( i = 0; i <= 10; i++)
    t[total].val[i] = y;
  push(next);
  push(last);
}
void Delete(int x)
{
  int last;
  int next;
  last = Kth(x - 1);
   next = Kth(x + 1);
  treesplay(last, 0);
  treesplay(next, last);
  t[next].ch[0] = 0;
  push(next);
  push(last);
}
void re_set(int x, int y)
{
  int temp;
  temp = Kth(x);
  treesplay(temp, 0);
  t[temp].here = y;
  push(temp);
}
int query(int x, int y, int k)
{
    int last;
    int next;
   last = Kth(x - 1);
    next = Kth(y + 1);
  treesplay(last, 0);
  treesplay(next, last);
  ll val=t[t[next].ch[0]].val[k];
  return val;
}
void pre_Cal()
{
    int i;
  for (i = 0; i <= 10; i++)
  cal[i][0] = 1;
  cal[1][1] = 1;
  i=1;
  while(i<=10)
  {
    i++;
    int j=0;
    while(j<=i)
    {
      j++;
      cal[i][j] = add(cal[i - 1][j], cal[i - 1][j - 1]);
    }
  }
}
void init()
{
  rep(i,1,2e+5)   //rep(i,a,b) for(int i=a;i<b;i++)
  {
    a[i][0] = 1;
    rep(k,1,11)
    {
      a[i][k] = a[i][k - 1] * i;
    }
  }
}
int main()
{
  int i;
  i=0;
  while(i<2e5 + 7)
  {
    i++;
    t[i].ff =0;
     t[i].size =0;
      t[i].ch[0] =0;
       t[i].ch[1] =0;
        t[i].here = 0;
    int j=0;
    while(j<11)
    {
        j++;
      t[i].val[j] = 0;
    }
  }
  pre_Cal();
  read(N);
  init();
  for (int i = 2; i <= N + 1; i++)
    scanf("%u", &array[i]);
  array[1] = 0;
  array[N + 2] = 0;
  treesplaytree(0, 1, N + 2);
  t[0].size =0;
   t[0].ff = 0;
t[0].here =0;
t[0].ch[0] = 0;
t[0].ch[1] = 0; 
  for (i = 0; i < 11; i++)
  {
    t[0].val[i] = 0;
  }
  root = (N + 3)>>1;
  total = N + 2;
  scanf("%d", &Q);
  char op[3];
  int x;
  int y;
  int k;
  while (Q--)
  {
     scanf("%s", op);
    if (op[0] == 'I') 
    {
      read(x);read(y);
      x=x+1;
      Entery(x, y);
    }
    else if (op[0] == 'D') 
    {
      read(x);
      x =x+2;
      Delete(x);
    }
    else if (op[0] == 'R') 
    {
      read(x);read(y);
      x =x+2;
      re_set(x, y);
    }
    else 
    {
      read(x);read(y);read(k);
      x =x+2;
      y =y+2;
      unsigned int tmp = query(x, y, k);
      printf("%u\n", tmp);
    }
  }
  return 0;
}