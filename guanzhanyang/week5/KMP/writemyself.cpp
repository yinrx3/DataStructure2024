#include <iostream>
#include <string>
using namespace std;

int* getnext(string t)
{
    int tlen=t.length();
    int* next=new int[tlen];
    if(tlen==0)
    {
        return next;
    }
    next[0]=-1;
    if(tlen==1)
    {
        return next;
    }
    next[1]=0;
    for(int i=2;i<tlen;++i)
    {
        
    }
}


//以下是主程序
int KMP(string s, string t)
{
    int i=0,j=0;
    int* next=getnext(t);
    int slen=s.length();
    int tlen=t.length();
    //下面i和j分别代表在文本串和模式串中的位序
    while(i<slen&&j<tlen)
    {
        if(j==-1||s[i]==t[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j=next[j];
        }
    }
    if(j==tlen)
    {
        return i-j;
    }
    else
    {
        return 0;
    }
}