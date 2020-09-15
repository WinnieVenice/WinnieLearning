#include<bits/stdc++.h>
using namespace std;
int n,m,k;
vector<long long> init(vector<long long> x){
    vector<long long> res(x.size()+1);
    for(int i=0,j=0;i<x.size();){
        while(x[i]==0){
            i++;
            continue;
        }
        j=i;
        while(j<x.size()&&x[j]==1)
            j++;
        for(int k=1;k<=j-i;k++)
            res[k]+=j-i-k+1;
        i=j;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    vector<long long> y(n),x(m);
    for(int i=0;i<n;i++)
        cin>>y[i];
    for(int i=0;i<m;i++)
        cin>>x[i];   
    vector<long long> cnty=init(y);
    vector<long long> cntx=init(x);
    long long ans=0;
    for(int i=1;i<cnty.size();i++)
        if(k%i==0&&k/i<=m)
            ans+=cnty[i]*cntx[k/i];
    cout<<ans<<endl;
}