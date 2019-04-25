#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Trim {
	long long amt = 0;
	long long cnt = 0;
};

long long n, m;
long long a1[50010], a2[50010];
vector<Trim> v1, v2;

void add(vector<Trim>& v, long long a, long long b) {
	Trim tmp;
	tmp.amt = a;
	tmp.cnt = b;
	v.push_back(tmp);
}

void trim() {
	for (int i = 0; i < n; i++) {
		if (v1.empty() || v1[v1.size() - 1].amt != a1[i])
			//v1.push_back(Trim{ .amt = a1[i], .cnt = 1});
			add(v1, a1[i], 1);
		else
			v1[v1.size() - 1].cnt++;
	}
	for (int i = 0; i < m; i++) {
		if (v2.empty() || v2[v2.size() - 1].amt != a2[i])
			//v2.push_back(Trim{a2[i], 1});
			add(v2, a2[i], 1);
		else
			v2[v2.size() - 1].cnt++;
	}
}

long long go(long long cur) {
	long long cnt = 0, i = 0, j = v2.size() - 1;
	
	while(i < v1.size() && j >= 0) {
		if (v1[i].amt + v2[j].amt > cur) {
			j--;
		}
		else if (v1[i].amt + v2[j].amt < cur) {
			i++;
		}
		else {
			cnt += v1[i].cnt * v2[j].cnt;
			j--;
			i++;
		}
	}
	
	
	return cnt;
}

int main()
{
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
 
	long long q, tmp;
	cin >> n >> m >> q;
	
	n++;
	m++;
	
	a1[0] = 0;
	a2[0] = 0;
	
	for (int i = 1; i < n; i++) {
		cin >> a1[i];
	}
	for (int i = 1; i < m; i++) {
		cin >> a2[i];
	}
 
 	sort(a1, a1 + n);
 	sort(a2, a2 + m);
 	
 	trim();
 
	while(q--) {
		cin >> tmp;
		cout << go(tmp) << '\n';
	}
 
	return 0;
}
