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

	for(int b=n-1; b >= 2; --b) {

		for(int a=1; a<b; ++a) {
			int t=-1;
			for(int c=b+2;c<= n; ++c) {
				t=max(t,profit(chain,a,b,c)+q[b+1][c]);
			}
			q[a][b]=t;
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
	cout << "answer:" << dynprog(chain) << endl;
}