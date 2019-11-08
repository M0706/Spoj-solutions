#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#define repp(i,n) for(int i=0;i<n;++i)
#define rep(i,a,b) for(int i=a;i<b;++i)
#define mem(x,i) memset(x,i,sizeof(x))

#define read(n) scanf("%d", &n)
#define print(n) printf("%d", n)

struct digit
{
  int d;
  int ps;
  int pr;
};
struct qnodee
{
  int a, b;
  struct qnodee *next;
  struct qnodee *prev;
};

struct q
{
  struct qnodee *front;
  struct qnodee *rear;
};

// function definitions
void dequeue(struct q *t);
struct qnodee *front(struct q *t);
int isEmpty(struct q *t); 
struct qnodee* create();
void enqueue(struct q *t, struct qnodee *node);
struct q* createQueue();
void bfs(int n);


int vis[1005][1005];
struct digit dp[1005][1005];

int main()
{
  int t;
  int n;
  int i;
  int x;
  int y;
  int k;
  int a[10000];
 
  scanf("%d", &t);
  while (t--)
  {
    read(n);
    if (n < 10)
    {
      print(n);
      printf("\n");
      continue;
    }
    bfs(n);
    x = n;
    y = 0;
    i = 0;
    while (1)
    {
      a[i++] = dp[x][y].d;
      int s = dp[x][y].ps;
      int r = dp[x][y].pr;
      x = s;
      y = r;
      if (x == 0)
      {
        break;
      }
    }
    for (k = i - 1; k >= 0; k--)
    {
      print( a[k]);
    }
    printf("\n");
  }
}
void bfs(int n)
{
  int i, j, s, r, cs, cr;
  repp(i,1005)
  {
    repp(j,1005)
    {
      vis[i][j] = 0;
    }
  }

  struct q *t=createQueue();
  struct qnodee *neew = create();
  enqueue(t, neew);
  
  vis[0][0] = 1;
 
  while (!isEmpty(t))
  {
    struct qnodee *p = front(t);
    if (p->a == n && p->b == 0)
    {
      break;
    }
    dequeue(t);
    for (i = (p->a ? 0 : 1); i < 10; i++)
    {
      cs = p->a + i;
      cr = (10 * (p->b) + i) % n;
      if (cs > n)
      {
        break;
      }
      if (vis[cs][cr] == 0)
      {
        dp[cs][cr].d = i;
        dp[cs][cr].ps = p->a;
        dp[cs][cr].pr = p->b;
        vis[cs][cr] = 1;
        struct qnodee *ptr = (struct qnodee *)malloc(sizeof(struct qnodee));
        ptr->a = cs;
        ptr->b = cr;
        ptr->prev = NULL;
        ptr->next = NULL;
        enqueue(t, ptr);
      }
    }
  }
}


struct q* createQueue() {
    struct q* q = malloc(sizeof(struct q));
    q->front = NULL;
    q->rear = NULL;
    return q;
}
void enqueue(struct q *t, struct qnodee *node)
{
  if (t->rear == NULL)
  {
    t->rear = node;
    t->front = node;
  }
  else
  {
    t->rear->next = node;
    node->prev = t->rear;
    t->rear = node;
  }
}
int isEmpty(struct q *t)
{
  if (t->front == NULL || t->rear == NULL)
  {
    return 1;
  }
  else
    return 0;
}
struct qnodee *front(struct q *t)
{
  struct qnodee *node = t->front;
  return node;
}
void dequeue(struct q *t)
{
  struct qnodee *ptr = t->front;
  ptr = ptr->next;
  t->front = ptr;
  // free(ptr);
  if (t->front == NULL)
    t->rear = NULL;
}
struct qnodee* create(){
  struct qnodee *newnode = (struct qnodee *)malloc(sizeof(struct qnodee));
  newnode->b = 0;
  newnode->a = 0;
  newnode->next = NULL;
  newnode->prev = NULL;
  return newnode;
}

