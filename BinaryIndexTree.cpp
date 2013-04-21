#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
class BinaryIndexTree {
private:
        int n, C[N];
        int lowbit(int x) {
                return x & (-x);
        }
public:
        BinaryIndexTree() {}
        BinaryIndexTree(int _n) {
                n = _n;
                fill(C+1, C+1+n, 0);
        }
        void init(int _n) {
                n = _n;
                fill(C+1, C+1+n, 0);
        }
        void add(int i, int v) {
                for(;i<=n;i+=lowbit(i))
                        C[i] += v;
        }
        int sum(int i) {
                int ret = 0;
                for(;i;i-=lowbit(i))
                        ret += C[i];
                return ret;
        }
}test(8);

int main () {
        test.add(2,1), test.add(3, 1);
        cout << test.sum(2) << " " << test.sum(3) << endl;
        return 0;
}
