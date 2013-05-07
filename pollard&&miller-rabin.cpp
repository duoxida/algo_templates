//poj 2429
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

LL mul_mod(LL a, LL n, LL m) {
        LL ans = 0; a = a % m;
        while(n) {
                if(n & 1) {
                        ans = (ans + a) % m;
                }
                a = (a + a) % m; n >>= 1;
        }
        return ans;
}

LL pow_mod(LL a, LL n, LL m) {
        LL ans = 1; a = a % m;
        while(n) {
                if(n & 1) {
                        ans = mul_mod(ans, a, m);
                }
                a = mul_mod(a, a, m);
                n >>= 1;
        }
        return ans;
}

LL gcd(LL a, LL b) {
        return b==0?a:gcd(b, a%b);
}

bool witness(LL a, LL n) {
        LL t = n-1;
        while(t % 2 == 0)
                t >>= 1;
        LL x, y;
        x = y = pow_mod(a, t, n);
        while(t<n) {
                x = mul_mod(x, x, n);
                if(x==1&&y!=1&&y!=n-1)
                        return 1;
                y = x;
                t <<= 1;
        }
        return x!=1;
}

bool miller_rabin(LL n, int s=10) {
        if(n == 2 || n == 3 || n == 5)
                return 1;
        if(n % 2 == 0 || n % 3 ==0 || n % 5 == 0)
                return 0;
        while(s--) {
                LL a = rand()%(n-1)+1;
                if(witness(a, n))
                        return 0;
        }
        return 1;
}

LL pollard_rho(LL n, LL c) {
        LL x, y;
        LL i=1, k=2;
        x = rand()%n; y = x;
        while(1) {
                i++;
                x = (mul_mod(x, x, n)+c)%n;
                LL d = gcd(y-x, n);
                if(d < 0) d = -d;
                if(d!=1 && d!=n)
                        return d;
                if(x == y)
                        return n;
                if(i == k) {
                        y = x;
                        k += k;
                }
        }
}

LL fac[1111]; int tot=0;
void findfac(LL n) {
        if(miller_rabin(n)) {
                fac[tot++] = n;
                return ;
        }
        LL p = n;
        if(n % 2 == 0 )
                p = 2;
        else if(n % 3 == 0) p = 3;
        else if(n % 5 == 0) p = 5;
        else
        while(p >= n)
                p = pollard_rho(p, rand()%(n-1)+1);
        findfac(p); findfac(n / p);
}

LL s[1111], sc;
pair<LL, LL> ans;
void dfs(LL d, LL now) {
        if(d > sc) {
                LL q = ans.first * ans.second / now;
                if(q + now < ans.first + ans.second) {
                        ans = make_pair(now, q);
                }
                return;
        }
        dfs(d+1, now * s[d]); dfs(d+1, now);
}

int main () {
        LL a, b;
        while(scanf("%I64d%I64d",&a,&b)!=EOF) {
                tot = 0;
                LL n = b/a, last = -1;
                if(n!=1)
                        findfac(n);
                sc = -1;
                sort(fac, fac+tot);
                for(int i=0;i<tot;++i) {
                        if(fac[i] != last)
                                last = s[++sc] = fac[i];
                        else
                                s[sc] *= last;
                }
                ans = make_pair(1, n);
                dfs(0, 1);
                if(ans.first > ans.second)
                        swap(ans.first, ans.second);
                printf("%I64d %I64d\n", ans.first*a, ans.second*a);
        }
        return 0;
}
