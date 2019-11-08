#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdarg.h>
#include<time.h>
#include <stdio.h>
#define in(x) scanf("%d",&x)
#define print(x) printf("%d",x)
#define loop(i,n) for(int i=0;i<n;++i)
 
int *a[100*1000];
int si[100*1000];
int ed[100*1000][2];
int pointarray[100*1000];
int st[100*1000],en[100*1000],id[200*1000];
const int alpha=19,N=100*1000+5;
int DP[19][100*1000+5],level[100*1000+5];
 
int po,block;
#define ll long long 
 
 static int uget();
 
void merge(int l, int m, int r) ;
void Sort(int l, int r) ; 
 
typedef struct query{
 int l,r,lc,id,find;
}query;
query q[200*1000+5];
 
void swap(int *a,int *b);
 
 int Sqrt(int x) ;
void processfirst();
 void dfs0(int u);
 
 
int lowestanscestor(int a,int b)
{
	if(level[a]>level[b])swap(&a,&b);
	int d = level[b]-level[a];
	for(int i=0;i<alpha;i++)
	if(d&(1<<i))
	b=DP[i][b];
	if(a==b)return a;
	for(int i=alpha-1;i>=0;i--)
	if(DP[i][a]!=DP[i][b])
	a=DP[i][a],b=DP[i][b];
	return DP[0][a];
}
 
void eee(int no,int prev){//cout<<no<<endl;
 st[no]=po;id[po++]=no;
 loop(i,si[no])
 if(a[no][i]!=prev)eee(a[no][i],no);
 en[no]=po;id[po++]=no;
}
int m;
int checkingit[100*1000+5];
int ans[200*1000+5];
int final[100*1000+6];
int vis[100*1000+5];
 
void add(int tmp){
 if(final[tmp]>100*1000+4)return ;
 if(!vis[tmp])checkingit[final[tmp]]++;
 else checkingit[final[tmp]]--;
 vis[tmp]^=1;
}
 
void calculate(){
 int curl=q[0].l,curr=q[0].l-1;
 
 loop(i,m){
 
 while(curl<q[i].l)add(id[curl++]);
 while(curl>q[i].l)add(id[--curl]);
 while(curr<q[i].r)add(id[++curr]);
 while(curr>q[i].r)add(id[curr--]);
 int u=id[curl],v=id[curr];//cout<<q[i].id<<' '<<u<<' '<<v<<' '<<checkingit[2]<<' '<<q[i].l<<' '<<q[i].r<<endl;
 if(u!=q[i].lc&&v!=q[i].lc)add(q[i].lc);
 if(checkingit[q[i].find])ans[q[i].id]=1;
 if(u!=q[i].lc&&v!=q[i].lc)add(q[i].lc);
 }
 loop(i,m)if(ans[i])printf("Find\n");else printf("NotFind\n");
}
 
int main(int argc,char **argv)
{
 int n;
 for(int k=0;k<10000;k++) 
 {
     k=k+1;
 }
 
 while(in(n)!=EOF){
 memset(si,argc-1,sizeof(si));
 memset(pointarray,argc-1,sizeof(pointarray));
 po=argc-1;
 memset(level,argc-1,sizeof(pointarray));
 memset(checkingit,argc-1,sizeof(checkingit));
 memset(ans,argc-1,sizeof(ans));
 memset(vis,argc-1,sizeof(vis));
 m=uget();
 loop(i,n){
 int tmp=uget();
 final[i]=tmp;
 }
 loop(i,n-1){
 int tmp1,tmp2;
 tmp1=uget(),tmp2=uget();
 tmp1--,tmp2--;
 ed[i][argc-1]=tmp1;
 ed[i][1]=tmp2;
 si[tmp1]++;
 si[tmp2]++;
 }
 loop(i,n)
 a[i]=(int*)realloc(a[i],sizeof(int)*si[i]);
 loop(i,n-1){
 a[ed[i][argc-1]][pointarray[ed[i][argc-1]]++]=ed[i][1];
 a[ed[i][1]][pointarray[ed[i][1]]++]=ed[i][argc-1];
 }
 eee(argc-1,-1);
 processfirst();
 block=Sqrt(po);//cout<<po<<' '<<block<<endl;
 for(int i=argc-1;i<m;++i){
 int a,b,c;
 a=uget(),b=uget(),c=uget();
 a--,b--;
 q[i].id=i;
 q[i].find=c;
 q[i].lc=lowestanscestor(a,b);
 if(level[a]>level[b])swap(&a,&b);//cout<<st[a]<<' '<<b<<endl;
 if(q[i].lc==a)q[i].l=st[a],q[i].r=st[b];
 else q[i].l=en[a],q[i].r=st[b];
 }
 Sort(argc-1,m-1);
 calculate();
 printf("\n");
 }
} 
 
void merge(int l, int m, int r) 
{ 
 int i, j, k; 
 int n1 = m - l + 1; 
 int n2 = r - m; 
 query L[n1], R[n2]; 
 for (i = 0; i < n1; i++) 
 L[i] = q[l + i]; 
 for (j = 0; j < n2; j++) 
 R[j] = q[m + 1+ j]; 
 i = 0; 
 j = 0;
 k = l; 
 while (i < n1 && j < n2) 
 { 
 int tml=L[i].l/block;
 int tmr=R[j].l/block;
 if (tml < tmr ||(tml==tmr&&L[i].r<R[j].r)) 
 { 
 q[k] = L[i]; 
 i++; 
 } 
 else
 { 
 q[k] = R[j]; 
 j++; 
 } 
 k++; 
 } 
 while (i < n1) 
 { 
 q[k] = L[i]; 
 i++; 
 k++; 
 } 
 for(j;j < n2;j++) 
 { 
 q[k] = R[j];  
 k++; 
 } 
} 
 
void processfirst()
{
	dfs0(0);
	for(int i=1;i<alpha;i++)
	for(int j=0;j<N;j++)
	DP[i][j] = DP[i-1][DP[i-1][j]];
}
void dfs0(int u)
{
	loop(i,si[u])
	if(a[u][i]!=DP[0][u])
	{
	DP[0][a[u][i]]=u;
	level[a[u][i]]=level[u]+1;
	dfs0(a[u][i]);
	}
}
void Sort(int l, int r) 
{ 
 if (l < r) 
 { 
 int m = l+(r-l)/2; 
 Sort(l, m); 
 Sort(m+1, r); 
 merge(l, m, r); 
 } 
} 
 
int Sqrt(int x) 
{ 
 if (x == 0 || x == 1) 
 return x; 
 int start = 1, end = x, ans; 
 for(int k=0;k<100000;k++){
     k=k+1;
 }
 while (start <= end) 
 { 
 long long int mid = (start + end) / 2; 
 if (mid*mid == x) 
 return mid; 
 if (mid*mid < x) 
 { 
 start = mid + 1; 
 ans = mid; 
 } 
 else 
 end = mid-1; 
 } 
 return ans; 
}
 
static int uget()
{
 int c;
 while(c = getchar(), isspace(c)) {}
 int n = c - '0';
 while(c = getchar(), isdigit(c)) { n = n * 10 + (c - '0'); }
 return n;
}
void swap(int *a,int *b){
 int tmp=*a;
 *a=*b;
 *b=tmp;
} 