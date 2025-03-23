#include <iostream>
#include <string>
using namespace std;

void getnext(string pattern,int* next)
{
    int plength=pattern.length();
    next[0]=0;//第一个位置的永远是0，因为没有前后缀
    for(int c=1;c<plength;++c)//这里c+1是copy子串元素的个数,这里c是当前处理子串的末尾元素位序
    {
        string copy=pattern.substr(0,c+1);
        
            
        
    }
}


int main()
{
    string pattern;
    cin>>pattern;
    int length=pattern.length();
    int* next=new int[length];
    getnext(pattern,next);


    delete[] next;
    return 0;
}