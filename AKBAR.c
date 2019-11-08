#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

typedef long long ll;
typedef struct queue{
    int front;
    int rear;
    int items[1000000];
}queue ;

int isEmpty(queue* q) {
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}
void enqueue(queue *q,int value){
    if(q->front == -1)
            q->front = 0;
    q->items[++q->rear] = value;
}
int dequeue(queue *q){
    int item = -1;
    if(isEmpty(q)==0){
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear)
            q->front = q->rear = -1;
    }
    return item;
}
queue* createQueue() {
    queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}


typedef struct node
{
  ll dest;
  struct node *next;
}node;
struct list
{
  struct node *start;
};
struct Graph
{
  ll v;
  struct list *a;
};
struct Graph *create_graph(ll vertices)
{
  if (vertices == 0)
  {
    return NULL;
  }
  struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
  g->v = vertices;
  g->a = (struct list *)malloc((vertices) * sizeof(struct list));
  ll i;
  for (i = 0; i < vertices; i++)
  {
    g->a[i].start = NULL;
  }
  return g;
}
void addedge(struct Graph *g, ll source, ll destination)
{
  // Add an edge from src to dest
  struct node *ptr1 = (struct node *)malloc(sizeof(struct node));
  ptr1->dest = destination;
  ptr1->next = g->a[source].start;
  g->a[source].start = ptr1;

  // Since graph is undirected, add an edge from 
    // dest to src also 
  struct node *ptr2 = (struct node *)malloc(sizeof(struct node));
  ptr2->dest = source;
  ptr2->next = g->a[destination].start;
  g->a[destination].start = ptr2;
}
int bfs(struct Graph* graph,int soldier[],int n)
{
    char count[n+1];
    
    memset(count, 0, sizeof(count));
    // memset(dist, 0, sizeof(dist));
    for (int i = 1; i < n+1; i++)
    {
        if(soldier[i] == -1) continue;
        if(count[i]) {
            // printf("%d frf\n", i);
            return 0;
        }
        count[i] = 1;
        int q[2*n], f = 0, r = 0;
        int dist[n+1];
        char vis[n+1];
        memset(vis, 0, sizeof(vis));
        dist[i] = 0;
        
        q[r++] = i;
        vis[i] = 1;
        while(f < r) {
            int curr = q[f++];
            
            node* nb = graph->a[curr].start;
            if(dist[curr] == soldier[i]) continue;
            while(nb) {
                if(vis[nb->dest]) {
                    nb = nb->next; continue;
                }
                if(count[nb->dest]){
                        //  printf("%d %d %d fff\n", i, curr, nb->dest);
                        return 0;
                }
                count[nb->dest] = 1;
                dist[nb->dest] = dist[curr] + 1;
                q[r++] = nb->dest;
                vis[nb->dest] = 1;
                nb = nb->next;
            }
        }
    } 
    for (int i = 1; i < n+1; i++)
    {
        if(count[i] != 1) return 0;
    }
    
    return 1;
}



int main(){
    int test;
    scanf("%d",&test);
    while(test--){
        int yes=1;
        int N,R,M;  //N:no. of cities, R:paths , M:soldiers
        scanf("%d %d %d",&N,&R,&M);
        struct Graph* graph=create_graph(N+1);
        for(int i=0;i<R;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            addedge(graph,a,b);
        }
        int soldier[N+1];
        // for(int i=0;i<M;i++){
        //     int k,s;
        //     scanf("%d %d",&k,&s);
        //     k--;
        // }
        memset(soldier, -1, sizeof(soldier));
        for (int i = 0; i < M; i++)
        {
            int x, s; scanf("%d %d",&x,&s);
            if(soldier[x] != -1) {
                yes = 0; break;
            }
            soldier[x] = s;
        }
        if(yes && bfs(graph, soldier, N)) printf("Yes\n");
        else printf("No\n");
    }
        
        
}





