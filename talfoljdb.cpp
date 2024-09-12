#include <iostream>
#include <cmath>

using namespace std;


int talfoljd_b(int N) {
    switch(N) {
        case 0:
            return -1;
        case 1:
            return 4;
        case 2:
            return 5;
        default:
            int lastlast = 4;
            int last = 5;
            int answer = 0;
            for(int i=3; i<=N; ++i) {
                answer = max(last,
                    max(lastlast, last-lastlast+7));
                lastlast = last;
                last = answer;
            }
            return answer;
    }
    return -1;
}


int talfoljd_b_optimized(int N) {
    if(N <= 0) {
        return -1;
    } else if (N == 1) {
        return 4;
    } else if (N == 2) {
        return 5;
    } else if (N == 3) {
        return 8;
    } else if (N >= 4) {
        return 10;
    }
    return -1;
}



int main() {
    for(int i=1; i<=7; ++i) {
        cout << "iteration: " << i << endl;
        cout << talfoljd_b(i) << endl;
        cout << talfoljd_b_optimized(i) << endl;
    }
}