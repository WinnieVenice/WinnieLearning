# 静态第K大数

主席树

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod=7+1e9;
ll gcd(ll x,ll y){return y?gcd(y,x%y):x;}
ll lcm(ll x,ll y){return x/gcd(x,y)*y;}
ll qpow(ll a,ll b,ll p){a%=p; ll ret=1;for(;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p; return ret;}
ll getInv(ll x,ll p){return qpow(x,p-2,p);}
const int N=5+2e5;
int n,m,q;
int a[N],b[N];
int tot=0;
int ls[N<<5],rs[N<<5],cnt[N<<5],rt[N];
int init(int l,int r){
    int x=++tot;
    cnt[x]=0;
    if(l==r) return x;
    int mid=(l+r)>>1;
    ls[x]=init(l,mid);
    rs[x]=init(mid+1,r);
    return x;
}
int update(int x,int l,int r,int v){
    int cur=++tot;
    ls[cur]=ls[x];
    rs[cur]=rs[x];
    cnt[cur]=cnt[x]+1;  
    if(l==r) return cur;
    int mid=(l+r)>>1;
    if(v<=mid) ls[cur]=update(ls[cur],l,mid,v);
    else rs[cur]=update(rs[cur],mid+1,r,v);
    return cur;
}
int query(int l,int r,int L,int R,int k){
    if(l==r) return l;
    int mid=(l+r)>>1;
    int x=cnt[ls[R]]-cnt[ls[L]];
    if(x>=k) return query(l,mid,ls[L],ls[R],k);
    else return query(mid+1,r,rs[L],rs[R],k-x);
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) b[i]=a[i];
    m=unique(b+1,b+1+n)-b-1;
    sort(b+1,b+1+m);
    for(int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+1+m,a[i])-b;
    rt[0]=init(1,m);
    for(int i=1;i<=n;i++) rt[i]=update(rt[i-1],1,m,a[i]);
    while(q--){
        int l,r,k; scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",b[query(1,m,rt[l-1],rt[r],k)]);
    }
}
```

