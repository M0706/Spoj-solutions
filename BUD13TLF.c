//Manav Garg
//B18BB016
 
#include <stdio.h>
#include<string.h>
 
// referenced Dynamic programming : https://www.geeksforgeeks.org/box-stacking-problem-dp-22/
 
 
#define N 300031
#define MOD 10007
  
 
int tests,n,w[N];
int pref_cost[N];
int W;
int groups_cnt;
int dp[2][103][2031];
int fact[N];
int ts;
int am[N];
int precalc_ways[103][103];
int C[231][231];
int ttl[N];
 
void add(int *a,int b){
    *a+=b;
    if (*a>=MOD)
        *a%=MOD;
}
 
int count_total_ways(){
    int res=1;
    int s=0;
    for (int i=0;i<groups_cnt;i++){
        res=res*C[s+am[i]][am[i]];
        res%=MOD;
        s+=am[i];
    }
    return res;
}
 
void preprocess_groups(){
    for (int i=0;i<=1000;i++){
        ttl[i]=0;
    }
    for (int i=0;i<n;i++){
        ttl[w[i]]++;
    }
    groups_cnt=0;
    for (int i=1000;i>=0;--i){
        if (ttl[i]){
            w[groups_cnt]=i;
            am[groups_cnt]=ttl[i];
            ++groups_cnt;
        }
    }
}
 
int main(){
 
    fact[0]=1;
    for (int i=1;i<=1000;i++){
        fact[i]=fact[i-1]*i%MOD;
    }
 
    for (int i=0;i<=200;i++){
        for(int j=0;j<=i;j++){
            if (j==0||j==i)
                C[i][j]=1;
            else
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
        }
    }
 
    scanf("%d",&tests);
    for (;tests;--tests){
        scanf("%d %d",&n,&W);
        for (int i=0;i<n;i++)
            scanf("%d",&w[i]);
 
        preprocess_groups();
 
        for (int i=0;i<groups_cnt;i++){
            pref_cost[i+1]=pref_cost[i]+w[i]*am[i];
        }
 
        for (int i=0;i<=n;i++){
            for (int j=0;j<groups_cnt;j++){
                long long ways=1;
                int cur_items=i;
                for (int q=groups_cnt-1;q>j;--q){
                    ways=ways*C[cur_items+am[q]][am[q]];
                    ways%=MOD;
                    cur_items+=am[q];
                }
                precalc_ways[i][j]=ways;
            }
        }
 
      
        int ans=0;
        if (pref_cost[groups_cnt]<=W)
            add(&ans,count_total_ways());
 
        for (int items=0;items<=n;items++){
            for (int cur_w=0;cur_w<=W;cur_w++){
                dp[0][items][cur_w]=dp[1][items][cur_w]=0;
            }
        }
 
        dp[0][0][0]=1;
 
        for (int i=0;i<groups_cnt;i++){
 
            for (int j=0;j<=n;j++){
                for (int q=0;q<=W;q++){
                    dp[1-i%2][j][q]=0;
                }
            }
 
            for (int cur_items=0;cur_items<=n;cur_items++){
                for (int cur_w=0;cur_w<=W;cur_w++){
                    if (dp[i%2][cur_items][cur_w]==0)
                        continue;
                    for (int from_this_group=0;from_this_group<=am[i]&&cur_w+w[i]*from_this_group<=W;from_this_group++){
                        int total_w=cur_w+pref_cost[groups_cnt]-pref_cost[i+1]+w[i]*from_this_group;
 
                        int ways_to_finish=dp[i%2][cur_items][cur_w]*
                                precalc_ways[cur_items+from_this_group][i]%MOD*
                                C[cur_items+from_this_group][from_this_group]%MOD;
                        if (total_w<=W&&total_w>W-w[i]&&from_this_group<am[i])
                        {
                            add(&ans,ways_to_finish);
                        }
 
                        int ways_to_take=1ll*dp[i%2][cur_items][cur_w]*C[cur_items+from_this_group][from_this_group]%MOD;
                        add(&dp[1-i%2][cur_items+from_this_group][cur_w+from_this_group*w[i]],ways_to_take);
                    }
                }
            }
        }
        ++ts;
        printf("Case %d: %d \n",ts,ans);
    }
 
    return 0;
} 
 
