#define ll long long
const ll mo=1e9+7;
ll C[1005][1005];//C(n,m)=C[n][m]
void getC(int n){
    for(int i=0;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(j==0||j==i)
                C[i][j]=1;
            else
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%mo;
        }
    }
}