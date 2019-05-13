#include <iostream>
#include <map>
//#include <stdio.h>
//#include <queue>
//#include <string>
//#include <vector>
#include <algorithm>
//#include <sstream>

using namespace std;

struct Node {
	//int l, r;
	int d;
	Node *nl = NULL, *nr = NULL;
};

int GCD(int a, int b) {
	if (b) while((a %= b) && (b %= a));
	return a + b;
}

void build(Node* cur, int l, int r) {
	cur->d = 1;
	if (l == r)	return;
	int mid = (l + r) / 2;
	cur->nl = new Node;
	cur->nr = new Node;
	build(cur->nl, l, mid);
	build(cur->nr, mid + 1, r);
}

int query(Node* cur, int l, int r, int f, int t) {
	//cout << "q " << l << ' ' << r << ' ' << f << ' ' << t << '\n';
	if (l == f && r == t) {
		//cout << "cur->d = " << cur->d << '\n';
		return cur->d;
	}	
	
	int mid = (l + r) / 2;
	if (t <= mid)	return query(cur->nl, l, mid, f, t);
	else if (mid + 1 <= f)	return query(cur->nr, mid + 1, r, f, t);
	return GCD(query(cur->nl, l, mid, f, mid), query(cur->nr, mid + 1, r, mid + 1, t));
}

void set(Node* cur, int l, int r, int tar, int x) {
	//cout << "s " << l << ' ' << r << ' ' << tar << ' ' << x << '\n';
	if (l == r) {
		cur->d = x;
		return;
	}
	int mid = (l + r) / 2;
	if (tar <= mid)	set(cur->nl, l, mid, tar, x);
	else 			set(cur->nr, mid + 1, r, tar, x);
	cur->d = GCD(cur->nl->d, cur->nr->d);
}

void del(Node* cur) {
	if (cur == NULL)	return;
	del(cur->nl);
	del(cur->nr);
	delete cur;
}

int n;
Node* root = NULL;

int bs(int l, int r, int ub) {
	if (l == r)	return l;
	
	int mid = (l + r) / 2;
	if (query(root, 1, n, l, mid) > ub)	return bs(mid + 1, r, ub);
	else 								return bs(l, mid, ub);
}

int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    
    int t, q, type, i, v;
    
    cin >> t;
    while (t--) {
    	cin >> n >> q;
    	
    	root = new Node;
    	build(root, 1, n);
    	while (q--) {
    		cin >> type >> i >> v;
    		if (type == 1) {
    			set(root, 1, n, i, v);
			}
			else {
				if (query(root, 1, n, i, n) > v) {
					cout << "DOYA!\n";
				}
				else {
					cout << bs(i, n, v) << '\n';
				}
			}
		}
		del(root);
	}
    
      
	return 0;
}

