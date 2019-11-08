#include<stdio.h>
#include<string.h>
#include<stdbool.h>
 
double max(double a, double b);
 
 
int main()
{
double arr[105][105];
int n,e,k;
k=1000000;
bool cond=true;
while(cond==true)
{
if(k==1000000)
    scanf("%d",&n);
else
    n=k;
scanf("%d",&e);
for(int i=0;i<105;i++){
    for(int j=0;j<105;j++){
        arr[i][j]=0;
    }
}
for(int i=0;i<e;i++)
{
int u,v;
double c;
scanf("%d %d %lf",&u,&v,&c);
arr[u][v]=arr[v][u]=c/100.0;
}
for(int k=1;k<=n;k++)
for(int i=1;i<=n;i++)
for(int j=1;j<=n;j++)
arr[i][j]=max(arr[i][j],arr[i][k]*arr[k][j]);
printf("%lf percent \n",arr[1][n]*100);
scanf("%d",&k)==0;
if(k==0)
    cond=false;
}
} 
 
double max(double a, double b){
    if(a>b)
    return a;
    else
    return b;
} 