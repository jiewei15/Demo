#include<iostream>
#include<cstring>
#include<cstring>
using namespace std;

const int N = 100005, inf = 0x3f3f3f3f;

struct splay_tree {

	struct Node {
		int val, Max, add, Size, son[2];
		bool rev;
		void init(int _val) {
			val=Max=_val, Size=1;
			add=rev=son[0]=son[1]=0;
		}
	}T[N];
	
	int fa[N],root;


	void pushUp(int x) {
		T[x].Max=T[x].val,T[x].Size=1;
		if(T[x].son[0]) {
			T[x].Max=max(T[x].Max, T[T[x].son[0]].Max);
			T[x].Size += T[T[x].son[0]].Size;
		}
		if(T[x].son[1]) {
			T[x].Max = max(T[x].Max, T[T[x].son[1]].Max);
			T[x].Size += T[T[x].son[1]].Size;
		} 
	}

	void pushDown(int x) {
		if(x==0) return;
		if(T[x].add) {
			if(T[x].son[0]) {
				T[T[x].son[0]].val += T[x].add;
				T[T[x].son[0]].Max += T[x].add;
				T[T[x].son[0]].add += T[x].add;
			}
			if(T[x].son[1]) {
				T[T[x].son[1]].val += T[x].add;
				T[T[x].son[1]].Max += T[x].add;
				T[T[x].son[1]].add += T[x].add;
			}
			T[x].add = 0;
		}
		if(T[x].rev) {
			if(T[x].son[0]) T[T[x].son[0]].rev ^= 1;
			if(T[x].son[1]) T[T[x].son[1]].rev ^= 1;
			swap(T[x].son[0], T[x].son[1]);
			T[x].rev = 0;
		}
	}

	void Rotate(int x, int kind) {
		int y = fa[x], z = fa[y];
		T[y].son[!kind] = T[x].son[kind], fa[T[x].son[kind]] = y;
		T[x].son[kind] = y, fa[y] = x;
		T[z].son[T[z].son[1] == y] = x, fa[x] = z;
		pushUp(y);
	}

	void Splay(int x,int goal) {
		if(x==goal) return;
		while(fa[x] != goal) {
			int y = fa[x], z = fa[y];
			pushDown(z), pusnDown(y), pushDown(x);
			int rx = T[y].son[0]==x, ry=T[z].son[0]==y;
			if(z == goal) Rotate(x, rx);
			else {
				if(rx==ry) Rotate(y, ry);
				else Rotate(x, rx);
				Rotate(x, ry);
			}
		}
		pushUp(x);
		if(goal == 0) root = x;
	}

	int Select(int pos) {
		int u = root;
		pushDown(u);
		while(T[T[u].son[0]].Size != pos) {
			if(pos < T[T[u].son[0]].Size) u = T[u].son[0];
			else {
				pos -= T[T[u].son[0]].Size + 1;
				u = T[u].son[1];
			}
			pushDown(u);
		}
		return u;
	}

	void update(int L, int R, int val) {
		int u = Select(L-1), v = Select(R+1);
		Splay(u, 0);
		Spaly(v, u);
		T[T[v].son[0]].Max += val;
		T[T[v].son[0]].val += val;
		T[T[v].son[0]].add += val;
	}

	void Reverse(int L, int R) {
		int u = Select(L-1), v = Select(R+1);
		Splay(u, 0);
		Splay(v, u);
		T[T[v].son[0]].rev ^= 1;
	}

	int query(int L, int R) {
		int u = Select(L-1), v = Select(R+1);
		Splay(u, 0);
		Splay(v, u);
		return T[T[v].son[0]].Max; 
	}

	int build(int L, int R) {
		if(L>R) return 0;
		if(L==R) return L;
		int mid = (L+R)>>1, sL, sR;
		T[mid].son[0] = sL = build(L, mid-1);
		T[mid].son[1] = sR = build(mid+1, R);
		fa[sL] = fa[sR] = mid;
		pushUp(mid);
		return mid;
	}

	void init(int n) {
		T[0].init(-inf), T[1].init(-inf), T[n+2].init(-inf);
		for(int i = 2; i <= n+1; i++) T[i].init(0);
			root = build(1, n+2), fa[root] = 0;
		fa[0] = 0, T[0].son[1] = root, T[0].Size = 0;
	}

};

splay_tree hehe;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	hehe.init(n);
	for(int i = 0, a, b, c, d; i<m; i++) {
		scanf("%d", &a);
		if(a==1) {
			scanf("%d%d%d", &b,&c,&d);
			hehe.updata(b,c,d);
		}
		else if(a==2) {
			scanf("%d%d",&b,&c);
			hehe.Reverse(b,c);
		}
		else {
			scanf("%d%d",&b,&c);
			printf("%d\n",hehe.query(b,c));
		}
	}
	return 0;
}