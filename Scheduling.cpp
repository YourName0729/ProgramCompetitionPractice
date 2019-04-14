#include <iostream>
#include <map>
#include <deque>
#include <set>
#include <stack>
#include <vector>
//#include <sstream>
//#include <string>
//#include <cmath>
//#include <iomanip>

using namespace std;

class Stack {
public:
	Stack(int id) {
		push(id);
	}
	
	struct Node {
		int id;
		Node* next = NULL;
	};	
	Node* head = NULL;
	int _size = 0;
	
	void push(int id) {
		_size++;
		if (head == NULL) {
			head = new Node;
			head->id = id;
		}
		else {
			Node* tmp = new Node;
			tmp->id = id;
			tmp->next = head;
			head = tmp;
		}
	}
	void pop() {
		_size--;
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
	int top() {
		return head->id;
	}
	int size() {
		return _size;
	}
};

int n;
int g[1000010];
vector<bool> is(1000010, false);

int offset = 0;
int head = 0;

map<int, int> m;
deque<Stack> dq;

bool existGroup(int gou) {
	return m.find(gou) != m.end();
}
int idxOfGroup(int gou) {
	return m[gou] - offset;
}
bool exist(int id) {
	return is[id];
}
void push(int id) {
	if (existGroup(g[id])) {
		int idx = idxOfGroup(g[id]);
		
		dq[idx].push(id);
		//dq[idx].push(id);
		is[id] = true;
	}
	else {
		//stack<int> stmp;
		//stmp.push(id);
		is[id] = true;
		dq.push_back(Stack(id));
		//add(dq.back(), id);
		m[g[id]] = head;
		//m.insert(g[id], head);
		
		head++;
	}
}
int top() {
	return dq[0].top();
}
void pop() {
	if (dq[0].size() == 1) {
		offset++;
		is[top()] = false;
		m.erase(g[top()]);
		dq.pop_front();		
	}
	else {
		//cout << top() << " be false\n"; 
		is[top()] = false;
		dq[0].pop();
		//Node* todel = dq[0];
		//dq[0] = todel->next;
		//delete todel;
		//dq[0].pop();
	}	
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int q, c, tar;
	
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		cin >> g[i];
	}
	
	while (q--) {
		cin >> c;
		switch(c) {
			case 1:
				cin >> tar;
				if (exist(tar)) {
					cout << "Ignore\n";
				}
				else {
					push(tar);
					cout << "Successful\n";
				}
				break;
				
			case 2:
				if (dq.size() == 0) {
					cout << "0\n";
				}
				else {
					cout << top() << '\n';
					pop();
				}
				break;
		}
	}	
	
	return 0;
}
