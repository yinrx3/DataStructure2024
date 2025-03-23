#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* UPLOAD START */

int simplePatternMatch(string s, string p){
    
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    string s1 = "aaccdabbca";
    switch(x){
        case 1:
            cout << simplePatternMatch(s1,"abb") << endl;
            cout << simplePatternMatch(s1,"cda") << endl;
            cout << simplePatternMatch(s1,"ccdb") << endl;
            break;
        case 2:
            cout << simplePatternMatch(s1,"aa*ab") << endl;
            cout << simplePatternMatch(s1,"ad*ab") << endl;
            cout << simplePatternMatch(s1,"aa*d") << endl;
            break;
        case 3:
            cout << simplePatternMatch(s1,"e*ac*da") << endl;
            cout << simplePatternMatch(s1,"ac*cb*a") << endl;
            cout << simplePatternMatch(s1,"ac*cd*ca") << endl;
        default: ;
    }
    return 0;
}