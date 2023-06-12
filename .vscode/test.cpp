#include<iostream>
using namespace std;


template <class InputIt, class T>
InputIt myfind(InputIt first, InputIt last, const T&value){
    for(InputIt it = first;it != last;it++){
        if (*it == value){
            return it;
        }
    }
         return last;
}

int main(){
    int a[3] = {1,2,3};
    int* e = myfind(begin(a),end(a),2);
    int index = distance(begin(a), e);
    cout << index;
}