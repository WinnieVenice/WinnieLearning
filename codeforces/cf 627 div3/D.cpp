#include<bits/stdc++.h>
using namespace std;
const int maxn=5+2e5;
pair<long long,long long> a[maxn];
bool cmp(pair<long long,long long> x,pair<long long,long long> y){
    if(x.first!=y.first)
        return x.first<y.first;
    else
        return x.second<y.second;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i].first;
    for(int i=1;i<=n;i++){
        cin>>a[i].second;
        a[i].first-=a[i].second;
    }
    sort(a+1,a+n+1,cmp);
    long long ans=0;
    for(int i=1;i<n;i++){
        int l=i+1,r=n;
        int res=n+1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(a[i].first+a[mid].first>0){
                res=mid;
                r=mid-1;
            }else
                l=mid+1;
        }
        ans+=n-res+1;
    }
    cout<<ans<<endl;
}