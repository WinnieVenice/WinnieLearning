#include<bits/stdc++.h>
#include<random>
#include<chrono>

using namespace std;
#define random(a,b) ((a)+rand()%((b)-(a)+1))

stringstream ss;
int main( int argc, char *argv[] )
{
	ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int seed=time(NULL);
	if(argc)
	{
		ss.clear();
		ss<<argv[1];
		ss>>seed;
	}
	std::mt19937 rng(seed);
	std::uniform_int_distribution<long long> range(0, 100000);
	std::uniform_int_distribution<long long> range1(1, 1000000);
	int T=1;
	//cout << T << endl;
	//printf("%d\n",T);
	while(T--){
		int q = 100000; std::cout << q << '\n';
		for (int i = 0; i < q; i++) {
			std::cout << range(rng) << ' ' << range1(rng) << '\n';
		}
		/*
		int n = random(2, 10), m = random(1, 10);
		printf("%d %d\n", m, n);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d ", random(1, 100));
			}
			printf("\n");
		}
		*/
	}
	return 0;
}
