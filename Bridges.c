#include <stdio.h>
 int max(int a, int b)
{
  if (a < b)
    return b;
  return a;
}
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
void sort(int arr[],int b[],int n)
{
int i, j, min_idx;  
  
    // One by one move boundary of unsorted subarray  
    for (i = 0; i < n-1; i++)  
    {  
        // Find the minimum element in unsorted array  
        min_idx = i;  
        for (j = i+1; j < n; j++)  {
        if (arr[j] < arr[min_idx])  
            min_idx = j;
        else if(arr[j] == arr[min_idx]){
            if(b[j] < b[min_idx])
                 min_idx = j;
        }
    }

        swap(&arr[min_idx], &arr[i]); 
        swap(&b[min_idx],&b[i]); 
        
}}
 
int main()
{
  int t, n;
  scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    int a[n], b[n], i, d[n], j;
    for (i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
    }
    for (i = 0; i < n; i++)
    {
      scanf("%d", &b[i]);
    }
    sort(a, b, n);
  for (i = 0; i < n; i++)
    {
      d[i] = 1;
    }
    int maxnum = 0;
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < i; j++)
      {
        if (b[j] <= b[i])
          d[i] = max(d[i], d[j] + 1);
      }
      maxnum = max(maxnum, d[i]);
    }
    printf("%d\n", maxnum);
  }
} 