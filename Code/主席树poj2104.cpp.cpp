#include<cstdio>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 1e5 + 5;

int n,m,cnt;
int root[maxn],a[maxn];
int x,y,k;

struct Node {
	int l,r,sum;
}T[maxn * 4];

vector<int> v;

int getid(int x) {
	return lower_bound(v.begin(),v.end(), x) - v.begin() + 1;
}

void update(int l,int r,int &x,int y,int pos) {
	T[++cnt] = T[y], T[cnt].sum++, x = cnt;
	if(l == r) return;
	int mid = (l+r) / 2;
	if(mid >= pos) {
		update(l, mid, T[x].l, T[y].l, pos);
	}
	else {
		update(mid+1, r, T[x].r, T[y].r,pos);
	}
}

int query(int l, int r, int x, int y, int k) {
	if(l == r) return l;
	int mid = (l+r) / 2;
	int sum = T[T[y].l].sum - T[T[x].l].sum;
	if(sum >= k) {
		return query(l, mid, T[x].l, T[y].l, k);
	}
	else {
		return query(mid+1, r, T[x].r, T[y].r, k-sum);
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for(int i = 1;i <= n;i++) {
		update(1, n, root[i], root[i-1], getid(a[i]));
	}
	for(int i = 1;i <= m;i++) {
		scanf("%d%d%d",&x,&y,&k);
		printf("%d\n",v[query(1, n, root[x-1], root[y], k) -1]);
	}
	return 0;
}