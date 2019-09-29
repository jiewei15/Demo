#include<bits/stdc++.h>
using namespace std;
const int maxn = 100005;
int n,q;
int cnt,tot;
int rank[maxn];///结点在数组内的位置
int L[maxn];///dfs进入时间戳
int R[maxn];///dfs退出时间戳
int v[maxn];///顶点权值
int T[maxn];///n颗字典树的根结点

struct Node {
	int sum;
	int l, r;
	Node() {
		sum = 0;
		l = 0;
		r = 0;
	}
}Tree[maxn << 6];

int head[maxn];
int ee = 0;

struct Edge {
	int v;
	int last;///next
}edge[maxn];

void add(int u, int v) {
	edge[ee].v = v;
	edge[ee].last = head[u];
	head[u] = ee++;
}

void dfs(int u) {
	L[u] = ++cnt;
	for(int i = head[u]; ~i; i = edge[i].last) {
		int v = edge[i].v;
		dfs(v);
	}
	R[u] = cnt;
}

void insert(int root, int x, int value) {
	int p = root;
	for(int i = 30;i >= 0;i--) {
		int num = (x>>i) & 1;
		if(num == 0) {
			if(Tree[p].l == 0) {
				Tree[p].l = tot++;
				p = Tree[p].l;
				Tree[p].sum +=value;
			}
			else {
				p = Tree[p].l;
				Tree[p].sum += value;
			}
		}
		else {
			if(Tree[p].r == 0) {
				Tree[p].r = tot++;
				p = Tree[p].r;
				Tree[p].sum += value;
			}
			else {
				p = Tree[p].r;
				Tree[p].sum += value;
			}
		}
	}
}

int update(int pa, int x) {
	int now = tot++;
	int p = now;
	for(int i = 30;i >= 0;i--) {
		int num = (x>>i) & 1;
		if(num == 0) {
			Tree[p].r = Tree[pa].r;
			Tree[p].l = tot++;
			p = Tree[p].l;
			pa = Tree[pa].l;
			Tree[p].sum = Tree[pa].sum + 1;
		}
		else {
			Tree[p].l = Tree[pa].l;
			Tree[p].r = tot++;
			p = Tree[p].r;
			pa = Tree[pa].r;
			Tree[p].sum = Tree[pa].sum + 1;
		}
	}
	return now;
}

int query(int p1, int p2, int x) {
	int d;
	int ans = 0;
	for(int i = 30;i >= 0;i--) {
		int num = (x>>i) & 1;
		if(num == 0) {
			if(Tree[p2].r == 0) {
				p2 = Tree[p2].l;
				p1 = Tree[p1].l;
				continue;
			}
			d = Tree[Tree[p2].r].sum - Tree[Tree[p1].r].sum;
			if(d > 0) {
				ans += (1<<i);
				p1 = Tree[p1].r;
				p2 = Tree[p2].r;
			}
			else {
				p1 = Tree[p1].l;
				p2 = Tree[p2].l;
			}
		}
		else {
			if(Tree[p2].l == 0) {
				p2 = Tree[p2].r;
				p1 = Tree[p1].r;
				continue;
			}
			d = Tree[Tree[p2].l].sum - Tree[Tree[p1].l].sum;
			if(d > 0) {
				ans += (1<<i);
				p1 = Tree[p1].l;
				p2 = Tree[p2].l;
			}
			else {
				p1 = Tree[p1].r;
				p2 = Tree[p2].r;
			}
		}
	}
	return ans;
}

void init() {
	cnt = 0;
	tot = 0;
	dfs(1);
	for(int i = 1;i <= n;i++) {
		rank[L[i]] = v[i];
	}
}

int main() {
	while(~scanf("%d%d",&n,&q)) {
		for(int i = 0; i < (maxn << 6) -1;i++) {
			Tree[i].l = 0;
			Tree[i].r = 0;
			Tree[i].sum = 0;
		}
		for(int i = 1;i <= n;i++) {
			scanf("%d",&v[i]);
		}
		int f;
		ee = 0;
		memset(head, -1, sizeof(head));
		for(int i = 1;i < n;i++) {
			scanf("%d",&f);
			add(f, i+1);
		}
		init();
		T[0] = ++tot;
		for(int i = 1;i <= n;i++) {
			insert(T[0], rank[i], 1);
		}
		for(int i = 1;i <= n;i++) {
			insert(T[0], rank[i], -1);
		}
		for(int i = 1;i <= n;i++) {
			T[i] = update(T[i - 1], rank[i]);
		}
		int uu,xx;
		for(int i = 1;i <= q;i++) {
			scanf("%d%d",&uu,&xx);
			printf("%d\n",query(T[L[uu] - 1], T[R[uu]], xx));
		}
	}
	return 0;
}