#include<bits/stdc++.h>
using namespace std;
struct Dijstra{
    #define type_data long long
    #define upper_bound 1e18L
    static const int maxsize=5+2e5;
    int size;
    vector<pair<type_data,int>> V[maxsize];
    type_data d[maxsize];
    int pa[maxsize];
    priority_queue<pair<type_data,int>,vector<pair<type_data,int>>,greater<pair<type_data,int>>> q;
    inline void dijstra(vector<pair<type_data,int>> a[],int n,int start){
        assert(start<=n);
        size=n;
        for(int i=1;i<=n;i++){
            V[i]=a[i];
            d[i]=upper_bound;
        }
        d[start]=0;
        q.push({0,start});
        while(q.size()){
            int cur=q.top().second;
            q.pop();
            for(int i=0;i<V[cur].size();i++)
                if(d[V[cur][i].second]>d[cur]+V[cur][i].first){
                    d[V[cur][i].second]=d[cur]+V[cur][i].first;
                    pa[V[cur][i].second]=cur;
                    q.push({d[V[cur][i].second],V[cur][i].second});
                }
        }
    }
}dij;
const int maxn=5+2e5;
int n,m;
vector<pair<long long,int>> G[maxn];
vector<int> ans;
void traceback(){
	ans.push_back(n);
	int cur=dij.pa[n];
	if(!cur){
		cout<<"-1\n";
		exit(0);
	}
	while(cur){
		ans.push_back(cur);
		cur=dij.pa[cur];
	}
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        G[u].push_back({w,v});
        G[v].push_back({w,u});
    }    
    dij.dijstra(G,n,1);
    traceback();
    for(int i=ans.size()-1;i>=0;i--)
        cout<<ans[i]<<' ';
    cout<<endl;
}