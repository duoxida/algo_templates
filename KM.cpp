#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef long long LL;

const int N = 220;
const int M = 30010;
const int INF = 1<<30;

struct Edge {
        int u, v, w, next;
        void set(int _u, int _v, int _w, int _next) {
                u = _u; v = _v; w = _w; next = _next;
        }
}E[M];
int H[N], tot, n;

void init() {
        fill(H, H+n, -1);
        tot = 0;
}
void addEdge(int u, int v, int w) {
        E[tot].set(u, v, w, H[u]);
        H[u] = tot ++;
}

/**
* KM算法，是通过保持任意边两端顶标和大于等于边
* 并通过选取满足满足 边等于两端之和的边
* 最大权匹配。并不是指所有匹配中权和最大，而是所有完美匹配中权和最大
* 只有顶标和等于边值才可以进入dfs寻增广路
* slack数组保证每次只加入最少量的边，保证算法正确性。
*/
struct KM {
        bool sx[N], sy[N];
        int lx[N], ly[N];
        /// slack代表y减去的最小值使得能dfs到更多的路
        int match[N], slack[N];

        bool dfs(int x) {
                sx[x] = 1;
                for(int e=H[x];e!=-1;e=E[e].next) {
                        int y = E[e].v, w = E[e].w;

                        if(sy[y])
                                continue;
                        int t = lx[x] + ly[y] - w;
                        if(t == 0) {
                                sy[y] = 1;
                                if(match[y]==-1 || dfs( match[y] )) {
                                        match[y] = x;
                                        return true;
                                }
                        }
                        else
                                slack[y] = min(slack[y], t);
                }
                return false;
        }
        int work() {
                fill(match, match+n, -1);

                ///将所有顶标更新为所有边的最大值以保证lx[x]+ly[y]>=w[x,y]
                int d = -INF;
                for(int i=0;i<tot;++i)
                        d = max(d, E[i].w);
                for(int i=0;i<n;++i)
                        lx[i] = ly[i] = d;

                for(int x=0;x<n;++x) {
                        /**
                        *  每新加一条边要把slack重新赋值
                        *  因为起点不同经过的路线也不同
                        */
                        fill(slack, slack+n, INF);
                        while(1) {
                                fill(sx, sx+n, 0);
                                fill(sy, sy+n, 0);
                                if(dfs(x))
                                        break;
                                int d = INF;
                                for(int y=0;y<n;++y) {
                                        if(!sy[y])
                                                d = min(d, slack[y]);
                                }
                                /// 不存在完美匹配
                                if(d == INF) return -1;
                                for(int i=0;i<n;++i) {
                                        if(sx[i])
                                                lx[i] -= d;
                                        if(sy[i])
                                                ly[i] += d;
                                        else
                                                slack[i] -= d;
                                }
                        }
                }
                int sum = 0;
                for(int i=0;i<n;++i)
                        sum += lx[i] + ly[i];
                return sum;
        }
}km;

int tmp[N][N];

int main () {
        int T;
        scanf("%d",&T);
        while(T --) {
                int m;
                scanf("%d%d",&n,&m);
                init();
                for(int i=0;i<n;++i) for(int j=0;j<n;++j)
                        tmp[i][j] = -INF;

                while(m --) {
                        int u, v, t;
                        scanf("%d%d%d",&u,&v,&t);
                        u--, v--;
                        if(u == v)
                                continue;
                        tmp[u][v] = max(tmp[u][v], -t);
                }
                for(int i=0;i<n;++i) for(int j=0;j<n;++j)
                        if(tmp[i][j] != -INF)
                                addEdge(i, j, tmp[i][j]);

                printf("%d\n", -km.work());
        }
        return 0;
}
