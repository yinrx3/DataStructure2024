#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

bool ifPalindrome(string s);
void makePalindrome(string s);

void makePalindrome(string s){
    int length=s.length();
    for(int i=0;i<length;++i)
    {
        string childstr=s.substr(i,length-i);
        if(i==0&&ifPalindrome(childstr))
        {
            cout<<s<<endl;
            break;
        }
        if(ifPalindrome(childstr))
        {
            cout<<s;
            for(int j=i-1;j>=0;--j)
            {
                cout<<s[j];
            }
            cout<<endl;
            break;
        }
    }
}

bool ifPalindrome(string s){
    int length=s.length();
    for(int i=0;i<length/2;++i)
    {
        if(s[i]!=s[length-1-i])
        {
            return false;
        }
    }
    return true;
}
/* UPLOAD END */

int main(){
    string x;
    cin >> x;
   
            makePalindrome(x);
            
    return 0;
}