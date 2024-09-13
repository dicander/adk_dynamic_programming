#include <iostream>

using namespace std;

int sequence_c(int n) {
    switch (n) {
        case 0:
            return -1;
        case 1:
            return 4;
        case 2:
            return 5;
        default:
            int lastlast = 4;
            int last = 5;
            for(int i=3; i<=n; ++i) {
                int temp = max(lastlast, last - lastlast + 7);
                lastlast = last;
                last = temp;
            }
            return last;
    }
    return -1;
}

int main() {
    for(int i=1; i<=7; ++i) {
        cout << "iteration: " << i << endl;
        cout << sequence_c(i) << endl;
    }
}