#pragma GCC optimize(2)
#include<bits/stdc++.h>
#include<chrono>
#include<random>
#define endl '\n'
using namespace std;
#define MT make_tuple
void debug() { cerr << endl; } template <typename T, typename... Ts> void debug(T x, Ts... y) { cerr << "\033[31m" << x << "\033[0m"; if (sizeof...(y) > 0) cerr << ' '; debug(y...); } template <typename T> void debug(const T& a, int l, int r, char c) { for (int i = l; i <= r; ++i) cerr << "\033[31m" << a[i] << "\033[0m" << (i == r ? '\n' : c); } template <typename T> void debug(vector<T> a) { for (int i = 0; i < (int)a.size(); ++i) cerr << "\033[31m" << a[i] << "\033[31m" << " \n"[i == ((int)a.size() - 1)]; }


const int N=5e5;
vector<string>s;
vector<int>id;
signed main() {
  //ofstream cout("E:\\acm dream\\2022 contest\\kizuna\\data\\9.in");
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  #ifdef BADDOG_LOCAL
  //ifstream cin("E:\\acm dream\\in.in");
  double be = clock();
  #endif

  mt19937 rd(chrono::system_clock::now().time_since_epoch().count());
  uniform_int_distribution<int>dist(1,10);

  string t="";
  uniform_int_distribution<int>rnd1(0,25);
  uniform_int_distribution<int>rnd2(1,10);
  uniform_int_distribution<int>rnd3(0,10);
  for(int i=0;i<N;++i)t+=rnd1(rd)+'a';
  //cout<<t;
  int n=rnd2(rd);
  set<int>st;
  while(st.size()<n){
    int x=rnd3(rd);
    st.insert(x);
  }
  s.push_back(t.substr(0,*st.begin()+1));
  for(auto it=next(st.begin());it!=st.end();++it){
    int x=*prev(it),y=*it;
    s.push_back(t.substr(x+1,y-x));
  }
  //s.push_back(t.substr(*st.rbegin()+1,N-*st.rbegin()-1));
  map<string,int>col;
  for(auto it:s){
    if(!col.count(it))col[it]=rnd2(rd);
  }
  for(int i=0;i<n;++i){
    id.push_back(col[s[i]]);
  }
  cout<<n<<endl;
  for(auto it:s)cout<<it<<endl;
  for(auto it:id)cout<<it<<' ';

  #ifdef BADDOG_LOCAL
  double en = clock();
  //cout<<"\ntime: "<<fixed<<setprecision(8)<<en-be;
  #endif
  return 0;
}
// init?
// var->0?
// infinite dfs?
// out of bound?
// max_element / min_element?