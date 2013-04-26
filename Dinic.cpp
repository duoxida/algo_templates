#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int N = 55;
const int NN = 2555;
const int M = 2555<<3;
const int INF = 1<<30;

struct Edge {
        int u, v, f, next;
        void set(int _u, int _v, int _f, int _next) {
                u = _u; v = _v; f = _f; next = _next;
        }
}E[M];

int H[NN], tot;

void init() {
        memset(H, -1, sizeof(H));
        tot = 0;
}

void addEdge(int u, int v, int f) {
        E[tot].set(u, v, f, H[u]);
        H[u] = tot++;
        E[tot].set(v, u, 0, H[v]);
        H[v] = tot++;
}

struct Dinic {
        int d[NN], W[NN], begin, end;
        bool bfs() {
                memset(d, -1, sizeof(d));
                d[begin] = 0;
                queue<int> q; q.push(begin);
                while(!q.empty()) {
                        int x = q.front(); q.pop();
                        for(int e=H[x];~e;e=E[e].next) {
                                int y = E[e].v;
                                if(E[e].f && d[y] < 0) {
                                        d[y] = d[x] + 1;
                                        q.push(y);
                                        if(y == end)
                                                return true;
                                }
                        }
                }
                return false;
        }
        int dfs(int x, int low) {
                if(x == end)
                        return low;
                for(int &e=W[x];~e;e=E[e].next) {
                        int y = E[e].v, t;
                        if(E[e].f && d[y] == d[x]+1 && (t=dfs(y,min(low,E[e].f)))) {
                                E[e].f -= t;
                                E[e^1].f += t;
                                return t;
                        }
                }
                return 0;
        }
        int work(int S, int T) {
                begin = S, end = T;
                int ans = 0;
                while(bfs()) {
                        int t;
                        for(int i=0;i<=end;++i)
                                W[i] = H[i];
                        while(t = dfs(begin, INF))
                                ans += t;
                }
                return ans;
        }
}dinic;

int a[N][N];

int main () {
        int n, m;
        while(scanf("%d%d",&n,&m)!=EOF) {
                init();
                int ans = 0;
                for(int i=0;i<n;++i) for(int j=0;j<m;++j) {
                        scanf("%d",&a[i][j]);
                        ans += a[i][j];
                }
                int begin = n*m, end = begin+1;
                for(int i=0;i<n;++i) for(int j=0;j<m;++j) {
                        int s = i*m + j, t;
                        if(j != m-1) {
                                t = s + 1;
                                if( (i+j)&1 )
                                        addEdge(t, s, INF);
                                else
                                        addEdge(s, t, INF);
                        }
                        if(i != n-1) {
                                t = s + m;
                                if( (i+j)&1 )
                                        addEdge(t, s, INF);
                                else
                                        addEdge(s, t, INF);
                        }
                        if( (i+j)&1 )
                                addEdge(s, end, a[i][j]);
                        else
                                addEdge(begin, s, a[i][j]);
                }
                printf("%d\n", ans - dinic.work(begin, end));
        }
        return 0;
}
