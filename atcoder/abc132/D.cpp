#include<bits/stdc++.h>
using namespace std;
const int inf=7+1e9,maxn=5+2e4;
typedef unsigned long long ll;
ll dp[maxn];
ll qpow(ll a,ll p){
	ll ans=1,tmp=a;
	while(p){
		if(p&1)
			ans=ans*tmp%inf;
		tmp=tmp*tmp%inf;
		p>>=1;	
	}
	return ans;
}
ll C(ll m,ll n){
	return dp[n]*qpow(dp[m]*dp[n-m]%inf,inf-2)%inf;
}
int main(){
	ll n,k;
	cin>>n>>k;
	//BLUE:C(i-1,k-1);RED:C(i,n-k+1);T0TAL:C(i,k-1)*C(i,n-k+1)
	//5 3
	//1:C(0,2)*C(1,3)=3;2:C(1,2)*C(2,3)=2*3=6;C(2,2)*C(3,3)=1
	memset(dp,0,sizeof(dp));
	dp[0]=1;
	for(ll i=1;i<=2005;i++)
		dp[i]=dp[i-1]*i%inf;
	/*
	for(ll i=1;i<=2000;i++)
		cout<<"dp["<<i<<"]="<<dp[i]<<endl;		
	*/
	for(ll i=1;i<=k;i++){
		if(i-1>n-k)
			cout<<"0\n";
		else	
			cout<<C(i-1,k-1)*C(i,n-k+1)%inf<<endl;
	}
		
}
