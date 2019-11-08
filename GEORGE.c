#include<stdio.h>
#include<stdlib.h>
 
int min(int a,int b){
    return a>b?b:a;
}
int max(int a,int b){
    return a>b?a:b;
}
 
int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int Gpath[1000][1000],lpath[1000][1000],Gfinal[1000], visited[1000];
    for(int i=0;i<1000;i++){
        for(int j=0;j<1000;j++){
        Gpath[i][j]=lpath[i][j]=1000000;
        }
    }
    int a,b,k,g;
    scanf("%d %d %d %d",&a,&b,&k,&g);
    a--;b--;
    for(int i=0;i<g;i++){
        scanf("%d",&Gfinal[i]);
        Gfinal[i]--;
    }
    int A,B,L;
    for(int i=0;i<m;i++){
        scanf("%d %d %d",&A,&B,&L);
        A--;
        B--;
        lpath[A][B]=lpath[B][A]=L;
    }
    int t=0;
    for(int i=1;i<g;i++)
    {
        Gpath[Gfinal[i-1]][Gfinal[i]]=t;
        Gpath[Gfinal[i]][Gfinal[i-1]]=t;
        t=t+lpath[Gfinal[i-1]][Gfinal[i]];
    }
    int Lfinal[1000]; //Luca final path
    for(int i=0;i<n;i++)
    {
        Lfinal[i]=1000000;
        visited[i]=0;
    }
    Lfinal[a]=k;
    int c;//check wheather a node is visited or not
    for(int i=0;i<n;i++)
    {
        c=-1;
        for(int j=0;j<n;j++)
        {
            if(visited[j])
                continue;
            if(c==-1 || Lfinal[j]<Lfinal[c])
                c=j;
        }
        visited[c]=1;
 
        for(int j=0;j<n;j++)
        {
            if(Lfinal[c] < Gpath[c][j])
                Lfinal[j]=min(lpath[c][j]+Lfinal[c],Lfinal[j]);
            else
                Lfinal[j]=min(Lfinal[j],max(Gpath[c][j]+lpath[c][j],Lfinal[c])+lpath[c][j]);
        }
    }
    int ans=Lfinal[b]-Lfinal[a];
    printf("%d \n",ans);
} 