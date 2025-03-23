#include <iostream>
using namespace std;
int main()
{
    int r;
    int sum=0;
    cin>>r;
    for(int i=(-1)*r;i<r+1;++i)
    {
        for(int j=(-1)*r;j<r+1;++j)
        {
            if(i*i+j*j<=r*r)
            {
                sum=sum+1;
            }
        }
    }
    cout<<sum;
    return 0;
}