#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

LL ext_gcd(LL a, LL b, LL &x, LL &y) {
        if(b == 0) {
                x = 1; y = 0;
                return a;
        }
        int ret = ext_gcd(b, a%b, y, x);
        y -= x*(a / b);
        return ret;
}

int get(int x) {
        if(x < 4)
                return x;
        if(x % 2 == 0)
                return get(x / 2) + 1;
        if(x % 4 == 1)
                return get(x / 2) + 2;
        if(x % 8 == 3)
                return get(x / 4) + 4;
        return get(x+1) + 1;
}

int main () {
        LL a, b, x, y;
        int T;
        for(cin>>T; T--; ) {
                LL a, b, c;
                cin >> c >> b >> a;
                LL d = ext_gcd(a, b, x, y);
                if(c % d) {
                        cout << -1 << endl;
                        continue;
                }
                c /= d; a /= d; b /= d;
                LL xx = x % b; if(xx <= 0) xx += b;
                LL yy = y - (xx-x)/b*a;
                xx = xx * c; yy = -yy * c;
                while(get(xx) > yy) {
                        yy += a; xx += b;
                }
                cout << yy << endl;
        }
        return 0;
}
