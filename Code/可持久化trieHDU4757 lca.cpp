#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6 + 10;
const int LOGN = 20;
int n, m;
int a[MAXN];
vector<int> G[MAXN];
int dep[MAXN];
int p[MAXN][LOGN];
void init() {
    for(int i = 1; i < LOGN; i++) {
        for(int j = 1; j <= n; j++) {
            p[j][i] = p[p[j][i - 1]][i - 1];
        }
    }
}
int lca(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 0; i < LOGN; i++) {
        if((dep[v] - dep[u]) >> i & 1) {
            v = p[v][i];
        }
    }
    if(v == u) return u;
    for(int i = LOGN - 1; i >= 0; i--) {
        if(p[u][i] != p[v][i]) {
            u = p[u][i];
            v = p[v][i];
        }
    }
    return p[u][0];
}
int sz[MAXN];
int nxt[MAXN][2], root[MAXN], L;
int newnode() {
    nxt[L][0] = nxt[L][1] = 0;
    return L++;
}
void insert(int u, int fa, int x) {
    int now1 = root[u], now2 = root[fa];
    for(int i = 18; i >= 0; i--) {
        int d = (x >> i) & 1;
        nxt[now1][d] = newnode();
        nxt[now1][!d] = nxt[now2][!d];
        now1 = nxt[now1][d]; now2 = nxt[now2][d];
        sz[now1] = sz[now2] + 1;
    }
}
int query(int u, int v, int x) {
    int k = lca(u, v);
    int res = 0;
    int now1 = root[u], now2 = root[v], now3 = root[k];
    for(int i = 18; i >= 0; i--) {
        int d = (x >> i) & 1;
        if(sz[nxt[now1][!d]] + sz[nxt[now2][!d]] - 2 * sz[nxt[now3][!d]] > 0) {
            res += (1 << i);
            d = !d;
        }
        now1 = nxt[now1][d];
        now2 = nxt[now2][d];
        now3 = nxt[now3][d];
    }
    return max(res, x ^ a[k]);
}
void dfs(int fa, int u) {
    root[u] = newnode();
    insert(u, fa, a[u]);
    p[u][0] = fa;
    dep[u] = dep[fa] + 1;
    for(int i = 0; i < (int)G[u].size(); i++) {
        int v = G[u][i];
        if(v != fa) {
            dfs(u, v);
        }
    }
}
int main() {
    while(~scanf("%d%d", &n, &m)) {
        L = 1;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            G[i].clear();
        }
        for(int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(0, 1);
        init();
        while(m--) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            printf("%d\n", query(x, y, z));
        }
    }
    return 0;
}