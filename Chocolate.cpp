#include <iostream>
#include <string>
//#include <map>
#include <vector>
//#include <sstream>
#include <set>
//#include <iomanip>
//#include <algorithm>
//#include <iomanip>

using namespace std;

class Pos {
public:
	Pos() : x(0), y(0) {}
	Pos(int a, int b) : x(a), y(b) {}
	int x, y;
	bool upperThan(int x, int y) const {
		return this->x >= x && this->y >= y;
	}
	bool operator<(const Pos& oth) const {
		if (x == oth.x)	return y > oth.y;
		return x < oth.x;
	}
};
using Ctn = set<Pos>;

int n, m;
Ctn s;

void show() {
	for (auto it = s.begin(); it != s.end(); it++) {
		cout << "(" << it->x << ", " << it->y << ") ";
	}
	cout << '\n';
}

bool upper(int x1, int y1, int x2, int y2) {
	return x1 >= x2 && y1 >= y2;
}
int area(Ctn::iterator it, int x, int y) {
	return (it->x - x + 1) * (it->y - y + 1);
}
int call(int x, int y) {
	Ctn::iterator from = s.lower_bound(Pos(x, m - 1));
	if (from == s.end())	return 0;
	if (!from->upperThan(x, y))	return 0;

	Ctn::iterator patch1 = s.lower_bound(Pos(x - 1, m - 1));
	if (patch1->x != x - 1 && x != 0) {
		s.insert(Pos(x - 1, from->y));
	}

	vector<Ctn::iterator> toErase;
	int re = 0;
	while (from != s.end() && from->upperThan(x, y)) {
		re += area(from, x, y);
		x = from->x + 1;
		toErase.push_back(from);
		from++;
	}

	Ctn::iterator patch2 = s.lower_bound(Pos(x, y));
	if (patch2 != s.end() && patch2->y != y - 1) {
		s.insert(Pos(x - 1, y - 1));
	}
	else if (patch2 == s.end() && y != 0) {
		s.insert(Pos(x - 1, y - 1));
	}

	for (auto it = toErase.begin(); it != toErase.end(); it++) {
		s.erase(*it);
	}

	return re;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int q;
	int a, b, res;

	cin >> n >> m >> q;
	s.insert(Pos(n - 1, m - 1));

	while (q--) {
		cin >> a >> b;

		res = call(n - a, m - b);
		if (res == 0) {
			cout << "QAQ\n";
		}
		else {
			cout << res << '\n';
		}
		//show();
	}
	cout << call(0, 0) << '\n';

	//system("pause");
	return 0;
}

