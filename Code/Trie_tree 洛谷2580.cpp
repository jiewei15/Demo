#include<bits/stdc++.h>
using namespace std;

struct Trie
{
	struct Node {
		char val;
		vector<Node*> sub;
		bool endQ;
		int rep;
	}*root = new Node;

	void add(const char str[]) {
		Node *p = root;
		unsigned int j = 0;
		for(unsigned int i = 0;i < strlen(str);i++) {
			for(j = 0;j < p->sub.size();j++) {
				if(p->sub[j]->val == str[i]) break;
			}
			if(j == p->sub.size()) {
				Node *t = new Node;
				t->val = str[i];
				t->sub.clear();
				t->endQ = false;
				t->rep = 0;
				p->sub.push_back(t);
				p = t;
			}
			else {
				p = p->sub[j];
			}
		}
		p->endQ = true;
	}

	int query(const char str[]) {
		Node *p = root;
		unsigned int j = 0;
		for(unsigned int i = 0;i < strlen(str);i++) {
			for(j = 0;j < p->sub.size();j++) {
				if(p->sub[j]->val == str[i]) break;
			}
			if(j == p->sub.size()) return 0;
			p = p->sub[j];
		}
		if(p->endQ) p->rep++;
		if(p->rep > 1) return 1;
		if(p->rep == 1) return 2;
		return 0;
	}
}Te;

int main() {
	int n,m;
	char st[55];
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%s",st);
		Te.add(st);
	}
	scanf("%d",&m);
	while(m--) {
		scanf("%s",st);
		int ans = Te.query(st);
		if(ans == 0) printf("WRONG\n");
		else if(ans == 1) printf("REPEAT\n");
		else printf("OK\n");
	}
	return 0;
}