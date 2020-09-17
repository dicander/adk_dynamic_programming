#include <bits/stdc++.h>
#include <cassert>
using namespace std;

int main() {
    int N_VALUES, GOAL;
    cin >> N_VALUES >> GOAL;
    
    vector<int> v(N_VALUES, 0);
    for(int i=0; i<N_VALUES; ++i) {
        cin >> v[i];
    }
    vector<int> d(GOAL+2, 0);
    d[0] = 1;
    for(int i=0; i < N_VALUES; ++i) {
        for(int j = v[i]; j<=GOAL; ++j) {
            d[j] += d[j-v[i]];
        }
        for(int j=0; j<=GOAL; ++j) {
            cout << d[j] << " ";
        }
        cout << endl;
    }

    cout << d[GOAL] << endl;
}
