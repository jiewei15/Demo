#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
typedef long long LL;

const int maxn = 1e5 + 5;

int n, m;
int last[maxn];
int id;
int pos[maxn], mx[maxn], v[maxn];
int bl[maxn], size[maxn], fa[maxn];
ll tag[4*maxn], sum[4*maxn];

vector<int> G[2*maxn];

void dfs(int u) {
	size[u] = 1;
	for(auto& v : G[u]) {
		if(v != fa[u]) {
			fa[v] = u;
			dfs(v);
			size[u] += size[v];
			mx[u] = max(mx[u], mx[v]);
		}
	}
}

void dfs2(int u, int cha) {
	bl[u] = cha, pos[u] = mx[u] = ++id;
	int k = 0;
	for(auto& v : G[u]) {
		if(v != fa[u] && size[v] > size[k]) 
			k = v;
	}
	if(k != 0) dfs2(k, cha), mx[u] = max(mx[u], mx[k]);
	for(autu &v : G[u]) {
		if(v != fa[u] && v != k) 
			dfs2(v, v), mx[u] = max(mx[u], mx[v]);
	}
}

