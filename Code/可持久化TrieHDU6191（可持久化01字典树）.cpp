/**
跑完dfs序后，按dfs序建可持久化字典树，维护dfs序前 个中每个数的出现次数，这样每次版本更新的时候只会更新（新增）个结点，其他结点都可以继承上一个版本的信息。
然后查询的时候只要sz[out[u]]-sz[in[u]-1]>0就说明可以走这个点，贪心即可。
*/
/**
用dfs序直接把子树转化为区间上的问题，然后用可持续化trie树去做。 
可持续化trie树本质其实和主席树的建树方式差不多，动态建树且每一次新增一条链。然后当询问某一个子树的时候，
通过dfs序把它变成一个区间，然后就是01字典树上面走走。从高到底看看这一位有没有与x相反的bit位，
如果有还要判断是否在L到R的区间上。
*/
#include<bits/stdc++.h>
using namespace std;

const int N = 1 << 17;

struct Trie {
	int sz[N << 5], ch[N << 5][2], tot;
	int rt[N];
	void init() {
		tot = 0;
		memset(rt, 0, sizeof(rt));
		rt[0] = newNode();
	}
	int newNode() {
		memset(ch[tot],0,sizeof(ch[tot]));
		sz[tot] = 0;
		return tot++;
	}
	void insert(int val, int x, int y) {
		rt[x] = newNode();
		int u = rt[x], v = rt[y];
		for(int i = 30; ~i; i--) {
			int d= val >> i & 1;
			sz[u] = sz[v] + 1;
			ch[u][d] = newNode();
			ch[u][d ^ 1] = ch[v][d ^ 1];
			u = ch[u][d], v = ch[v][d];
		}
		sz[u] = sz[v] + 1;
	}
	int query(int val, int x, int y) {
		int u = rt[x], v = rt[y];
		int ans = 0;
		for(int i = 30; ~i; i--) {
			int d = val >> i & 1;
			int t = sz[ch[v][d ^ 1]] - sz[ch[u][d ^ 1]];
			if(t > 0) d ^= 1;
			ans |= d << i;
			u = ch[u][d], v = ch[v][d];
		}
		return ans;
	}
}trie;

int val[N];
vector<int> G[N];
int in[N], out[N], dfn;

void dfs(int u) {
	trie.insert(val[u], dfn + 1, dfn);
	in[u] = ++ dfn;
	for(auto& v : G[u]) {
		dfs(v);
	}
	out[u] = dfn;
}

int main() {
	int n, q;
	while(~scanf("%d%d",&n, &q)) {
		trie.init(), dfn = 0;
		for(int i = 1;i <= n;i++) {
			G[i].clear();
			scanf("%d",val + i);
		}
		for(int i = 2, v;i <= n;i++) {
			scanf("%d",&v);
			G[v].push_back(i);
		}
		dfs(1);
		while(q--) {
			static int u, x;
			scanf("%d%d",&u, &x);
			printf("%d\n",x ^ trie.query(x, in[u] - 1, out[u]));
		}
	}
	return 0;
}