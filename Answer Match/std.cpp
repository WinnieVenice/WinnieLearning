#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long 
using namespace std;
const int maxn = 1e6 + 10;
int N, cnt = 0;
ll int x1, x2, y1, y2, X[maxn << 1];
struct scanline{
	ll l, r, h;
	int mark;//保存权值
	bool operator <(const scanline &te)const{
		return h  < te.h;
	} 
}line[maxn << 1];

struct tree{
	int l, r, sum;
	//sum:被完全覆盖的次数
	//len:区间被截的长度 
	ll len;	
}st[maxn << 2];

void build(int o, int l, int r){
	st[o].l	= l, st[o].r = r;
	st[o].len = 0;
	st[o].sum = 0;
	if(l == r)return;
	int mid = (l + r) >> 1;
	build(o << 1, l, mid);
	build(o << 1|1, mid + 1, r);
}
void pushup(int o){
	int l = st[o].l, r = st[o].r;
	if(st[o].sum)st[o].len = X[r + 1] - X[l];//已经被覆盖了，更新长度 
	else{st[o].len = st[o << 1].len + st[o << 1 |1].len;}
}
void change(int o, ll L, ll R, int c){
	int l = st[o].l, r = st[o].r;
	//l,r代表o这个点的范围，L,R意义是待修改的区间
	if( X[r + 1] <= L || R <= X[l] )return;
	//当右区间 + 1小于左区间， 
	if(L <= X[l] && X[r + 1] <= R){
		st[o].sum += c;
		pushup(o);
		return;
	}
	change(o << 1, L, R, c);
	change(o << 1 | 1, L, R, c);
	pushup(o);
}
int main(){
	scanf("%d",&N);
	for(int i = 1; i <= N; i++){
		cin>>x1>>y1>>x2>>y2;
		X[2 * i - 1] = x1, X[2 * i] = x2;
		line[2 * i - 1] = (scanline){ x1, x2, y1, 1};
		line[2 * i] = (scanline){ x1, x2, y2, -1};
	}
	N = N << 1;
	sort(line + 1, line + N +1);
	sort(X + 1, X + N + 1);
	int tot = unique(X + 1, X + N + 1) - (X + 1);
	build(1, 1 , tot - 1);
	//右端点的对应关系已经被修改了,我们用 
	//[1,tot - 1]描述的是[x[1],x[tot]] 
	ll ans = 0;
	for(int i = 1; i < N; i++){
    cout << i << ' ' << line[i].l << ' ' << line[i].r << ' ' << line[i].mark << '\n';
		change(1, line[i].l,line[i].r,line[i].mark);
    cout << st[1].len << ' ' << line[i + 1].h - line[i].h << '\n';
		ans += st[1].len *(line[i + 1].h - line[i].h);
	}
	cout<<ans;
}