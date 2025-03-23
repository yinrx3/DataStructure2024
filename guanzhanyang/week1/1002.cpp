#include <iostream>
using namespace std;
int main()
{
    int l;
    cin>>l;
    if(2%l!=0)
    {
        cout<<2<<endl;
    }
    for(int i=3;i<1001;++i)
    {
        int cnt=0;
        for(int j=2;j<i;++j)
        {
            if(i%j==0)
            {
                cnt+=1;
            }
        }
        int sumofi=0;
        int x=i;
        while(x!=0)
        {
            int b;
            b=x%10;
            sumofi+=b;
            x=x/10;
        }
        if(cnt==0&&sumofi%l!=0)
        {
            cout<<i<<endl;
        }
    }
}