#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<ctime>
#include<algorithm>
#include<cmath>
#include<queue>
#include<set>
#include<stack>
#include<vector>
#include<bitset>
#define ll long long 
#define ull unsigned long long 
#define mem(a) memset(a,0,sizeof(a))
#define rint register int 
#define rll register long long 
#define rull register unsigned long long 
#define rchar register char
#define rstring register string 
#define rfloat register float
#define rdouble register double 
#define fio ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define For(i,a,b) for(int i=a;i<b;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define cFor(i,a,b) for(int i=a;i>b;i--)
#define cFOR(i,a,b) for(int i=a;i>=b;i--)
#define lFor(i,a,b) for(ll i=a;i<b;i++)
#define lFOR(i,a,b) for(ll i=a;i<=b;i++)
#define lcFor(i,a,b) for(ll i=a;i>b;i--)
#define lcFOR(i,a,b) for(ll i=a;i>=b;i--)
#define watch(a) cout<<#a<<"="<<a<<endl
#define mkp(a,b) make_pair(a,b)
#define inthis cout<<"--------this\n"
#define pr(a,b) pair(a,b)
#define iset(a) set<a>::iterator 
#define imap(a,b) map<a,b>::iterator 
#define vec vector
#define fi first
#define se second
#define _vec vector<int>
#define __vec vector<vector<int>> 
#define pb push_back
#define mp map
#define _pr pair<int,int>
#define ins insert
#define era erase
#define fin find
#define EXIT exit(0)
#define all(a) a.begin(),a.end()
using namespace std;
using namespace std;  
const int maxn = 105;   
const int M = 9973;  
struct Matrix{  
    int n,m;  
    int v[maxn][maxn];  
    Matrix(int n,int m):n(n),m(m){}  
    void init(){                    
        memset(v,0,sizeof v);  
    }  
    Matrix operator* (const Matrix B) const {  
        Matrix C(n,B.m);             
        C.init();  
        for(int i = 0;i < n;i++)  
        for(int j = 0;j < B.m;j++)  
        for(int k = 0;k < m;k++)       
            C.v[i][j] = (C.v[i][j] + v[i][k]*B.v[k][j] % M) % M;  
        return C;  
    }  
    void print(){ 
        for(int i = 0;i < n;i++){  
        for(int j = 0;j < m;j++)  
            cout << v[i][j] << " ";  
        cout << endl;  
        }  
    }  
};  
Matrix q_pow(Matrix& A,int b,int M){  
    Matrix C(A.n,A.m);  
    C.init();  
    for(int i = 0;i < C.n;i++)   C.v[i][i] = 1;  
    while(b){  
        if(b&1) C = C*A;  
        A = A*A;  
        b >>= 1;  
    }  
    return C;  
}  

int main(){
	fio;
	int t;
	cin>>t;
	while(t--){
		int n,k;
		cin>>n>>k;
		Matrix a(n,n);
		For(i,0,n)
			For(j,0,n)
				cin>>a.v[i][j];
		Matrix res(n,n);
		res=q_pow(a,k,M);
		int ans=0;
		For(i,0,n)
			ans=(ans+res.v[i][i])%M;
		cout<<ans<<endl;			
	}
}
