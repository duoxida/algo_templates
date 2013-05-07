#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

typedef long long LL;
const int N = 40000;
int pri[N], tot = 0;
void mklist() {
        static bool isnp[N];
        for(int i=2;i<N;++i) {
                if(!isnp[i]) {
                        pri[tot ++] = i;
                        for(int j=i+i;j<N;j+=i)
                                isnp[j] = 1;
                }
        }
}

LL pow(LL a, LL b, LL c) {
        LL ans = 1;
        while (b) {
                if(b & 1) ans = ans * a % c;
                a = a * a % c; b >>= 1;
        }
        return ans;
}

int findRoot(int p) {
        int k = p-1;
        for(int i=2;i<p;++i) {
                int flag = 1;
                for(int j=0;(LL)pri[j]*pri[j]<=k;++j) {
                        if( k % pri[j] == 0 && pow(i, k/pri[j], p) == 1 ) {
                                flag = 0;
                                break;
                        }
                }
                if(flag)
                        return i;
        }
}

map<int, int> hash;
int getIndex(int x, int rt, int p) {
        if( x == 1 )
                return 0;
        int m = sqrt(p * 1.0);
        LL t = 1;
        for(int i=0;i<m;++i) {
                if( t == x )
                        return i;
                hash[ t*x%p ] = i;
                t = t * rt % p;
        }
        LL tt = 1;
        for(int i=1;i<=m+1;++i) {
                tt = tt * t % p;
                if( hash.count(tt) )
                        return i*m - hash[tt];
        }
}

LL ex_gcd(LL a, LL b, LL &x, LL &y) {
        if( !b ) {
                x = 1; y = 0;
                return a;
        }
        LL ret = ex_gcd(b, a%b, y, x);
        y -= a/b * x;
        return ret;
}

LL MOD(LL a, LL b) {
        a %= b;
        if(a <= 0) a += b;
        return a;
}

int rt;
vector<LL> ans;
// a * x = c (mod b)
bool solve(LL a, LL b, LL c) {
        LL x, y;
        LL g = ex_gcd(a, b, x, y);
        x = x * c/g;
        x = MOD(x, b/g);
        if(c % g)
                return false;
        for(int i=0;i<g;++i) {
                ans.push_back( pow(rt, x, b+1) );
                x += b/g;
        }
        return true;
}

int main () {
        mklist();
        LL P, K, A;
        cin >> P >> K >> A;
        if(A == 0) {
                cout<<1<<endl<<0<<endl;
                return 0;
        }
        rt = findRoot(P);
        LL c = getIndex(A, rt, P);
        if (!solve(K, P-1, c)) {
                cout << 0 << endl  << endl;
                return 0;
        }
        sort(ans.begin(), ans.end());
        cout<<ans.size()<<endl;
        for(int i=0;i<ans.size();++i) {
                cout<<ans[i];
                if(i != ans.size()-1)
                        cout<<" ";
        }
        cout << endl;
        return 0;
}
