#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/* UPLOAD START */

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


int simplePatternMatch(string s, string p){
    int slen=s.length();
    int plen=p.length();
    if(plen==0)
        return 0;
    bool isallstar=true;
    int numstar=0;
    for(int i=0;i<plen;++i)
    {
        if(p[i]!='*')
            isallstar=false;
        else
            ++numstar;
    }
    if(isallstar)
        return 0;
    if(numstar==0)
        return KMP(s,p);
    //以上是预备处理过程。处理了空串，全是*，没有*的情况
    //下面是非空串，且至少有一个*，至少有一个字符
    string copys=s;
    int i=0,j=0,result=-1;
    bool firstresult=true,setj=true;
    while(i<plen)
    {
        if(p[i]=='*')
        {
            ++i;
        }
        else
        {
            if(setj)
                j=i+1;
            if(p[j]=='*'||j>=plen)
            {
                string copyp=p.substr(i,j-i);
                int resultj=KMP(copys,copyp);
                if(firstresult==true)
                {
                    result=resultj;
                    firstresult=false;
                }
                if(resultj==-1)
                    return -1;
                copys=copys.substr(resultj+copyp.length(),copys.length()-resultj-copyp.length());
                if(j>=plen)
                    return result;
                else
                {
                    for(int k=j;k<plen;++k)
                    {
                        if(p[k]!='*')
                        {
                            i=k;
                            setj=true;
                            break;
                        }
                            
                    }
                }
                
            }
            else
            {
                ++j;
                setj=false;
            }
        }
    }
}

/* UPLOAD END */

int main(){
    int x;
    cin >> x;
    string s1 = "aaccdabbca";
    switch(x){
        case 1:
            cout << simplePatternMatch(s1,"a*************b********b****************************") << endl;
            cout << simplePatternMatch(s1,"c*da") << endl;
            cout << simplePatternMatch(s1,"********ccd******b*******") << endl;
            break;
        case 2:
            cout << simplePatternMatch(s1,"aa*ab") << endl;
            cout << simplePatternMatch(s1,"ad*ab") << endl;
            cout << simplePatternMatch(s1,"aa*d") << endl;
            break;
        case 3:
            cout << simplePatternMatch(s1,"e**ac*da*") << endl;
            cout << simplePatternMatch(s1,"ac******cb*a") << endl;
            cout << simplePatternMatch(s1,"*ac*cd*ca*") << endl;
        default: ;
    }
    return 0;
}