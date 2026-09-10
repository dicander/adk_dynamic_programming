#include <bits/stdc++.h>

using namespace std;

static const int DBG = 1;

typedef vector<vector<int>> matrix;


int main() {
	string a, b;
	
	cin >> a;
	cin >> b;
	a = " " + a;
	b = " " + b;
	int m = a.size();
	int n = b.size();
	matrix d(n, vector<int>(m, 0));
	cout << " " << a << endl;
	cout << " ";
	for(int i=0; i<m; ++i) {
		cout << 0;
	}
	cout << endl;
	for(int j=1; j<n; ++j) {
		cout << b[j] << 0;
		for (int i=1; i<m; ++i) {
			if (a[i] == b[j]) {
				d[j][i]= 1 + d[j-1][i-1];
				cout << d[j][i];
			} else {
				cout << 0;
			}
		}
		cout << endl;
	}
	
}
