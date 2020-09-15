/*--WinnieVenice--*/

typedef long long ll;
pair<ll,ll> exgcd(ll a,ll b){ //pair(x,y)
    if(!b) return {1,0};
    else{
        pair<ll,ll> ret=exgcd(b,a%b);
        return {ret.second,ret.first-a/b*ret.second};
    }
}