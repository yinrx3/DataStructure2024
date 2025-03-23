#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int* getNext(string T){
    int L = T.length();
    int* next = new int[L];
	if(L==0) return next;
    next[0] = -1;
	if(L==1) return next;
    next[1] = 0;
    for(int i=2;i<L;i++){
        // calculate next[i]
        int k = next[i-1];
        while(k!=-1 && T[k]!=T[i-1]){
            k = next[k];
        }
        next[i] = k+1;
    }
    return next;
}

int KMP(string S, string T){
    int i=0,j=0;
    int* next = getNext(T);
	int sLen = S.length();
	int tLen = T.length();
    while(i<sLen && j<tLen){
        if(j==-1||S[i]==T[j]){
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(j==tLen){
        return i-j;
    }
    else{
        return -1;
    }
}

int main(){
    string longTxt, pTxt;
    cin >> longTxt >> pTxt;
    int* n = getNext(pTxt);
    cout << setw(5) << right << " ";
    for(int i=0;i<pTxt.length();i++){
        cout << setw(5) << right << pTxt[i];
    }
    cout << endl;
    cout << setw(5) << right << "Next:";
    for(int i=0;i<pTxt.length();i++){
        cout << setw(5) << right << n[i];
    }
    cout << endl << endl;
    cout << "String matched at position " << KMP(longTxt, pTxt) << endl;
    return 0;
}