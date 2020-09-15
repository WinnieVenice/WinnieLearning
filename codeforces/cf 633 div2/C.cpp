//
#include<bits/stdc++.h>
using namespace std;
const int N=5+1e5;
int n,a[N],b[N];
bool ck(int x){
    int res=0;
    for(int i=0;i<x;i++)//当前二分答案1111类型的数,长度是x-1
        res+=(1<<i);
    //cout<<"res: "<<res<<'\n';
    for(int i=0;i<n;i++) b[i]=a[i];
    for(int i=1;i<n;i++){
        if(b[i]>=b[i-1])
            continue;
        if(b[i-1]-b[i]<=res){
            //cout<<"b["<<i-1<<"],b["<<i<<"],dis: "<<b[i-1]-b[i]<<",res: "<<res<<'\n';
            b[i]+=b[i-1]-b[i];
            continue;
        }
        return 0;
    }
    return 1;
}
void solve(){
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",a+i);
    int l=0,r=31;
    int ret=0;
    while(l<=r){//二分答案
        int mid=(l+r)>>1;//mid表示当前二分答案
        if(ck(mid)){
            //cout<<"yes: "<<mid<<'\n';
            ret=mid;
            r=mid-1;
        }else
            l=mid+1;
    }
    printf("%d\n",ret);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--)
        solve();
}