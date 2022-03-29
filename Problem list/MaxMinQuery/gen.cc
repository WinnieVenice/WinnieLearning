#include "/mnt/d/Ccode/CPP/testlib/testlib.h"
#include <iostream>
#include <algorithm>
#include <vector>

// argv = [ __name__, testCase, n, q(, max_ai) ]
int main(int argc, char **argv) {
    if (argc < 4) {
        std::cerr << "Err.";
        return 0;
    }

    registerGen(argc, argv, 1);
    startTest(atoi(argv[1]));

    int n = atoi(argv[2]), q = atoi(argv[3]);

    std::vector<int> a(n);
    std::for_each(a.begin(), a.end(), [&](int &x) {
        if (argc >= 5) {
            x = rnd.next(0, atoi(argv[4]));
        } else {
            x = rnd.next(0, 998244352);
        }
    });

    println(n, q);
    println(a);

    for (int i = 0; i < q; i++) {
        int l = rnd.next(1, n);
        int r = rnd.next(1, n);

        if (l > r) {
            std::swap(l, r);
        }

        println(l, r);
    }
}