#include <iostream>
#include <vector>
using namespace std;
static const int dbg = 0;
#define dout if(dbg)cout

int profit(const string& chain, int a, int b, int c) {
	int shortest=min(b-a,c-(b+1));
	int s=0;
	for(int i=1; i<=shortest; ++i) {
		if (chain[b-i]=='1' && chain[b+1+i]=='1') {
			++s;
		}
	}
	return s;
}

void print_matrix(const string& chain, const vector<vector<int>>& q, int n) {
	printf("idx");
	for(int i=1; i<n; ++i) {
		printf("%3d ", i);
	}
	printf("\n");
	printf("str");
	for(int i=1; i<n; ++i) {
		printf("  %c ", chain[i]);
	}
	printf("\n===");
	for(int i=1; i<n; ++i) {
		printf("====");
	}
	printf("\n");
	for(int i=1; i<n; ++i) {
		printf("%2d:", i);
		for(int j=1; j<n; ++j) {
			printf("%3d ", q[i][j]);
		}
		printf("\n");
	}
}

int find_max_index(vector<vector<int>>& q, int row, int size) {
	int best = -1;
	int best_index = 0;
	for(int i=1; i<=size; ++i) {
		if(q[row][i]>=best) {
			best_index = i;
			best = q[row][i];
		}
	}
	return best_index;
}

int dynprog(const string& chain) {
	int n = chain.size();
	vector<vector<int>> q(n+2,vector<int>(n+2,0));
	vector<vector<int>> f(n+2,vector<int>(n+2,0));
	int fold_point;
	for(int b=n-1; b >= 2; --b) {
		for(int a=1; a<b; ++a) {
			int t=-1;
			for(int c=b+2;c<= n; ++c) {
				int candidate = profit(chain,a,b,c)+q[b+1][c];
				if( candidate > t ) {
					t = candidate;
				}
				fold_point = c;
			}
			q[a][b]=t;
			f[a][b]=fold_point;
		}
	}
	print_matrix(chain, q, n);
	int max_score=0;
	for(int b = 2; b<=n; ++b) {
		if(q[1][b]>=max_score) {
			max_score=q[1][b];
		}
	}
	// Let's solve this beast
	int width = 2*n+5;
	int height = n+5;
	int string_index = 1;
	int x = width / 2;
	int dx = 1;
	int max_x = x;
	int min_x = x;
	int y = 0;
	int next_fold = find_max_index(q, 1, n);
	int old_fold = 1;
	vector<vector<char>> m(height, vector<char>(width, ' '));
	for(y=1; true; ++y) {
		if(y%2) {
			dx = 1;
		} else {
			dx = -1;
		}
		while(true) {
			if(string_index>=n) break;
			dout << y << " <y x> " << x << " string_index " << string_index << endl;
			if(dbg && string_index <=n) {
				dout << "current letter" << chain[string_index]<< endl;
			}
			m[y][x] = chain[string_index];
			//dout << "waiting for next fold " << next_fold << " now" << endl;
			if(string_index == next_fold) {
				int temp = next_fold;
				next_fold = f[old_fold][next_fold];
				old_fold = temp;
				//dout << "string_index + 1 = " << string_index + 1 << endl;
				//dout << "new next fold " << next_fold << endl;
				string_index++;
				break;
			}
			string_index++;
			if(string_index>=n) break;
			x += dx;
			if (x > max_x) {
				max_x = x;
			}
			if (x < min_x) {
				min_x = x;
			}
		}
		if(string_index>=n) break;
	}
	dout << "y is " << y << " max_x= " << max_x << " min_x " << min_x << endl;
	cout << endl;
	cout << "How to fold: " << endl;
	for(int i = 1; i <= y; ++i) {
		for(int j = min_x; j <= max_x; ++j) {
			cout << m[i][j];
		}
		cout << endl;
	}
	return max_score;
}

int main() {
	string chain;
	cin >> chain;
	chain = " "+chain;
	int answer =  dynprog(chain);

	cout << endl << "answer: " << answer << endl;
}
