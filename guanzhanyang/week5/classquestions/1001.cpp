#include <iostream>
#include <string>
using namespace std;
int main()
{
    string S;
    cin>>S;
    int Slength=S.length();
    for(int i=0;i<Slength;++i)
    {
        bool full=false;
        string T;
        T=S.substr(0,i+1);
        int Tlength=T.length();
        int multiple=Slength/Tlength+1;
        string copyT;//验证是否是生成最小前缀
        for(int j=0;j<multiple;++j)
        {
            copyT+=T;
            if(copyT==S)
            {
                full=true;
                cout<<Tlength<<endl;
                cout<<T<<endl;
            }
        }
        if(full)
        {
            break;
        }
    }
    return 0;
}
