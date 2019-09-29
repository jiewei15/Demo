#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#define maxn 10010
using namespace std;

typedef pair<long long,long long> P;

inline long long read(){
    long long x=0,t=1,c;
    while(!isdigit(c=getchar())) if(c=='-') t=-1;
    while(isdigit(c)) x=x*10+c-'0',c=getchar();
    return x*t;
}

long long n, m, s, tot;

long long head[maxn];
struct Edge {
	int to, next, val;
}edge[maxn << 10];

long long dis[maxn], vis[maxn];

priority_queue<P, vector<P>, greater<P> > q;///优先队列优化

inline void add(long long u, long long v,long long w) {
	tot++;
	edge[tot].to = v;
	edge[tot].val = w;
	edge[tot].next = head[u];
	head[u] = tot;
}

inline void init() {
	tot = 0;
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
}

void Dijkstra() {
	for(int i = 1;i <= n;i++) {
		dis[i] = 0x3f3f3f3f;
	}
	dis[s] = 0;
	q.push(P(0, s));
	while(!q.empty()) {
		long long u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(long long i = head[u]; ~i;i = edge[i].next) {
			int v = edge[i].to, w = edge[i].val;
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push(P(dis[v], v));
			}
		}
	}
}

int main() {
	init();
	scanf("%d%d%d",&n,&m,&s);
	long long u, v, w;
	for(int i = 1;i <= m;i++) {
		scanf("%d%d%d",&u,&v,&w);
		add(u, v, w);
	}
	Dijkstra();
	for(int i = 1;i <= n;i++) {
		printf("%lld ",dis[i]);
	}
}
