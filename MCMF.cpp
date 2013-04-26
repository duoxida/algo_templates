#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 220;
const int M = 30010;
/// for MCMF
const int NN = 440;
const int INF = 1<<30;

struct Edge {
        int u, v, c, f, next;
        void set(int _u, int _v, int _c, int _f, int _next) {
                u = _u; v = _v; c = _c; f = _f;next = _next;
        }
}E[M+M];
int tot, H[NN];
void G_init() {
        memset(H, -1, sizeof(H));
        tot = 0;
}
void addEdge(int u, int v, int c, int f) {
        E[tot].set(u, v, c, f, H[u]);
        H[u] = tot++;
        E[tot].set(v, u, -c, 0, H[v]);
        H[v] = tot++;
}
struct MCMF {
        bool inq[NN];
        /// pre存的是边
        int dis[NN], pre[NN];
        bool spfa(int begin, int end) {
                queue<int> q;
                for(int i=0;i<=end;++i) {
                        pre[i] = -1;
                        inq[i] = 0;
                        dis[i] = INF;
                }
                inq[begin] = 1; dis[begin] = 0;
                q.push(begin);
                while(!q.empty()) {
                        int u = q.front(); q.pop();
                        inq[u] = false;
                        for(int e=H[u];~e;e=E[e].next) if(E[e].f){
                                int v = E[e].v;
                                if(dis[v] > dis[u] + E[e].c) {
                                        dis[v] = dis[u] + E[e].c;
                                        pre[v] = e;
                                        if(! inq[v]) {
                                                inq[v] = 1;
                                                q.push(v);
                                        }
                                }
                        }
                }
                return dis[end] != INF;
        }
        int work(int begin, int end) {
                /// ans 为最小费用流， flow_sum为最大流
                int ans = 0, flow_sum = 0;
                while(spfa(begin, end)) {
                        int flow = INF;
                        for(int e=pre[end];~e;e=pre[ E[e].u ])
                                flow = min(flow, E[e].f);
                        for(int e=pre[end];~e;e=pre[ E[e].u ]) {
                                E[e].f -= flow;
                                E[e^1].f += flow;
                        }
                        flow_sum += flow;
                        ans += dis[end]*flow;
                }
                return ans;
        }
}mcmf;

int tmp[N][N];
int main () {
        int T;
        scanf("%d", &T);
        while(T --) {
                int n, m;
                scanf("%d%d",&n,&m);
                for(int i=0;i<n;++i) for(int j=0;j<n;++j)
                        tmp[i][j] = INF;
                while(m --) {
                        int u, v, w;
                        scanf("%d%d%d",&u,&v,&w);
                        u--; v--;
                        if(u != v)
                                tmp[u][v] = min(tmp[u][v], w);
                }
                G_init();
                for(int i=0;i<n;++i) for(int j=0;j<n;++j) if(tmp[i][j] != INF)
                        addEdge(i, j+n, tmp[i][j], 1);
                int begin = n+n, end = n+n+1;
                for(int i=0;i<n;++i) {
                        addEdge(begin, i, 0, 1);
                        addEdge(i+n, end, 0, 1);
                }
                printf("%d\n", mcmf.work(begin, end));
        }
        return 0;
}
