#include <iostream>
#include <string>
//#include <vector>
//#include <sstream>
//#include <sstream>
//#include <iomanip>
#include <algorithm>
//#include <iomanip>

using namespace std;

struct Node {
	int amt = 0;
	Node* l = NULL;
	Node* r = NULL;
};

Node* head;

void push(Node* cur, string& s, int idx) {
	if (idx == s.size())	return;

	if (s[idx] == '0') {
		if (cur->l == NULL)	cur->l = new Node;

		cur->l->amt++;
		push(cur->l, s, idx + 1);
	}
	else {
		if (cur->r == NULL)	cur->r = new Node;

		cur->r->amt++;
		push(cur->r, s, idx + 1);
	}
}

int search(Node* cur, string& s, int idx) {
	if (cur == NULL)	return 0;
	if (s.size() == idx)	return cur->amt;

	if (s[idx] == '0') return search(cur->l, s, idx + 1);
	if (s[idx] == '1')	return search(cur->r, s, idx + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, q;
	string s;

	head = new Node;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s;
		push(head, s, 0);
	}
	cin >> q;
	for (int i = 0; i < q; i++) {
		cin >> s;
		cout << search(head, s, 0) << '\n';
	}
	
	return 0;
}

