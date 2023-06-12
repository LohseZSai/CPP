

//该题的可以分成两部分，即素数判断+组合选取

// 素数判断:试除法
// bool isPrime(int n){
//     if(n <= 1) return false;
//     else if(n >= 2){
//         double m = sqrt(n);
//         for(int i=2;i<=m;i++)
//             if (n % i == 0) return false;
//         return true;
//     }
// }

// int combines_result(int a[], int combinelength, int numschose){
//         int num = 0;
//         int results[combinelength]={0};
//         if(numschose == 1){
//             return combinelength;
//         }
//         else{
//             for(int i=0;i<combinelength;i++){
                
//             }
//             combines_result(a,combinelength-1,numschose-1) + combines_result(a,combinelength-1,numschose);
//         }
        
// }

// #include <iostream>
// using namespace std;
// void cage(int a[], int n, int k, int b[], int index,int &count) {
//     int finalsum = 0; 
//     if (k == 0) {
//         // 输出a数组中的全部元素
//         for (int i = 0; i < index; ++i) {
//             finalsum += a[i];
//             cout << a[i] << " ";
//         }
//         if(isPrime(finalsum) == true) count++;
//         cout << endl;
//     }
//     for (int i = n-1; i >= k-1; --i) {
//         // 选取第i个数
//         a[k-1] = b[i];
//         cage(a, i, k-1, b, index,count);
//     }
// }

// int main(){
//     int n = 4, k = 2;
//     int b[n] = {1,2,3,4};
//     int a[k] = {0};
//     int count = 0;
//     cage(a, n, k, b, k, count);
// }

#include<bits/stdc++.h>
using namespace std;


//该题的可以分成两部分，即素数判断+组合选取

// 素数判断:试除法
bool isPrime(int n){
    if(n <= 1) return false;
    else if(n >= 2){
        double m = sqrt(n);
        for(int i=2;i<=m;i++)
            if (n % i == 0) return false;
        return true;
    }
}

int combination_sum_is_prime(int a[], int n, int k, int sum, int index){
    if(k == 0){
        if(isPrime(sum)) return 1;
        else return 0;
    }
    else if(index == n) return 0;
    else{
        return combination_sum_is_prime(a,n,k-1,sum+a[index],index+1) + combination_sum_is_prime(a,n,k,sum,index+1);
    }
}

void list_the_combination(int a[], int n, int k, int choselength, int index,int b[]){
    // 如果已经选取了k个元素
    if(k == 0){
        // 输出当前组合
        for(int i=0;i<choselength;i++){
            cout << b[i] << " ";
        }
        cout << endl;
    }
    // 如果已经遍历完了数组
    else if(index == n) return;
    else{
        // 选取当前元素，继续递归计算
        b[choselength] = a[index];
        list_the_combination(a,n,k-1,choselength+1,index+1,b);
        // 不选取当前元素，继续递归计算
        list_the_combination(a,n,k,choselength,index+1,b);
    }
}


int main(){
    int n,k;
    cin>>n>>k;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    cout<<combination_sum_is_prime(a,n,k,0,0)<<endl;
    int b[n] = {};
    list_the_combination(a,n,k,0,0,b);
    return 0;
}

