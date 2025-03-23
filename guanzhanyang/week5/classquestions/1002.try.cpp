#include <iostream>
#include <string>


using namespace std;


int* getNext(string T);
int KMP(string S, string T);
int simplePatternMatch(string s, string p);
int* getNext(string T)
{
    int L = T.length();
    int* next = new int[L];
	if(L==0) return next;
    next[0] = -1;
	if(L==1) return next;
    next[1] = 0;
    for(int i=2;i<L;i++)
    {
        // calculate next[i]
        int k = next[i-1];
        while(k!=-1 && T[k]!=T[i-1])
        {
            k = next[k];
        }
        next[i] = k+1;
    }
    return next;
}

int KMP(string S, string T)
{
    int i=0,j=0;
    int* next = getNext(T);
	int sLen = S.length();
	int tLen = T.length();
    while(i<sLen && j<tLen)
    {
        if(j==-1||S[i]==T[j])
        {
            i++;
            j++;
        }
        else{
            j = next[j];
        }
    }
    if(j==tLen)
    {
        return i-j;
    }
    else
    {
        return -1;
    }
}

int simplePatternMatch(string s, string p) {
    int slength=s.length();
    int plength=p.length();//p是模式串
    if(p=="*")
        return 0;
    int nstar=0;
    for(int i=0;i<plength;++i)
    {
        if(p[i]=='*')
            ++nstar;
    }
    if(nstar==0)
    {
        return KMP(s,  p);
    }
    int nchild=nstar+1;
    string* diff=new string[nchild];
    //下面将分割开来的各个模式串复制进去
    int fuzhi=0;//记录已经复制的个数
    int i=0,j=1;
    while(fuzhi<nchild)
    {
        if(p[j]=='*'||j>=plength)
        {
            diff[fuzhi]=p.substr(i,j-i);
            fuzhi++;
            i=j+1;
            j=i+1;
        }
        else
        {
            ++j;
        }
    }
    //这里已经全部复制完，下面与主串比较
    string copys=s;
    int result=KMP(s,diff[0]);
    for(int i=0;i<nchild;++i)
    {
        if(KMP(copys,diff[i])==-1)
        {
            return -1;
        }
        else
        {
            //在copys中匹配到的位置
            int a=KMP(copys,diff[i]);
            //匹配到的尾元素位置
            int b=a+diff[i].length();
            //截断后copys开始的位序
            int c=b+1;
            //剩下的元素个数
            int numleft=copys.length()-c;
            copys=copys.substr(c-1,numleft+1);
        }
    }
    delete[] diff;
    return result;
}


int main() {
    int x;
    std::cin >> x; 
    std::string s1 = "accdabbca";
    switch (x) {
        case 1:
            std::cout << simplePatternMatch(s1, "abb") << std::endl;
            std::cout << simplePatternMatch(s1, "cda") << std::endl;
            std::cout << simplePatternMatch(s1, "ccdb") << std::endl;
            break;
        case 2:
            std::cout << simplePatternMatch(s1, "aa*ab") << std::endl;
            std::cout << simplePatternMatch(s1, "ad*ab") << std::endl;
            std::cout << simplePatternMatch(s1, "aa*d") << std::endl;
            break;
        case 3:
            std::cout << simplePatternMatch(s1, "e*ac*da") << std::endl;
            std::cout << simplePatternMatch(s1, "ac*cb*a") << std::endl;
            std::cout << simplePatternMatch(s1, "ac*cd*ca") << std::endl;
            break;
        case 4:
            std::cout << simplePatternMatch(s1, "c**a") << std::endl;
            std::cout << simplePatternMatch(s1, "ac**b*a") << std::endl;
            std::cout << simplePatternMatch(s1, "ac*cd*c") << std::endl;
            break;
        default:
            break;
    }
    return 0;
}