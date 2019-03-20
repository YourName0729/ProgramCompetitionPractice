#include <iostream>
//#include <sstream>
#include <string>
//#include <string.h>
//#include <vector>
//#include <math.h>
//#include <stdio.h>
#include <sstream>
//#include <sstream>
//#include <iomanip>
#include <algorithm>
//#include <queue>
#include <iomanip>

#define N 10000005

using namespace std;

bool exist[N];
int may;

void update() {
	if (may >= N)	return;
	if (exist[may]) {
		exist[may] = false;
		may++;
		update();
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, n;
	long long l, r, tmp;
	cin >> t;

	while (t--) {
		cin >> n >> l >> r;
		may = 0;

		for (int i = 0; i < n; i++) {
			cin >> tmp;
			tmp = tmp - l;

			if (tmp > N)	continue;
			if (tmp < may)	continue;

			if (tmp == may) {
				exist[tmp] = true;
				update();
			}
			else {
				exist[tmp] = true;
			}
		}

		if (r - l < (long long)(N - 1)) {
			for (int i = may; i <= r - l; i++) {
				exist[i] = false;
			}
		}
		else {
			for (int i = may; i < N - 1; i++) {
				exist[i] = false;
			}
		}

		/*for (int i = may; i <= min(long long(N - 1), r); i++) {
			exist[i] = false;
		}*/

		if (l + may > r) {
			cout << "^v^\n";
		}
		else {
			cout << l + may << '\n';
		}
	}
	
	return 0;
}

