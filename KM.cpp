#include <algorithm>
#include <iostream>

using namespace std;

const int M = 111;
const int INF = 1<<30;

int w[M][M], n;
int match[M];
struct KM {
        int lx[M], ly[M], slack[M];
        bool sx[M], sy[M];
        void init() {
                for(int i=0;i<n;++i)
                        for(int j=0;j<n;++j)
                                w[i][j] = -INF;
        }
        bool dfs(int u) {
                sx[u] = 1;
                for(int v=0;v<n;++v) {
                        if(sy[v])
                                continue;
                        int t = lx[u] + ly[v] - w[u][v];
                        if( !t ) {
                                sy[v] = 1;
                                if(match[v] == -1 || dfs(match[v])) {
                                        match[v] = u;
                                        return true;
                                }
                        }
                        else
                                slack[v] = min(slack[v], t);
                }
                return false;
        }
        int work() {
                fill(match, match+n, -1);
                for(int i=0;i<n;++i) {
                        lx[i] = ly[i] = -INF;
                        for(int j=0;j<n;++j)
                                lx[i] = max(lx[i], w[i][j]);
                }
                for(int i=0;i<n;++i) {
                        fill(slack, slack+n, INF);
                        while(true) {
                                fill(sx, sx+n, 0);
                                fill(sy, sy+n, 0);
                                if(dfs(i))
                                        break;
                                int d = INF;
                                for(int j=0;j<n;++j)
                                        if(!sy[j])
                                                d = min(d, slack[j]);
                                for(int j=0;j<n;++j) {
                                        if(sx[j])
                                                lx[j] -= d;
                                        if(sy[j])
                                                lx[j] += d;
                                        else
                                                slack[j] -= d;
                                }
                        }
                }
                int sum = 0;
                for(int i=0;i<n;++i)
                        sum += w[ match[i] ][i];
                return sum;
        }
}km;

int main () {
        n = 5; km.init();
        for(int i=0;i<5;++i) w[i][i] = 1;
        w[0][1] = 100;
        cout << km.work() << endl;
        return 0;
}
