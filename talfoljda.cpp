#include <iostream>

using namespace std;

int sequence_a(int N) {
    int answer = 0;
    for(int i=1; i<N; ++i) {
        answer = answer*2 + 1;
    }
    return answer;
}


int main() {
    int N;
    cin >> N;
    int answer = sequence_a(N);
    cout << answer << endl;
}