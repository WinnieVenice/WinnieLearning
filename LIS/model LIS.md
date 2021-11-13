# model LIS

```C++
//LIS DP

dp[1]=1;
for(int i=1;i<=n;i++)
    for(int j=1;j<i;j++)
        if(a[i]>a[j]) dp[i]=max(dp[i],dp[j]+1);
for(int i=2;i<=n;i++) dp[i]=max(dp[i],dp[i-1]);

//LIS 贪心二分

int lis(vector<long long int> array){
    int n=array.size();
    vector<long long int> mi_ele(n+1,LONG_LONG_MAX);
    for(auto v:array) *upper_bound(mi_ele.begin(),mi_ele.end(),v)=v;
    return lower_bound(mi_ele.begin(),mi_ele.end(),LONG_LONG_MAX)-mi_ele.begin();
}

int lis(long long int *array,int n){
    vector<long long int> mi_ele(n+1,LONG_LONG_MAX);
    for(int i=0;i<n;i++) *upper_bound(mi_ele.begin(),mi_ele.end(),array[i])=array[i];
    return lower_bound(mi_ele.begin(),mi_ele.end(),LONG_LONG_MAX);
}
```

