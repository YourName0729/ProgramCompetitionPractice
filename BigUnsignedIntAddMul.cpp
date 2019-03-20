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

#define N 300
#define Unit 1000000000
#define Pow 9

using namespace std;
using Type = long long;

struct BigInt {
	Type a[N] = {};
	int size = 0;
};

BigInt a, b, buf;

void show(BigInt& bi);

void init(BigInt& bi) {
	for (int i = 0; i < N; i++) {
		bi.a[i] = 0;
	}
	bi.size = 0;
}
void clear(BigInt& bi) {
	/*cout << "clear ";
	show(buf);
	cout << '\n';*/

	for (int i = 0; i < bi.size; i++) {
		bi.a[i] = 0;
	}
	bi.size = 0;

	/*cout << "after clear ";
	show(buf);
	cout << '\n';*/
}
void carry(BigInt& bi, int dgt) {
	//cout << "check " << dgt << "-th " << int(bi.a[dgt]) << '\n';
	if (bi.a[dgt] == 0)	return;
		
	bi.size = max(bi.size, dgt + 1);

	//cout << "len = " << bi.size << '\n';

	if (bi.a[dgt] < Unit)	return;

	//cout << "carry~\n";

	bi.size = max(bi.size, dgt + 2);

	bi.a[dgt + 1] += bi.a[dgt] / Unit;
	bi.a[dgt] %= Unit;
	carry(bi, dgt + 1);
}
void copy(BigInt& org, BigInt& tar) {
	/*cout << "copy ";
	show(org);
	cout << " => ";
	show(tar);
	cout << " = ";*/

	for (int i = tar.size - 1; i >= org.size; i--) {
		tar.a[i] = 0;
	}

	for (int i = 0; i < org.size; i++) {
		tar.a[i] = org.a[i];
	}
	tar.size = org.size;

	/*show(tar);
	cout << '\n';*/
}

char input(BigInt& bi, stringstream& ss) {
	char tmp;

	clear(bi);

	int idx = 0;
	while (ss >> tmp) {
		if ('0' <= tmp && tmp <= '9') {
			buf.a[idx] = tmp - '0';
			idx++;
		}
		else {
			break;
		}
	}

	/*for (int i = 0; i < idx; i++) {
		cout << buf.a[i] << ' ';
	}
	cout << '\n';*/

	int cur = 0;
	for (int i = idx - Pow; i >= 0; i-= Pow) {
		for (int j = i; j < i + Pow; j++) {
			bi.a[cur] *= 10;
			bi.a[cur] += buf.a[j];
		}
		cur++;
	}
	if (idx % Pow != 0) {
		for (int i = 0; i < idx % Pow; i++) {
			bi.a[cur] *= 10;
			bi.a[cur] += buf.a[i];
		}
		cur++;
	}

	buf.size = idx;
	bi.size = cur;

	/*cout << "input ";
	show(bi);
	cout << '\n';*/

	/*for (int i = idx; i < N; i++) {
		bi.a[i] = 0;
	}*/
	clear(buf);

	/*cout << "get ";
	show(bi);
	cout << '\n';*/

	return tmp;
}
void output(BigInt& bi) {
	int idx = bi.size;
	if (idx == 0 || (idx == 1 && bi.a[0] == 0)) {
		cout << '0';
		return;
	}

	int p;

	cout << bi.a[idx - 1];
	for (int i = idx - 2; i >= 0; i--) {
		p = Unit / 10;
		while (p != 0 && bi.a[i] / p == 0) {
			cout << '0';
			p /= 10;
		}
		if(p)	cout << bi.a[i];
	}

	/*int idx = N - 1;
	while (idx >= 0 && bi.a[idx] == 0)	idx--;

	if (idx == -1)	cout << '0';

	for (int i = idx; i >= 0; i--) {
		cout << int(bi.a[i]);
	}*/
}
void show(BigInt& bi) {
	cout << '(';
	output(bi);
	cout << ", " << bi.size << ')';
}

void add(BigInt& sum, BigInt& tmp) {
	/*show(sum);
	cout << " + ";
	show(tmp);
	cout << " = ";*/

	for (int i = 0; i < max(sum.size, tmp.size); i++) {
		sum.a[i] += tmp.a[i];
		carry(sum, i);
	}

	/*show(sum);
	cout << '\n';*/
}
void mul(BigInt& sum, BigInt& tmp) {
	/*show(sum);
	cout << " * ";
	show(tmp);
	cout << " = ";*/

	clear(buf);
	/*cout << "buf = ";
	show(buf);
	cout << '\n';*/

	for (int i = 0; i < sum.size; i++) {
		for (int j = 0; j < tmp.size; j++) {
			//cout << i + j << "-th = " << int(buf.a[i + j]) << '\n';
			buf.a[i + j] += sum.a[i] * tmp.a[j];
			//cout << i + j << " += " << sum.a[i] * tmp.a[j] << " be " << int(buf.a[i + j]) << '\n';
			carry(buf, i + j);
		}
	}

	/*cout << "after buf = ";
	show(buf);
	cout << '\n';*/

	copy(buf, sum);
	clear(buf);

	/*show(sum);
	cout << '\n';*/
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string s;

	//init(a);
	//init(b);
	//init(buf);

	while (getline(cin, s)) {
		char opr;
		
		stringstream ss;

		ss << s;

		opr = input(a, ss);

		while (true) {
			if (opr == '+') {
				opr = input(b, ss);
				add(a, b);
			}
			else if (opr == '*') {
				opr = input(b, ss);
				mul(a, b);
			}
			else {
				//cout << "last, break\n";
				break;
			}
			/*show(a);
			cout << '\n';*/
		}
		output(a);
		cout << '\n';
	}
	
	return 0;
}

