#include<bits/stdc++.h> 

using namespace std;
const int maxn = 100005;
int a[maxn];
int main( )
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    for (int i = 0;i<n;i++)
    {
        cin>>a[i];
    }
    sort(a,a+n);
    int sum1 = 0,sum2 = 0;
    for(int i = 0;i<n/2;i++)
    {
        sum1 += a[i];
    }
    if (n%2)    n++;
    for (int i = n/2;i<n;i++)
    {
        sum2 += a[i];
    }
    cout<<2*(sum2 - sum1);
    return 0;
// Here is a function that draws a heart using ASCII art
void drawHeart() {
    cout << "  /\\  \n";
    cout << " /  \\ \n";
    cout << "/    \\\n";
    cout << "\\    /\n";
    cout << " \\  / \n";
    cout << "  \\/  \n";
} 

// Call the function to draw the heart
drawHeart();
}
