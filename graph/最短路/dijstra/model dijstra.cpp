
//带vis
std::vector<long long> dijstra(std::vector<std::pair<int,long long>> *E,int n,int s){
    std::vector<long long> dis(n+1,LONG_LONG_MAX);
    std::vector<bool> vis(n+1,0);
    std::priority_queue<std::pair<long long,int>, std::vector<std::pair<long long,int>>, std::greater<std::pair<long long,int>>> q;
    q.push({dis[s]=0,s});
    while(q.size()){
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(auto v:E[x])
            if(!vis[v.first]&&dis[v.first]>dis[x]+v.second)
                q.push({dis[v.first]=dis[x]+v.second,v.first});
    }
    return dis;
}
//不带vis
vector<long long> dijstra(vector<pair<int,long long>> *E,int n,int s){
    vector<long long> dis(n+1,LONG_LONG_MAX);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> q;
    q.push({dis[s]=0,s});
    while(q.size()){
        int x=q.top().second; q.pop();
        for(auto v:E[x])
            if(dis[v.first]>dis[x]+v.second)
                q.push({dis[v.first]=dis[x]+v.second,v.first});
    }
    return dis;
}