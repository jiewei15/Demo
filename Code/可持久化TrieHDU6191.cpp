#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 140000;
int L[maxn + 50], R[maxn + 50];
int TOT = 0;
int root[maxn + 50];
struct Trie {
	int next[2];
	int sum;
	Init () {
		memset(next,-1,sizeof(next));
		sum = 0;
	}
}trie[(maxn << 6) + (maxn << 5)];

struct Edge {
	int next, to;
}edge[200100];

int head[maxn];
int tot = 0;
int cnt = 0;
int v[maxn];
int rank[maxn];

void init() {
	tot = 0;
	memset(head,-1,sizeof(head));
	cnt = 0;
	TOT = 0;
}

void add(int u, int v) {
	edge[++tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}

void dfs(int pre, int u) {
	L[u] = ++cnt;
	rand[cnt] = u;
	for(int i = head[u]; ~i;i = edge[i].next) {
		int v = edge[i].to;
		if(v == pre) continue;
		dfs(u, v);
	}
	R[u] = cnt;
}

void build(int x) {
	int now = 0;
	for(int i = 31;i >= 0;i--) {
		int p = (x >>i ) & 1;
		if(trie[now].next[p] == -1) {
			trie[now].next[p] = ++TOT;
			trie[TOT].Init();
		}
		now = trie[now].next[p];
		trie[now].sum;
	}
}

int Insert(int x, int rt, int d) {
	TOT++;
	int now = TOT;
	trie[now] = trie[rt];
	if(d == -1) return now;
	int p = (x >> d) &1;
	trie[now].next[p] = inset(x, trie[now].next[p], d-1);
	trie[trie[now].next[p]].sum++;
	return now;
}

int Que(int x,int L_rt,int R_rt) {
	int res = 0;
	for(int i = 31; i>= 0;i--) {
		int p = (x >> i) &1;
		if(trie[R_rt].next[p ^ 1] == -1) {
			R_rt = trie[R_rt].next[p];
			L_rt = trie[L_rt].next[p];
		}
		else {
			int tmp1 = trie[R_rt].next[p ^ 1];
			int tmp2 = trie[L_rt].next[p ^ 1];
			if(trie[tmp1].sum - trie[tmp2].sum > 0) {
				res += (1 << i);
				R_rt = tmp1;
				L_rt = tmp2;
			}
			else {
				R_rt = trie[R_rt].next[p];
				L_rt = trie[L_rt].next[p];
			}
		}
	}
	return res;
}

int main() {
	int n, q;
	while(~scanf("%d%d",&n,&q)) {
		init();
		for(int i = 1;i <= n;i++) {
			scanf("%d",&v[i]);
		}
		int tmp;
		for(int i = 1;i < n;i++ ) {
			scanf("%d",&tmp);
			add(i + 1,tmp);
			add(tmp , i+ 1);
		}
		dfs(-1, 1);
		for(int i = 1;i <= n;i++) {
			trie[0].Init();
		}
		for(int i = 1;i <= n;i++) {
			build(v[rank[i]]);
		}
		root[0]= 0;
		for(int i =1;i <=n;i++) {
			root[i] = Insert(v[rank[i]], root[i - 1], 31);
		}
		int u, x;
		int l, r;
		int ans = 0;
		while(q--) {
			scanf("%d%d",&u, &x);
			l = L[u] - 1;
			r = R[u] ;
			ans = Que(x, root[l], root[r]);
			printf("%d\n",ans);
		}
		for(int i = 0;i <= TOT;i++) {
			memset(trie[i].next,-1, sizeof(trie[i].next));
			trie[i].sum = 0;
		}
	}
	return 0;
}