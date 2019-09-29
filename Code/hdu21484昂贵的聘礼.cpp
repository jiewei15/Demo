#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
#define maxn 109
#define inf 0x3f3f3f3f
using namespace std;

int n, m, tot;

struct Edge {
	int to, w, next;
}edge[maxn];

int w[maxn], r[maxn];

void add(int u, int v, int val) {
	tot++;
	edge[tot].to = v;
	edge[tot].next = head[u];
	edge[tot].w = val;
}

int dis[maxn], vis[maxn];

void dijkstra(int st) {
	for(int i = 1;i <= n;i++) {
		dis[i] = inf;
	}
	dis[st] = 0;
	vis[st] = 1;
	while(1) {
		int minv, u = -1;
		for(int i = 1;i <= n;i++) {
			if(!vis[i] && dis[i] <= minv) minv = dis[u = i];
		}
		if(u == -1) break;
		vis[u] = 1;
		for(int i = head[u]; ~i;i = edge[i].next) {
			int w = edge[i].w;
			int v = edge[i].to;
			if(dis[u] + w < dis[v] && !vis[v])
				dis[i] = dis[u] + w;
		}
	}
}

int main() {
	scanf("%d%d",&m,&n);
	tot = 0;
	for(int i = 1, x;i <= n;i++) {
		scanf("%d%d%d",&w[i],&r[i],&x);
		while(x--) {
			scanf("%d%d",&u,&val);
			add(u, i, val);
		}
	}
	for(int i = 1;i <= n;i++) {
		if(r[1] - r[i] <= m) {
			ans = min(ans, dijkstra(i));
		}
	}
}