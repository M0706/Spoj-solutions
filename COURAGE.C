#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <limits.h>
#include <math.h> 
typedef long long ll; 
#define ll_MAX 10000000000000;
 
ll minVal(ll x, ll y) { return (x < y)? x: y; } 
 
ll getMid(ll s, ll e) {  return s + (e -s)/2;  } 
 
ll getSumUtil(ll *st, ll ss, ll se, ll qs, ll qe, ll si) 
{ 
    // If segment of this node is a part of given range, then return 
    // the sum of the segment 
    if (qs <= ss && qe >= se) 
        return st[si]; 
  
    // If segment of this node is outside the given range 
    if (se < qs || ss > qe) 
        return 0; 
  
    // If a part of this segment overlaps with the given range 
    ll mid = getMid(ss, se); 
    return getSumUtil(st, ss, mid, qs, qe, 2*si+1) + 
           getSumUtil(st, mid+1, se, qs, qe, 2*si+2); 
} 
 
void updateValueUtil(ll *st, ll ss, ll se, ll i, ll diff, ll si) 
{ 
	// Base Case: If the input index lies outside the range of 
	// this segment 
	if (i < ss || i > se) 
		return; 
 
	// If the input index is in range of this node, then update 
	// the value of the node and its children 
	st[si] = st[si] + diff; 
	if (se != ss) 
	{ 
		ll mid = getMid(ss, se); 
		updateValueUtil(st, ss, mid, i, diff, 2*si + 1); 
		updateValueUtil(st, mid+1, se, i, diff, 2*si + 2); 
	} 
} 
void updateValuemin(ll arr[], ll* st, ll ss, ll se,  
 
                 ll index, ll value, ll node) 
{ 
 
    if (index < ss || index > se)  
    { return; } 
    if (ss == se)  
    {
        arr[index] = value; 
        st[node] = value; 
    } 
 
    else { 
 
            ll mid = getMid(ss, se); 
            if (index >= ss && index <= mid) 
                updateValuemin(arr, st, ss, mid, index, value, 2 * node + 1); 
 
            else
                updateValuemin(arr, st, mid + 1, se,index, value, 2 * node + 2); 
            st[node] = minVal(st[2 * node + 1], st[2 * node + 2]); 
             } 
     return; 
} 
 
 
 
void updateValue(ll arr[], ll *st, ll n, ll i, ll new_val,ll which) 
{ 
	// Check for erroneous input index 
	if (i < 0 || i > n-1) 
	{ 
		//prllf("Invalid Input"); 
		return; 
	} 
   
    if(which==0){ 
 
	updateValueUtil(st, 0, n-1, i, new_val-arr[i], 0); 
    }
    else{
      updateValuemin(arr,st, 0, n-1, i, new_val, 0); 
    }
} 
ll getSum(ll *st, ll n, ll qs, ll qe) 
{ 
	// Check for erroneous input values 
	if (qs < 0 || qe > n-1 || qs > qe) 
	{ 
		//prllf("Invalid Input"); 
		return -1; 
	} 
 
	return getSumUtil(st, 0, n-1, qs, qe, 0); 
} 
 
ll segmentparts(ll *st, ll ss, ll se, ll qs, ll qe, ll index) 
{ 
    // If segment of this node is a part of given range, then return the min of the segment 
    if (qs <= ss && qe >= se) 
        return st[index]; 
  
    // If segment of this node is outside the given range 
    if (se < qs || ss > qe) 
        return ll_MAX; 
  
    // If a part of this segment overlaps with the given range 
    ll mid = getMid(ss, se); 
    return minVal(segmentparts(st, ss, mid, qs, qe, 2*index+1), 
                  segmentparts(st, mid+1, se, qs, qe, 2*index+2)); 
} 
ll RMQ(ll *st, ll n, ll qs, ll qe) 
{ 
    // Check for erroneous input values 
    if (qs < 0 || qe > n-1 || qs > qe) 
    {  
        return -1; 
    } 
  
    return segmentparts(st, 0, n-1, qs, qe, 0); 
} 
ll constructST1(ll arr[], ll ss, ll se, ll *st, ll si,ll which)  // for sum
{ 
	if (ss == se) 
	{ 
		st[si] = arr[ss]; 
		return arr[ss]; 
	} 
	ll mid = getMid(ss, se); 
    if(which==0){
	st[si] = constructST1(arr, ss, mid, st, si*2+1,which) + 
			constructST1(arr, mid+1, se, st, si*2+2,which); 
	return st[si]; 
    }
    else{
    st[si] =  minVal(constructST1(arr, ss, mid, st, si*2+1,which), 
                     constructST1(arr, mid+1, se, st, si*2+2,which)); 
    return st[si]; 
    }
} 
ll *constructSTmem1(ll arr[], ll n,ll which) //for sum 
{ 
	// Allocate memory for the segment tree 
 
	//Height of segment tree 
	ll x = (ll)(ceil(log2(n))); 
 
	//Maximum size of segment tree 
	ll max_size = 2*(ll)pow(2, x) - 1; 
 
	// Allocate memory 
	ll *st = (ll*)malloc(sizeof(ll)*1000000); 
 
	// Fill the allocated memory st 
	constructST1(arr, 0, n-1, st, 0,which); 
 
	// Return the constructed segment tree 
	return st; 
} 
int main(){
    ll number;
    ll apples[100000];
    scanf("%lld",&number);
    ll num;
    for(ll i=0;i<number;i++){
        scanf("%lld",&num);
        apples[i]=num;
        num=0;
    }
    ll test;
    scanf("%lld",&test);
    ll length = sizeof(apples) / sizeof(apples[0]); 
    ll *st1 = constructSTmem1(apples,length,0);
    ll *st2 = constructSTmem1(apples,length,1);
    while(test--){
        
        char c[8];
        scanf("%s",c);
        if (strcmp(c, "GROW") == 0){
            ll x,y;
            scanf("%lld ",&x);
            scanf("%lld ",&y);
            //apples[y]=apples[y]+x;
            //prllf("%d \n",y);
           updateValue(apples,st1,length,y,apples[y]+x,0);
           //prllf("%d \n",getSum(st1, length,2,4));
           updateValue(apples,st2,length,y,apples[y]+x,1);
        }
        else if(strcmp(c,"EAT")==0){
             ll x,y;
            scanf("%lld ",&x);
            scanf("%lld ",&y);
            //apples[y]=apples[y]-x;
            updateValue(apples,st1,length,y,apples[y]-x,0);
            updateValue(apples,st2,length,y,apples[y]-x,1);
        }
        else{
            ll x,y;
            scanf("%lld ",&x);
            scanf("%lld ",&y);
            
            //ll *st2=constructSTmem2(apples,length);
            ll sum1=getSum(st1, length, x,y);
            //prllf("%d \n",sum1);
            //ll *st2 = constructSTmem1(apples,length,1);
            ll minele=RMQ(st2, length, x, y);
            //prllf("%d \n",minele);
            ll finalval=sum1-minele;
            printf("%lld \n",finalval);
 
 
        }
        
    }
} 