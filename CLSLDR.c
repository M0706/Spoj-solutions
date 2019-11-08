#include <stdio.h>
int arr[1001][1001];
int ans(int n, int o)
{
  if (n == 1)
  {
    arr[1][o] = 1;
    return 1;
  }
  if (arr[n][o] != 0)
    return arr[n][o];
  int temp = ans(n - 1, o);
  int start;
  if (o % n == 0)
    start = n;
  else
    start = o % n;
  if (temp == 1)
  {
    arr[n][o] = start;
    return arr[n][o];
  }
  int t2 = (start + temp) % n;
  if (t2 == 0)
    arr[n][o] = n;
  else
  {
    arr[n][o] = t2;
  }
  return arr[n][o];
}
int main()
{
  int t;
  scanf("%d", &t);
  while (t--)
  {
    int n, m, o;
    scanf("%d %d %d", &n, &m, &o);
    int temp = (m - 1 + ans(n, o)) % n;
    if (temp == 0)
    {
      printf("%d\n", n);
    }
    else
    {
      printf("%d\n", temp);
    }
  }
}