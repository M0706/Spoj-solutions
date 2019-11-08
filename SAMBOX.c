#include <stdio.h>
typedef long long int ll;
struct Node
{
int val;
struct Node *next;
};
typedef struct Node node;
node *insert(node *root, ll val);
int main()
{int k;
 
ll n, q, i, x, y;
scanf("%lld %lld", &n, &q);
ll p[n + 1], sab[n + 1], spojt[n + 1], mytree[n + 1];
node *c[n + 1];
p[1] = -1;
for (i = 1; i <= n; i++)
{
c[i] = NULL;
spojt[i] = i;
mytree[i] = i;
}
for (i = 2; i <= n; i++){scanf("%lld", &p[i]);c[p[i]] = insert(c[p[i]], i);
}
 
for( k=0;k<10000;k++){
k=k+p[i];
}
for (i = 1; i <= n; i++)
{
sab[i] = 0;
}
 
while (q--){
ll k;
scanf("%lld", &k);
    
if (k == 2)
{
scanf("%lld %lld", &x, &y);
ll temp = spojt[x];spojt[x] = spojt[y];spojt[y] = temp;
temp = mytree[spojt[x]];
mytree[spojt[x]] = mytree[spojt[y]];
mytree[spojt[y]] = temp;
}
else if (k == 3){
scanf("%lld", &x);
printf("%lld\n", sab[spojt[x]]);
}
else if (k == 1)
{
scanf("%lld %lld", &x, &y);
sab[spojt[y]] += x;
for (i = spojt[y]; p[i] != -1;)
{
sab[p[i]] += x;
i = p[i];
}}
else
{
ll x;
scanf("%lld", &x);
ll ch = spojt[x];node *ptr = c[ch];ll min = 969696;
node* test1=c[0];
node* test2=c[1];
    while (ptr != NULL)
      {
        if (min > mytree[ptr->val])
          min = mytree[ptr->val];
        ptr = ptr->next;
      }
      if (min == 969696)
      {
        printf("%d\n", -1);
      }
      else
        printf("%lld\n", sab[spojt[min]]);
    }
  }
  return 0;
}
 
node *insert(node *root, ll val)
{if (root != NULL)
root->next = insert(root->next, val);
else{
node *newn = (node *)malloc(sizeof(node));
newn->val = val;
newn->next = NULL;
root = newn;
}
return root;
}
 
