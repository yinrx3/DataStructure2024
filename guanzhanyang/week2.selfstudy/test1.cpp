#include <iostream>
using namespace std;
template <class T>
class VecList
{
    private:
    int capacity;//标注总长度
    int length;//标注有效长度
    T* arr;
    void doubleListSize()
    {
        T* oldArr=arr;
        arr=new T[2*capacity];
        capacity=2*capacity;
        for(int i=0;i<length;++i)
        {
            arr[i]=oldArr[i];
        }
        delete[] oldArr;
    }
    public:
    VecList()
    {
        length=0;
        capacity=100;
        arr=new T[capacity];
    }
    VecList(T* a,int n)
    {
        length=n;
        capacity=100+2*n;
        arr=new T[capacity];
        for(int i=0;i<n;++i)
        {
            arr[i]=a[i];
        }
    }
    ~VecList()
    {
        delete[] arr;
    }
    int getlength()
    {
        return length;
    }
    bool isEmpty()
    {
        return length==0;
    }
    void insertEleAtPos(int i,T x)
    {
        if(length==capacity)
        {
            doubleListSize();
        }
        if(i>length||i<0)
        {
            throw "insertEleAtPos: Illegal position!";
        }
        for(int j=length;j>i;--j)
        {
            arr[j]=arr[j-1];
        }
        arr[i]=x;
        length++;
    }
    T deleteEleAtPos(int i)
    {
        if(i>=length||i<0)
        {
            throw "deleteEleAtPos: Illegal position";
        }
        T temp=arr[i];
        for(int j=i;j<length-1;++j)
        {
            arr[j]=arr[j+1];
        }
        --length;
        return temp;
    }
    void setEleAtPos(int i,T x)
    {
        if(i<0||i>=length)
        {
            throw "setEleAtPos: Illegal position";
        }
        arr[i]=x;
    }
    T getEleAtPos(int i)
    {
        if(i<0||i>=length)
        {
            throw "getEleAtPos: Illegal position";
        }
        return arr[i];
    }
    void reverseEleAtPos(int i,int j)
    {
        if(i<0||i>=length)
        {
            throw "reverseEleAtPos(i): Illegal position";
        }
        if(j<0||j>=length)
        {
            throw "reverseEleAtPos(j): Illegal position";
        }
        T temp=arr[j];
        arr[j]=arr[i];
        arr[i]=temp;
    }
    int locateEle(T x)
    {
        for(int i=0;i<length;++i)
        {
            if(arr[i]==x)
            {
                return i;
            }
        }
        return -1;
    }
    void printList()
    {
        for(int i=0;i<length;++i)
        {
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};
class IntPolynomial{
    private:
    int effective;
    int total;
    VecList<int> coefficient;
    VecList<int> power;
    public:
    IntPolynomial():effective(0),total(100),coefficient(),power(){};
    IntPolynomial(int* c,int* d,int n):effective(n),total(100+2*n),coefficient(c,n),power(d,n){};
    //上面是两个构造函数，对于其中两个VecList都使用了上面已经定义好的类进行初始化
    ~IntPolynomial(){}//这里会自动调用VecList的初始化函数
    int getDegree(){
        if(effective==0)
        {
            return -1;
        }
        int maxDegree=power.getEleAtPos(0);//首先假设第一个元素是最大的
        for(int i=1;i<effective;++i)
        {
            if(maxDegree<power.getEleAtPos(i))
            {
                maxDegree=power.getEleAtPos(i);
            }
        }
        return maxDegree;
    }
    //下面定义一个辅助函数，专门用来合并同类项
    IntPolynomial* CombinedPoly()
{
    // 冒泡排序，对幂次进行升序排序
    for (int i = 0; i < effective - 1; ++i)
    {
        for (int j = i + 1; j < effective; ++j)
        {
            if (power.getEleAtPos(i) > power.getEleAtPos(j))
            {
                // 交换系数和幂次
                int tempCoeff = coefficient.getEleAtPos(i);
                int tempPower = power.getEleAtPos(i);
                coefficient.setEleAtPos(i, coefficient.getEleAtPos(j));
                power.setEleAtPos(i, power.getEleAtPos(j));
                coefficient.setEleAtPos(j, tempCoeff);
                power.setEleAtPos(j, tempPower);
            }
        }
    }

    // 合并具有相同幂次的项
    int i = 0;
    while (i < effective - 1)
    {
        int j = i + 1;
        while (j < effective)
        {
            if (power.getEleAtPos(i) == power.getEleAtPos(j))
            {
                int newCoeff = coefficient.getEleAtPos(i) + coefficient.getEleAtPos(j);
                if (newCoeff != 0)
                {
                    coefficient.setEleAtPos(i, newCoeff);
                }
                else
                {
                    // 如果合并后的系数为0，则删除第i项和第j项
                    coefficient.deleteEleAtPos(i);
                    power.deleteEleAtPos(i);
                    --effective;
                    // 删除第j项
                    coefficient.deleteEleAtPos(j - 1);
                    power.deleteEleAtPos(j - 1);
                    --effective;
                    // 调整索引
                    --i;
                    break;
                }
                // 删除第j项
                coefficient.deleteEleAtPos(j);
                power.deleteEleAtPos(j);
                --effective;
            }
            else
            {
                ++j;
            }
        }
        ++i;
    }

    return this;
}
    IntPolynomial* Add(IntPolynomial* b) 
    {
        int nowEffective=this->effective+b->effective;
        int* CombinedCoeff=new int[nowEffective];
        int* CombinedPower=new int[nowEffective];
        //下面依次将要处理的两个多项式相关内容写到“处理连接多项式”里面
        for(int i=0;i<this->effective;++i)//先写本矩阵
        {
            CombinedCoeff[i]=this->coefficient.getEleAtPos(i);
            CombinedPower[i]=this->power.getEleAtPos(i);
        }
        for(int i=0;i<b->effective;++i)//再写入传入进去的矩阵
        {
            CombinedCoeff[this->effective+i]=b->coefficient.getEleAtPos(i);
            CombinedPower[this->effective+i]=b->power.getEleAtPos(i);
        }
        //下面正式创建“处理连接多项式”
        IntPolynomial* result=new IntPolynomial(CombinedCoeff,CombinedPower,nowEffective);
        result->CombinedPoly();
        delete[] CombinedCoeff;
        delete[] CombinedPower;
        return result;
    }
    void printPolynomial() 
    {
        if(effective==0)
        {
            cout<<0<<endl;
        }
        for(int i=0;i<effective;++i)
        {
            int coefficient=this->coefficient.getEleAtPos(i);
            int power=this->power.getEleAtPos(i);
            if(i==0)
            {
                
            }
            else
            {

            }
        }   
        cout<<endl;
    }

};


void test2(){
    int p1c[8] = {2,-6,-6,2,6, 6,-2,1};
    int p1d[8] = {0, 1,4,8, 1,  4,8, 10};
    IntPolynomial p1(p1c,p1d,8);
    p1.CombinedPoly()->printPolynomial();
}
int main()
{
    test2();
    return 0;
}