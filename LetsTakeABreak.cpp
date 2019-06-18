#include <iostream>
//#include <deque>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

class State {
public:
	char board[5][5];
	int x, y;
	
	void operator=(const State& other) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				board[i][j] = other.board[i][j];
			}
		}
		x = other.x;
		y = other.y;
	}
	
	void move(int a, int b) {
		char tmp = board[x][y];
		board[x][y] = board[a][b];
		board[a][b] = tmp;
		
		x = a;
		y = b;
	}
	
	bool operator<(const State& other) const {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (board[i][j] != other.board[i][j])
					return board[i][j] < other.board[i][j]; 
			}
		}
		return false;
	}
	
	bool operator==(const State& other) const {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (board[i][j] != other.board[i][j])	return false;
			}
		}
		return true;
	}
	
	friend istream& operator>>(istream& in, State& s) {
		char tmp;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				in >> tmp;
				s.board[i][j] = tmp;
				if (tmp == 'W') {
					s.x = i;
					s.y = j;
				}
			}
		}
		return in;
	}
	
	friend ostream& operator<<(ostream& out, const State& s) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				cout << s.board[i][j];
			}
			cout << '\n';
		}
		cout << s.x << ' ' << s.y << '\n';
	}
};

const int drct[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

bool legal(int i, int j) {
	if (i < 0 || i >= 5)	return false;
	if (j < 0 || j >= 5)	return false;
	return true;
}

set<State> all;
void show() {
	cout << "show time\n";
	for (auto it = all.begin(); it != all.end(); it++) {
		cout << *it;
		cout << it->x << ' ' << it->y << "\n\n";
	}
}


void run1(State stt, int fx, int fy, int step, int stop) {
	//cout << "now step = " << step << '\n';
	//cout << stt << '\n';
	if (step == stop) {
		//cout << "get one!\n";
		//cout << stt << '\n';
		all.insert(stt);
		return;
	}
	for (int i = 0; i < 8; i++) {
		int tox = stt.x + drct[i][0], toy = stt.y + drct[i][1];
		//cout << "try go to " << tox << ' ' << toy << '\n';
		if (fx == tox && fy == toy)	continue;
		if (!legal(tox, toy))	continue;
		stt.move(tox, toy);
		//cout << "a legal one!\n";
		//cout << stt << '\n';
		run1(stt, tox - drct[i][0], toy - drct[i][1], step + 1, stop);
		stt.move(tox - drct[i][0], toy - drct[i][1]);
	}
}

bool run2(State stt, int fx, int fy, int step, int stop) {
	if (step == stop) {
		//cout << "find one\n";
		//cout << stt << '\n';
		if (all.find(stt) == all.end()) {
			//cout << "not found!\n";
			return false;	
		}
		else {
			//cout << "found it !!!!\n";
			return true;
		}
		return all.find(stt) != all.end();
	}
	for (int i = 0; i < 8; i++) {
		int tox = stt.x + drct[i][0], toy = stt.y + drct[i][1];
		if (fx == tox && fy == toy)	continue;
		if (!legal(tox, toy))	continue;
		stt.move(tox, toy);
		bool res = run2(stt, tox - drct[i][0], toy - drct[i][1], step + 1, stop);
		if (res)	return true;
		stt.move(tox - drct[i][0], toy - drct[i][1]);
	}
	return false;
}

int main() {
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL); 
	
	int t;
	State ini, tar;
	
	cin >> t;
	while (t--) {
		cin >> ini >> tar;
		
		if (ini == tar) {
			cout << "0\n";
			continue;
		}
		
		for (int step = 1; step <= 20; step++) {
			//cout << "step = " << step << '\n';
			int stepf = step / 2;
			int stepb = step - stepf;
			
			all.clear();
			run1(ini, 100, 100, 0, stepf);
			//show();
			if (run2(tar, 100, 100, 0, stepb)) {
				cout << step << '\n';
				break;
			}
		}
	}
	

	
	return 0;
} 
