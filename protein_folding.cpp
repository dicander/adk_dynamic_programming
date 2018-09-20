#include <iostream>
#include <vector>
using namespace std;
static const int dbg = 1;


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

int dynprog(const string& chain) {
	int n = chain.size();
	vector<vector<int>> q(n+2,vector<int>(n+2,0));

	for(int fold = n-2; fold >= 2; --fold) {

		for(int start = 1; start < fold; ++start) {
			int optimal = -1;
			for(int end = fold + 2; end <= n; ++end) {
				optimal = max(optimal, profit(chain, start, fold, end) + q[fold + 1][end]);
			}
			q[start][end] = optimal;
		}
	}
	print_matrix(chain, q, n);
	int max_score=0;
	for(int b = 2; b<=n; ++b) {
		if(q[1][b]>max_score) {max_score=q[1][b]; }
	}
	return max_score;
}

int main() {
	string chain;
	cin >> chain;
	chain = " "+chain;
	int answer =  dynprog(chain);
	cout << "answer: " << answer << endl;
}
