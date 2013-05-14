#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
struct SegmentTree {
private:
        int a[N << 2], s[N << 2];
        int L, R, V, n;

        #define lson l,m,rt<<1
        #define rson m+1,r,rt<<1|1

        void relax(int rt) {
                if(a[rt]) {
                        a[rt<<1] += a[rt];
                        a[rt<<1|1] += a[rt];
                        s[rt<<1] += a[rt];
                        s[rt<<1|1] += a[rt];
                        a[rt] = 0;
                }
        }
        void update(int rt) {
                s[rt] = s[rt<<1] + s[rt<<1|1];
        }
        void init(int l, int r, int rt) {
                s[rt] = a[rt] = 0;
                if(l == r) return;
                int m = (l + r) >> 1;
                init(lson);init(rson);
        }
        void add(int l, int r, int rt) {
                if(L <= l && r <= R) {
                        a[rt] += V;
                        s[rt] += (r-l+1)*V;
                        return;
                }
                relax(rt);
                int m = (l+r)>>1;
                if(L <= m) add(lson);
                if(m <  R) add(rson);
                update(rt);
        }
        int sum(int l, int r, int rt) {
                if(L <= l && r <= R) {
                        return s[rt];
                }
                relax(rt);
                int m = (l+r)>>1;
                return (L<= m?sum(lson):0) + (m<R?sum(rson):0);
        }
public:
        SegmentTree() {}
        SegmentTree(int _n) {
                n = _n;
                init(1, n, 1);
        }
        void Init(int _n) {
                n = _n;
                init(1, n, 1);
        }
        void Add(int l, int r, int v) {
                L = l; R = r; V = v;
                add(1, n, 1);
        }
        int Sum(int l, int r) {
                L = l; R = r;
                return sum(1, n, 1);
        }

        #undef lson
        #undef rson
};

int main () {
        return 0;
}
