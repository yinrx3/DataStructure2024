#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


int simplePatternMatch(string s, string p) {
    int slen = s.length();
    int plen = p.length();
    string t;
    for (int i = 0; i < plen; ++i) {
        if (p[i] == '*') {
            if (t.empty() || t.back() != '*') {
                t += '*';
            }
        } else {
            t += p[i];
        }
    }//多个星号替换成单个星号

    int newp = t.length();
    for (int i = 0; i <= slen; ++i) {
        int k = i;
        int m = 0;
        bool matched = true;

        while (m < newp) {
            if (t[m] == '*') {
                m++;
                if (m == newp) {
                    return i;
                }
                while (k < slen && s[k] != t[m]) {
                    k++;
                }
                if (k == slen) {
                    matched = false;
                    break;
                }
            } else {
                if (k < slen && s[k] == t[m]) {
                    k++;
                    m++;
                } else {
                    matched = false;
                    break;
                }
            }
        }
        if (matched && m == newp) {
            return i;
        }
    }

    return -1;
}

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