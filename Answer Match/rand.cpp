#include<bits/stdc++.h>
#include<random>
#define random(a,b) (int)a + rand()%((int)b - (int)a + 1)
using namespace std;

signed main() {
    srand((unsigned)time(NULL));
    int n = random(1, 10);
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        int x1 = random(0, 1e9), y1 = random(0, 1e9), x2 = random(x1 + 1, 1e9), y2 = random(y1 + 1, 1e9);
        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
    }


}