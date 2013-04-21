#include <iostream>
#include <algorithm>

using namespace std;

const int M = 111;

int w[M][M], n;
int match[M];
bool s[M];
bool dfs(int u) {
        for(int v=0;v<n;++v) {
                if(s[v] || !w[u][v])
                        continue;
                s[v] = 1;
                if(match[v]==-1 || dfs(match[v])) {
                        match[v] = u;
                        return true;
                }
        }
        return false;
}
int XYL() {
        int ans = 0;
        fill(match, match+n, -1);
        fill(s, s+n, 0);
        for(int i=0;i<n;++i) if(dfs(i))
                ans ++;
        return ans;
}

int main () {
        return 0;
}
