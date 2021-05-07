# 枚举C(k,n)

枚举朴素算法：枚举出C(k,n)中所有的组合(k<=n) 

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1+1e6;
int a[MAXN]; 
void from_max_to_min(int k,int n,int idx){// k表示当前还剩多少个要选择;n表示当前待选区中的最大值;idx表示当前赋值的是组合中的哪个下标 
	if(!k){//当k==0,代表一次组合被完全选择完毕,输出当前a[]中的所有元素,即：一次组合中的选择 
		for(int i=1;i<idx;i++)
			cout<<a[i]<<' ';
		cout<<endl;	 
	}
	else{
		for(int i=n;i>=k;i--){//对于每种组合中的每次选择我们有很多种选择,但是由于是无序的,所以我们可以人为的调序为从大到小(或从小到大),每次选择我们都选择当前未被选择中的最大(小)值,由于当前我们要选择k个,所以最后一种情况一定是k,k-1,...,1,故i>=k; 
			a[idx]=i;
			from_max_to_min(k-1,i-1,idx+1);//当前选择完毕,进入下一次选择,由于选择了i为当前最大值,那下一次的最大值至多是i-1 
		}
	}
}
void from_min_max(int q,int k,int idx,int n){//同理我们可以写出从小到大的全组合 
	if(!k){
		for(int i=1;i<idx;i++)
			cout<<a[i]<<' ';
		cout<<endl;	
	}
	else{     
		for(int i=q;i<=n-k+1;i++){
			a[idx]=i;
			from_min_to_max(i+1,k-1,idx+1,n);
		}
	}
}
int main(){
	int k,n;
	cin>>k>>n;
	from_max_to_min(k,n,1);	
}
```

