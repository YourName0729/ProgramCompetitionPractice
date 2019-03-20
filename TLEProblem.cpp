#include <iostream>
//#include <sstream>
//#include <string>
//#include <string.h>
//#include <vector>
//#include <math.h>
//#include <stdio.h>
//#include <sstream>
//#include <sstream>
//#include <iomanip>
#include <algorithm>
//#include <queue>
//#include <iomanip>
#include <deque>

using namespace std;

struct Data {
	int max;
	int len;
};

deque<Data> dq;

void show() {
	for (int i = 0; i < dq.size(); i++) {
		cout << '(' << dq[i].max << ", " << dq[i].len << ") ";
	}
	cout << '\n';
}
int search(int tar) {
	//cout << "search for " << tar << '\n';

	if (dq.size() == 0) return -1;
	if (dq[dq.size() - 1].max >= tar) return -1;

	int l = 0, r = dq.size() - 1, mid;
	while (l < r) {
		mid = (l + r) / 2;
		if (dq[mid].max >= tar) {
			l = mid + 1;
		}
		else {
			r = mid;
		}
	}

	return l;
}
void push(int m, int l) {
	//cout << "append " << m << ' ' << l << '\n';

	Data d = {m, l};
	dq.push_back(d);
}
void trim(int cur) {
	//cout << "trim for " << cur << '\n';
	//show();

	if (cur != 0) {
		if (dq[cur - 1].max >= dq[cur].max && dq[cur - 1].len <= dq[cur].len) {			
			dq[cur - 1].max = dq[cur].max;
			cur--;
		}
	}
	while (dq.size() > cur + 1)	dq.pop_back();
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, n, in, res;
	cin >> t;

	while (t--) {
		dq.clear();

		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> in;

			res = search(in);
			if (res == -1) {				
				push(in, 1);
				res = dq.size() - 1;
			}
			else {
				dq[res].max = in;
				dq[res].len++;				
			}
			trim(res);
			//show();
		}

		int ans = 0;
		for (int i = 0; i < dq.size(); i++) {
			ans = max(ans, dq[i].len);
		}
		cout << ans << '\n';
	}
	
	return 0;
}

