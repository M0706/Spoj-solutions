//Manav Garg
//B18BB016
// sited from github

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define repp(i,n) for(int i=0;i<n;i++)
#define rep(i,a,b) for(int i=a;i<b;i++)
#define read(n) scanf("%d", &n)

typedef long long int64;


// < DEFAULT CONSTANTS AND STRUCTURES TO BE USED >
#define N 100010
#define M 100010
#define K 16

int addition(int a,int b){
    return a+b;
}

int multiply(int a,int b){
    return a*b;
}



typedef struct query_t
{
    int l;
    int r;
    int  t;
    int  z;
} query_t;

query_t ask[100010];



typedef struct pii
{
    int first;
    int second;
} pii;

typedef struct list
{
    int data;
    struct list *next;
} list;

typedef struct vector_int
{
    
    list *start;
    list *end;
    int n;
} vector_int;

typedef struct mo
{
     int64 ret;
    int cnt[M];
    int  mark[N];
   
} mo; 

void emplace_back(vector_int *v, int value)
{

    list *newList = (list *)malloc(sizeof(list));
    newList->next = NULL;
    newList->data = value;
    (v->end) ? (v->end->next = newList,v->end = newList): (v->end =newList,v->start = newList);
}
int lca(int x, int y);
vector_int edges[N], query[60][60];
int pos[N * 2];int a[N];
int  value[N];
int dfn[N * 2]; 
int st[N];
int ed[N];int  sz;

int fa[N][K + 1], dep[N];
int n, q, B;

void dfs(int u, int p)
{
    dfn[st[u] = ++sz] = u;
    fa[u][0] = p;
    int i = 1;
    
    while ( i < K)
    {
        fa[u][i] = fa[fa[u][i - 1]][i - 1], i++;
    }
    int v;
    list *start = edges[u].start;
    while( start != NULL)
    {
  
        int v = start->data;
         (v != p)? dep[v] = dep[u] + 1, dfs(v, u) : 0;
        
         start = start->next;
    }
    dfn[ed[u] = ++sz] = u;
}



/*

    More information can be found here:
    https://www.youtube.com/watch?v=gUpfwVRXhNY
    Video by : Gaurav Sen
    Took help from senior mentor in understanding algo properly
*/


void add(mo *m, int x)
{
    int v;
    v = value[x];
    if (m->mark[x])
        m->ret = addition(m->ret,-(--m->cnt[v]));
    else
        m->ret = addition(m->ret,m->cnt[v]++);
    m->mark[x] ^= 1;
}
void definition(){
    for (int i = 0; i < N; i++)
    {
        edges[i].n = 0;
        edges[i].start = NULL;
        edges[i].end = NULL;
    }
}
void def1(){
    int i;
    int j;
    for ( i = 0; i < 60; i++)
    {
        for (j = 0; j < 60; j++)
        {
            query[i][j].n = 0;
            query[i][j].start = NULL;
            query[i][j].end = NULL;
        }
    }
}

int main()
{
    definition();
    int i;
    int j;
    def1();

    scanf("%d", &n);
    scanf("%d",&q);
    for (i = 0; i < n; ++i)
    {
        read(a[i]);
    }
    for (i = 1; i < n; ++i)
    {
        int u; int v;
        scanf("%d%d", &u, &v);
        emplace_back(&edges[u], v);
        emplace_back(&edges[v], u);
    }
    sz = 0;
    dep[0] = 0;
    dfs(0, 0);

    for (B = 1; multiply(multiply(B,B), B) < sz; ++B);
    B = multiply(B,B);
    pii modify[N];
    int modify_size = 0;
    for (i = 0; i < q; ++i)
    {
        int op;
        int x;
        int y;
        read(op);
        read(x);
        read(y);
        if (op == 1)
        {
            ask[i].t = -2;
            modify[modify_size].second = y;
            modify[modify_size].first = x;
            modify_size++;
        }
        else
        {
            if (st[x] > st[y])
            {
                int z;
                z = x;
                x = y;
                y = z;
            }
            int l;
            int z;
            z = lca(x, y);
            int r;
            r = st[y];
            if(z==x)
            l=st[x];
            else
            l=ed[x];
            
            ask[i].t = addition(modify_size, - 1);
            if(z==x)
            ask[i].z=-1;
            else
            ask[i].z=z;
            ask[i].l = l;
            ask[i].r = r;
            emplace_back(&query[l / B][r / B], i);
        }
    }
    int64 ret[q];
    int m = (sz - 1) / B + 1;
    for (int i = 0; i < m; ++i)
    {
        for (int j = i; j < m; ++j)
        {
            if (query[i][j].start == NULL)
                continue;
            memcpy(value, a, sizeof(*a) * n);
            mo mo_instance;
            memset(mo_instance.cnt, 0, sizeof(mo_instance.cnt));
            mo_instance.ret = 0;
            memset(mo_instance.mark, 0, sizeof(mo_instance.mark));
            int t = 0;
            int l = 0;
            int r = -1;
            list *start = query[i][j].start;
            while( start != NULL)
            {
                int v = start->data;
                struct query_t qr = ask[v];
                if (qr.r > r)
                {
                    r++;
                    while ( r <= qr.r)
                        add(&mo_instance, dfn[r]), r++;
                    --r;
                }
                while (r > qr.r)
                    add(&mo_instance, dfn[r--]);
                while (l < qr.l)
                    add(&mo_instance, dfn[l++]);
                if (l > qr.l)
                {
                    l--;
                    while ( l >= qr.l)
                        add(&mo_instance, dfn[l]), l--;
                    ++l;
                }
                int x, y;
                while (t <= qr.t)
                {
                    x = modify[t].first;
                    y = modify[t].second;
                    int flag = (qr.l <= st[x] && st[x] <= qr.r) ^ (qr.l <= ed[x] && ed[x] <= qr.r);
                     (flag != 0) ? add(&mo_instance, x) : 0;
                    value[x] = y;
                    (flag != 0) ? add(&mo_instance, x) : 0;
                    t++;
                }
                if (qr.z != -1)
                    add(&mo_instance, qr.z);
                ret[v] = mo_instance.ret;
                if (qr.z != -1)
                    add(&mo_instance, qr.z);
                start = start->next;
            }
        }
    }
    for (int i = 0; i < q; ++i)
    {
        if (ask[i].t == -2)
            continue;
        printf("%lld\n", ret[i]);
    }
    return 0;
}

int lca(int x, int y)
{
    if (y== x)
        return x;
    if (dep[x] < dep[y])
    {
        int z;
        z = x;
        x = y;
        y = z;
    }
    for(int i=0;i<1000;i++){
        i=i+1;
    }
    for (int i = K; ~i; --i)
    {
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    }
    if (x == y)
        return x;
    for (int i = K; ~i; --i)
    {
        if (fa[x][i] == fa[y][i])
            continue;
        y = fa[y][i];
        x = fa[x][i];

    }
    return fa[x][0];
}