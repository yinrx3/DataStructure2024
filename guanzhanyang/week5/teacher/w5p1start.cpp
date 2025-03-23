#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

void makePalindrome(string s){
    
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    switch(x){
        case 1:
            makePalindrome("A");
            makePalindrome("ABA");
            // break;
        case 2:
            makePalindrome("AB");
            makePalindrome("ABC");
            // break;
        case 3:
            makePalindrome("ABCB");
            makePalindrome("ABCC");
        default: ;
    }
    return 0;
}