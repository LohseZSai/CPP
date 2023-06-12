#include<bits/stdc++.h>
using namespace std;

void hanoi(int n, char A, char B, char C) {
    if (n == 1) {
        cout << "Move disk 1 from rod " << A << " to rod " << C << endl;
        return;
    }
    hanoi(n - 1, A, C, B);
    cout << "Move disk " << n << " from rod " << A << " to rod " << C << endl;
    hanoi(n - 1, B, A, C);
}


int main(){
    hanoi(3,'A','B','C');
}