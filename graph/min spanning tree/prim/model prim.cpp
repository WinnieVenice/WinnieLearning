
pair<long long,bool> Prim(vector<pair<int,long long>> *E,int n){
    vector<long long> dis(n+1,LONG_LONG_MAX);
    vector<bool> vis(n+1,0);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> q;
    q.push({dis[1]=0,1});
    for(int e=0;e<n&&q.size();){
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        e++;
        for(auto v:E[x]){
            if(!vis[v.first]&&dis[v.first]>v.second){
                dis[v.first]=v.second;
                q.push({dis[v.first],v.first});
            }
        }
    }
    for(int i=1;i<=n;i++)
        if(!vis[i]) return {0,0};
    long long sum=0;
    for(int i=1;i<=n;i++) sum+=dis[i];
    return {sum,1};
}