#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> matrix;

static const int inf = 1<<30;

void print_matrix(const matrix& m) {
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            cout << setw(2) << (m[i][j]) << " ";
        }
        cout << endl;
    }
    cout << endl;
}


void print_sophisticated(matrix& M, matrix& D) {
    // Prints the values in the first matrix using two digits and the second value using two digits
    // with the format [ 1:12] [ 2:23]

    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            cout << "[" << setw(2) << M[i][j] << ":" << setw(2) << D[i][j] << "] ";
        }
        cout << endl;
    }
    cout << endl;

}

void transpose(matrix& M) {
    int temp;
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8 ; ++j) {
            if(i<=j)continue;
            temp = M[i][j];
            M[i][j] = M[j][i];
            M[j][i] = temp;
        }
    }
}


int main() {
    srand(time(NULL));
    matrix M(8, vector<int>(8, 0));
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            M[i][j] = 1 + rand()%9;
        }
    }
    cout << "The Swamp!" << endl;
    print_matrix(M);
    transpose(M);
    cout << "Transposed!" << endl;
    print_matrix(M);
    matrix D(8, vector<int>(8, inf));
    // BASE CASE
    for(int i=0; i<8; ++i) {
        D[0][i] = M[0][i];
    }
    for(int i=1; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            for(int k = -1; k<2; ++k) {
                int x = j-k;
                if(0<=x && x<8) {
                    D[i][j] = min(D[i-1][x]+M[i][j], D[i][j]);
                }
            }
        }
    }
    print_matrix(D);
    print_sophisticated(M, D);
}
