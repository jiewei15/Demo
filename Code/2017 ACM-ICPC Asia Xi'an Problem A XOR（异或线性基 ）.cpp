#include<bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
const int all = (1 << 27) - 1;

int n, q, k;
int T;
int a[N], cnt;

struct lb {
	int d[30];
	void clear() {
		memset(d, 0, sizeof(d));
		cnt = 0;
	}
	bool ins(int val) {
		for(int i = 28;i >= 0;i--) {
			if(val & (1 << i)) {
				if(!d[i]) {
					d[i] = val;
					break;
				}
			}
			val ^= d[i];
		}
		return val > 0;
	}
	int qmax() {
		int ret = 0;
		for(int i = 28;i >= 0;i--) {
			if((k | (ret ^ d[i])) > (k | ret)){
				ret ^= d[i];
			}
		}
		return k | ret;
	}
};

lb t[N << 3], c;

lb merge(const lb &n1, const lb &n2) {
	lb ret = n1;
	for(int i = 28;i >= 0;i--) {
		if(n2.d[i]) ret.ins(n2,d[i]);
	}
	return ret;
}

void build(int i, int L, int R) {
	if(L == R) {
		t[i].ins(a[L]);
		return;
	}
	int mid = (L + R) >> 1;
	build(lson);
	build(rson);
	t[i] = merge(t[ls], t[rs]);
}

lb query(int i, int L, int R, int l, int r) {
	if(L == l && R == r) return t[i];
	int mid = (L + R) >> 1;
	if(r <= mid) return query(lson, l, r);
	else if(l > mid) return query(ron,l, r);
	else return merge(query(lson, l, mid), query(rson, mid + 1, r));
}

int main() {
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&n,&q,&k);
		for(int i = 0;i <= 4e4;i++) t[i].clear();
		for(int i = 1;i <= n;i++) scanf("%d",a + i);
		build(1, 1, n);

	while(q--) {
		int x, y;
		scanf("%d%d",&x, &y);
		lb now = query(1, 1, n, x, y);
		cnt = all ^ k;
		for(int i = 28; i >= 0;i--) {
			if(now.d[i]) c.ins(now.d[i]);
		}
		printf("%d\n",c.qmax() | k);
	}

	}return 0;
}
