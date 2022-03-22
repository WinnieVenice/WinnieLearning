# dijstra

## vis

```C++
template<typename T, typename Graph>
std::vector<T> dijstra(Graph E, int n, int s, T inf){
    std::vector<T> dis(n + 1, inf);
    std::vector<bool> vis(n + 1, 0);
    std::priority_queue<std::pair<T,int>, std::vector<std::pair<T,int>>, std::greater<std::pair<T, int>>> q;
    q.push({dis[s] = 0, s});
    while(!q.empty()){
        int x = q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        for(auto &v: E[x])
            if(!vis[v.first] && dis[v.first] > dis[x] + v.second)
                q.push({dis[v.first] = dis[x] + v.second, v.first});
    }
    return dis;
}
```

## not vis

```C++
template<typename T, typename Graph>
std::vector<T> dijstra(Graph E, int n, int s, T inf){
    std::vector<T> dis(n + 1, inf);
    std::priority_queue<std::pair<T,int>, std::vector<std::pair<T,int>>, std::greater<std::pair<T, int>>> q;
    q.push({dis[s] = 0, s});
    while(!q.empty()){
        int x = q.top().second; q.pop();
        for(auto &v: E[x])
            if(dis[v.first] > dis[x] + v.second)
                q.push({dis[v.first] = dis[x] + v.second, v.first});
    }
    return dis;
}
```

