#include <stdio.h>
#include<stdlib.h>
 
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
 
typedef struct minheap
{
  int a[100000];
  int size;
}minheap;
typedef struct maxheap
{
  int a[100000];
  int size;
}maxheap;
 
void insertmin(struct minheap *h,int value){
    h->size++; 
    h->a[(h->size)-1]=value; /*Insert in the last place*/
    int now = h->size-1;
    while (h->a[(int)((now-1)/ 2)] > value) {
        swap(&h->a[(int)((now-1)/ 2)],&h->a[now]);
    now=(int)(now-1)/2;
    }
}
void insertmax(struct maxheap *h,int value){
    h->size++; 
    int now = h->size-1;
    h->a[now]=value; /*Insert in the last place*/
    while (now!=0 && h->a[(int)((now-1)/ 2)] < value) {
        swap(&h->a[(int)((now-1)/ 2)],&h->a[now]);
       now=(int)(now-1)/2;
    }
}
 
void heapifymax(maxheap *h, int i)
{
  int l = (2 * i + 1); //left
  int r = (2 * i + 2); //right
  int k = i;     //smallest 
  if (l < h->size && h->a[l] > h->a[k])
    k = l;
  if (r < h->size && h->a[r] > h->a[k])
    k = r;
  if (k != i)
  {
    swap(&h->a[i], &h->a[k]);
    heapifymax(h, k);
  }
}
void heapifymin(minheap *h, int i)
{
  int l = (2 * i + 1); //left
  int r = (2 * i + 2); //right
  int k = i;     //smallest 
  if (l < h->size && h->a[l] < h->a[k])
    k = l;
  if (r < h->size && h->a[r] < h->a[k])
    k = r;
  if (k != i)
  {
    swap(&h->a[i], &h->a[k]);
    heapifymin(h, k);
  }
}
int top_max(maxheap *h)
{
  return h->a[0];
}
int deletemax(maxheap *h){
if (h->size <= 0)
  {
    h->size--;
    return h->a[0];
  }
    int t = h->a[0];
    h->a[0] = h->a[h->size- 1];
    h->size--;
    heapifymax(h, 0);
    return t;
}
 
int deletemin(minheap *h)
{
  if (h->size <= 0)
  {
    h->size--;
    return h->a[0];
  }
  int t = h->a[0];
  h->a[0] = h->a[h->size- 1];
  h->size--;
  heapifymin(h, 0);
  return t;
}
 
int main()
{
  int t;
  scanf("%d", &t);
  while (t--)
  {
     minheap hmin;
      maxheap hmax;
      //hmin=(minheap*)malloc(sizeof(minheap));
      //hmax=(maxheap*)malloc(sizeof(maxheap));
      hmin.size=0;
      hmax.size=0;
    int dump = 1;
    while (1)
    {
      int n;
      scanf("%d", &n);
      if (n == 0)
        break;
      else if(n!=-1)
      {
        if (dump == 1)
        {
          insertmax(&hmax, n);
          dump = 0;
          //   printf("%d\n",top_max(&hmax));
        }
        else
        {
          int n2 = top_max(&hmax);
          if (n2 <= n)
            insertmin(&hmin, n);
          else
          {
            insertmax(&hmax, n);
          }
          if (hmax.size < hmin.size)
          {
            int temp = deletemin(&hmin);
            insertmax(&hmax, temp);
          }
          else if (hmax.size - hmin.size > 1)
          {
            int temp = deletemax(&hmax);
            insertmin(&hmin, temp);
          }
        }
        // printf("%d",top_max(&hmax));
      }
      else if (n == -1)
      {
        printf("%d\n", deletemax(&hmax));
        if (hmax.size < hmin.size)
        {
          int temp = deletemin(&hmin);
          insertmax(&hmax, temp);
        }
      }
    }
  }
 return 0;
}
 
 