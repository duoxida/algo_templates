#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

int ext_gcd(LL a, LL b, int &x, int &y) {
        if(b == 0) {
                x = 1; y = 0;
                return a;
        }
        int ret = ext_gcd(b, a%b, y, x);
        y -= x*(a / b);
        return ret;
}

int main () {
        LL x, y, a, b, p, T;
        for(cin>>T; T--; ) {
                cin >> p >> a >> b;
                int d = ext_gcd(a, b, x, y);
                if(d % p)
                        cout << -1 << endl;
                else {
                        a /= d; b /= d; p /= d;

                }
        }
        return 0;
}
