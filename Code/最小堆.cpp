#include<bits/stdc++.h>
using namespace std;
int main() {

	int n;
	for(int i = 1;i <= n;i++) {
		scanf("%d",&a[i]);
		for(int k = i;k > 1 && a[k] < a[k/2];k /= 2) {
			swap(a[k],a[k/2]);
		}
	}
}


// #include<bits/stdc++.h>
// #define inc(i,a,b) for(int i = a;i <= b;i++)
// #define dec(i,a,b) for(int i = a;i >= b;i--)
// #define p_b(x) push_back(x)
// using namespace std;
// const int maxn = 33;
// vector<int> in,pre,post;
// int rch[maxn<<2],lch[maxn<<2];
// int n,pos;


// int rec(int L,int R) {
// 	if(L >= R) return 0;
// 	int root = pre[pos++];
// 	int mid = distance(in.begin(),find(in.begin(),in.end(),root));
// 	lch[root] = rec(L,mid);
// 	rch[root] = rec(mid+1,R);
// 	return root;
// }

// void bfs(int root) {
// 	queue<int> q;
// 	while(!q.empty()) q.pop();
// 	q.push(root);
// 	while(!q.empty()) {
// 		int top = q.front();q.pop();
// 		if(rch[top]) q.push(rch[top]);
// 		if(lch[top]) q.push(lch[top]);
// 		post.p_b(top);
// 	}
// }

// void solve() {
// 	pos = 0;
// 	int root = rec(0,n);
// 	bfs(root);
// 	inc(i,0,n-1) {
// 		if(i) cout<<' ';
// 		cout<<post[i];
// 	}
// 	cout<<endl;
// }

// int main() {
// 	ios::sync_with_stdio(0);
// 	cin.tie(0);
// 	cin>>n;
// 	int x;
// 	inc(i,1,n) {
// 		cin>>x;
// 		in.p_b(x);
// 	}
// 	inc(i,1,n) {
// 		cin>>x;
// 		pre.p_b(x);
// 	}
// 	solve();
// }