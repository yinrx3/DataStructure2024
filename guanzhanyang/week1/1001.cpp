#include <iostream>
using namespace std;
int main()
{
    int sum=0;
    for(int i=0;i>-1;++i)
    {
        int a=0;
        cin>>a;
        sum+=a;
        if(a==0)
        {
            break;
        }
    }
    cout<<sum<<endl;
    return 0;
}