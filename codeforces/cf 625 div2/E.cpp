#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5+2e5;
int n,m,k;
pair<ll,ll> a[maxn],b[maxn];
pair<pair<ll,ll>,ll> p[maxn];

struct SegmentTree{
    #define ls (cur<<1)
    #define rs (cur<<1|1)
    #define type_data long long 
    static const int maxsize=5+2e5;
    int size; 
    type_data unit[maxsize],sg[maxsize<<2],mk[maxsize<<2];
    inline type_data root(){
        return sg[1];
    }
    inline void push_back(int cur){
        return sg[cur]=max(sg[ls],sg[rs]),void();
    }
    inline void push_down(int cur){
        if(mk[cur]){
            mk[ls]+=mk[cur];
            mk[rs]+=mk[cur];
            sg[ls]+=mk[cur];
            sg[rs]+=mk[cur];
            mk[cur]=0;
        }
    }
    inline void build(int cur,int l,int r){
        if(l==r)
            return sg[cur]=unit[l],void();
        int mid=(l+r)>>1;
        build(ls,l,mid);
        build(rs,mid+1,r);
        push_back(cur);
    }
    inline void init(type_data v[],int l,int r){
        size=r-l+1;
        for(int i=l;i<=r;i++)
            unit[i-l+1]=v[i];
        build(1,1,size);
    }
    inline void updata_unit(int cur,int l,int r,int p,type_data v){
        if(l==r&&l==p)
            return sg[cur]=v,void();
        push_down(cur);
        int mid=(l+r)>>1;
        if(p<=mid)
            updata_unit(ls,l,mid,p,v);
        else
            updata_unit(rs,mid+1,r,p,v);
        push_back(cur);
    }
    inline void update_range(int cur,int l,int r,int L,int R,type_data v){
        if(l>=L&&r<=R){
            mk[cur]+=v;
            sg[cur]+=v;
        }else{
            push_down(cur);
            int mid=(l+r)>>1;
            if(L<=mid)
                update_range(ls,l,mid,L,R,v);
            if(mid<R)
                update_range(rs,mid+1,r,L,R,v);
            push_back(cur);
        }
    }
    inline type_data query_range(int cur,int l,int r,int L,int R){
        if(l>=L&&r<=R)
            return sg[cur];
        else{
            push_down(cur);
            int mid=(l+r)>>1;
            type_data res;
            if(L<=mid)
                res=max(res,query_range(ls,l,mid,L,R));
            if(mid<R)
                res=max(res,query_range(rs,mid+1,r,L,R));
            return res;
        }
    }
}seg;
bool cmp1(pair<ll,ll> x,pair<ll,ll> y){
    if(x.first!=y.first)
        return x.first<y.first;
    else
        return x.second<y.second;
}
bool cmp2(pair<pair<ll,ll>,ll> x,pair<pair<ll,ll>,ll> y){
    if(x.first!=y.first){
        if(x.first.first!=y.first.first)
            return x.first.first<y.first.first;
        else
            return x.first.second<x.first.second;
    }else
        return x.second<y.second;
}
long long cb[maxn];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        ll x,y;
        cin>>x>>y;
        a[i]={x,y};
    }
    for(int i=1;i<=m;i++){
        ll x,y;
        cin>>x>>y;
        b[i]={x,y};
    }
    for(int i=1;i<=k;i++){
        ll x,y,z;
        cin>>x>>y>>z;
        p[i]={{x,y},z};
    }
    sort(a+1,a+1+n,cmp1);
    sort(b+1,b+1+m,cmp1);
    sort(p+1,p+1+k,cmp2);
    for(int i=1;i<=m;i++)
    	cb[i]=-b[i].second;
    seg.init(cb,1,m);
    ll ans=-1e18L;
    for(int i=1,j=1;j<=n;j++){
        while(i<=k&&a[j].first>p[i].first.first){
            int l=1,r=m,tmp=m+1;
            while(l<=r){
                int mid=(l+r)>>1;
                if(b[mid].first>p[i].first.second){
                    tmp=mid;
                    r=mid-1;
                }else
                    l=mid+1;
            }
            if(tmp<=m)
                seg.update_range(1,1,m,tmp,m,p[i].second);
            i++;
        }
        ans=max(ans,seg.root()-a[j].second);
    }
    cout<<ans<<endl;
}