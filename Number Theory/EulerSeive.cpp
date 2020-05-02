/*--WinnieVenice--*/


//欧拉筛(附带筛欧拉函数和莫比乌斯函数前缀和)-带模
typedef long long ll;
const int N=2e6;//欧拉筛的规模
const int mod=7+1e9;
ll add(ll &x,ll y){//模加法
    x+=y;
    if(x>=mod) x-=mod;
    return x;
}
ll sub(ll &x,ll y){//模减法
    x-=y;
    if(x<mod) x+=mod;
    return x;
}
struct EulerSeive{
    int sz;//规模
    vector<bool> vis;
    vector<int> pri;//质数筛
    vector<ll>phi,miu;
    EulerSeive(int n):sz(n),vis(n,0),phi(n,0),miu(n,0){init();}
    inline void init(){
        vis[0]=vis[1]=1;
        phi[1]=miu[1]=1;
        for(int i=2;i<sz;i++){
            if(!vis[i]){
                vis[i]=1;
                pri.push_back(i);
                phi[i]=i-1;
                miu[i]=-1;
            }
            for(int j=0;j<(int)pri.size()&&i*pri[j]<sz;j++){
                vis[i*pri[j]]=1;
                //下面欧拉筛筛质数都可以不要
                if(i%pri[j]==0){
                    phi[i*pri[j]]=phi[i]*pri[j];
                    break;
                }
                phi[i*pri[j]]=phi[i]*phi[pri[j]];
                miu[i*pri[j]]=-miu[i];
            }
        }
        for(int i=2;i<sz;i++){//欧拉函数和莫比乌斯函数前缀和
            add(phi[i],phi[i-1]);
            add(miu[i],miu[i-1]);
        }
    }
}es(N);

