#include<queue>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll long long
#define inf 1000000009
#define maxn 200005
#define maxm 10000007
using namespace std;

int T,n,m,ans;
int cnt,a[maxn],nxt[maxn],last[maxn];
int rt[maxn],ls[maxm],rs[maxm],v[maxm];

int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar(); }
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar(); }
	return x*f;
}

void insert(int x,int &y,int l,int r,int val) {
	int mid = (l + r) >>1;
	y = ++cnt; v[y] = v[x] + 1;
	if(l == r) return ;
	ls[y] = ls[x];
	rs[y] = rs[x];
	if(val <= mid) {
		insert(ls[x], ls[y], l, mid, val);
	}
	else {
		insert(rs[x], rs[y], mid+1, r, val);
	}
}

int query(int x,int y,int l,int r,int K) {
	if(l==r) return 0;
	int mid = (l+r) >>1;
	if(K <= mid) {
		return v[rs[y]] - v[rs[x]] + query(ls[x], ls[y], l, mid, K);
	}
	else {
		return query(rs[x], rs[y], mid+1, r, K);
	}
}

int solve(int l,int r) {
	int ans = query(rt[l-1], rt[r], 1, n+1, r);
	return ans;
}

int main() {
	T = read();
	for(int test = 1;test <= T;test++) {
		n = read();
		m = read();
		cnt = ans = 0;
		for(int i = 1;i <= n;i++) {
			a[i] = read();
		}
		for(int i = 0;i <= 200000;i++) {
			last[i] = n+1;
		}
		for(int i = n;i >= 1;i--) {
			nxt[i] = last[a[i]];
			last[a[i]] = i;
		}
		for(int i = 1;i <= n;i++) {
			insert(rt[i-1], rt[i], 1, n+1, nxt[i]);
		}
		cout<<"Case #"<<text<<":";
		for(int i = 1;i <= m;i++) {
			int l = read(), r = read();
			l = (l+ans) % n+1, r = (r+ans) % n+1;
			if(l>r) swap(l,r);
			int t = solve(l,r);
			t = (t+1)/2;
			int L = l, R = r;
			while(L <= R) {
				int mid = (L+R) >> 1;
				if(solve(l,mid) >= t) ans = mid, R = mid - 1;
				else L = mid+1;
			}
			cout<<' '<<ans;
		}
		cout<<endl;
	}
	return 0;
}