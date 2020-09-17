#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> matrix;
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

void print_matrix(const string& chain, const matrix& q, int n) {
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

int find_max_index(matrix& q, int row, int size) {
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


//Also count points so they match!
pair<int, int> find_max_index_qualified(matrix& q, int row, int size, int current_score, const string& chain, int last_fold) {
        dout << "find_max_index_qualified called with current_score " << current_score << " row " << row << endl;
        dout << "last_fold = " << last_fold << endl;
        if(dbg && chain.size() > 20) {
            cout << "profit 1, 7, 15" << profit(chain, 1, 7, 15) << endl;
        }
        int best_index = 0;
        pair<int, int> p(0, 0);
	for(int i=row+1; i<=size; ++i) {
                int new_score = q[row][i];
		if(current_score == profit(chain, last_fold, row-1, i)+ new_score) {
                        dout << "returning from find_max_index_qualified with" << i << " <i new_score> " << new_score << endl;
			p = pair<int, int>(i, new_score);
		}
	}
	return p;
}





int dynprog(const string& chain) {
	int n = chain.size();
	matrix q(n+2,vector<int>(n+2,0));
	matrix f(n+1,vector<int>(n+2,0));
	int fold_point;
	for(int b=n-1; b >= 2; --b) {

		for(int a=1; a<b; ++a) {
			int t=-1;
			for(int c=b+2;c<= n; ++c) {
				int candidate = profit(chain,a,b,c)+q[b+1][c];
				if( candidate > t ) {
					t = candidate;
					fold_point = c;
				}

			}
			q[a][b]=t;
			f[a][b]=fold_point;
		}
	}
	print_matrix(chain, q, n);
	printf("\n");
	print_matrix(chain, f, n);
	int max_score=0;
	int max_start=0;
	for(int b = 2; b<=n; ++b) {
		if(q[1][b]>=max_score) {
			max_score=q[1][b];
			max_start = b;
			fold_point = f[1][b];
		}
	}
	// Let's solve this beast
	int width = 2*n+5;
	int height = n+5;
	int string_index = 1;
	int x = width / 2;
	int dx = 1;
	int max_x = 2*n+4;
	int min_x = 0;
	int y = 0;
        vector<int> folds(1,1);
        folds.push_back(find_max_index(q, 1, n));
	vector<vector<char>> m(height, vector<char>(width, ' '));
        int current_max = max_score;
	for(y=1; true; ++y) {
		if(y%2) { //direction of the snake
			dx = 1;
		} else {
			dx = -1;
		}
		while(true) {
			if(string_index>=n) break;
			dout << y << " <y x> " << x << " string_index " << string_index << endl;
			m[y][x] = chain[string_index];
			if(string_index == folds.back()) {
                                pair<int, int> p = find_max_index_qualified(q, folds.back()+1, n, current_max, chain, folds[folds.size()-2]); 
				folds.push_back(p.first);
                                current_max = p.second;
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
        if(dbg) {
            cout << "FOLDS" << endl;
            for(auto it=folds.begin(); it!=folds.end(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        }
	dout << "y is " << y << " max_x= " << max_x << " min_x " << min_x << endl;
	//print the snake
        for(int i = 1; i <= y; ++i) {
		for(int j = min_x; j <= max_x; ++j) {
			printf("%c", m[i][j]);
		}
		printf("\n");
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
