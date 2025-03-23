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
    //下面的这个获得最高次项的成员函数，不需要考虑伪0情况，伪0情况我们另外考虑
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
    //这里的测试程序输入的系数全都不含0，唯一需要考虑的就是合并同类项时同幂次相加是0
    //可以增加考虑，如果输入的系数是0但是相关幂次不是0，就需要再写一个辅助函数，专门来处理伪0项的情况
    //我们可以对刚刚输入的多项式就进行删除伪0操作，因此后续考虑输出多项式只需要考虑系数全都不为0的情况
    //现在编写辅助函数，用来合并同类项
    IntPolynomial* CombinedPoly()
    {
        for(int i=0;i<effective-1;++i)
        {
            for(int j=i+1;j<effective;++j)
            {
                if(power.getEleAtPos(i)>power.getEleAtPos(j))
                {
                    //交换系数和幂次
                    int tempCoeff=coefficient.getEleAtPos(i);
                    int tempPower=power.getEleAtPos(i);
                    coefficient.setEleAtPos(i,coefficient.getEleAtPos(j));
                    power.setEleAtPos(i,power.getEleAtPos(j));
                    coefficient.setEleAtPos(j,tempCoeff);
                    power.setEleAtPos(j,tempPower);
                }
            }
        }
        //下面合并具有相同幂次的项
        int i=0;
        while(i<effective-1)
        {
            int j=i+1;
            while(j<effective)
            {
                if(power.getEleAtPos(i)==power.getEleAtPos(j))
                {
                    int newCoeff=coefficient.getEleAtPos(i)+coefficient.getEleAtPos(j);
                    if(newCoeff!=0)
                    {
                        coefficient.setEleAtPos(i,newCoeff);
                    }
                    else
                    {
                        //合并后的系数为0，两项都需要删去，先删i再删j
                        coefficient.deleteEleAtPos(i);
                        power.deleteEleAtPos(i);
                        --effective;
                        //下面删除j
                        coefficient.deleteEleAtPos(j-1);
                        power.deleteEleAtPos(j-1);
                        --effective;
                        //由于删去的原因需要调整索引
                        --i;
                        break;
                    }
                    //这个是接着if里面的
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
    //下面是加法函数
    IntPolynomial* Add(IntPolynomial* b)
    {
        int nowEffective=this->effective+b->effective;
        int* CombinedCoeff=new int[nowEffective];
        int* CombinedPower=new int[nowEffective];
        //下面写入连接数组，先写入this
        for(int i=0;i<this->effective;++i)
        {
            CombinedCoeff[i]=this->coefficient.getEleAtPos(i);
            CombinedPower[i]=this->power.getEleAtPos(i);
        }
        for(int j=0;j<b->effective;++j)
        {
            CombinedCoeff[this->effective+j]=b->coefficient.getEleAtPos(j);
            CombinedPower[this->effective+j]=b->power.getEleAtPos(j);
        }
        IntPolynomial* AddResult=new IntPolynomial(CombinedCoeff,CombinedPower,nowEffective);
        delete[] CombinedCoeff;
        delete[] CombinedPower;
        return AddResult->CombinedPoly();
    }
    //下面是减法函数
    IntPolynomial* Subtract(IntPolynomial* b)
    {
        int nowEffective=this->effective+b->effective;
        int* CombinedCoeff=new int[nowEffective];
        int* CombinedPower=new int[nowEffective];
        //下面写入连接数组，先写入this
        for(int i=0;i<this->effective;++i)
        {
            CombinedCoeff[i]=this->coefficient.getEleAtPos(i);
            CombinedPower[i]=this->power.getEleAtPos(i);
        }
        for(int j=0;j<b->effective;++j)
        {
            CombinedCoeff[this->effective+j]=(-1)*b->coefficient.getEleAtPos(j);
            CombinedPower[this->effective+j]=b->power.getEleAtPos(j);
        }
        IntPolynomial* SubtractResult=new IntPolynomial(CombinedCoeff,CombinedPower,nowEffective);
        delete[] CombinedCoeff;
        delete[] CombinedPower;
        return SubtractResult->CombinedPoly();
    }
    //下面是乘法函数
    IntPolynomial* Multiply(IntPolynomial* b)
    {
        int nowEffective=this->effective*b->effective;
        int* CombinedCoeff=new int[nowEffective];
        int* CombinedPower=new int[nowEffective];
        for(int i=0;i<this->effective;++i)
        {
            for(int j=0;j<b->effective;++j)
            {
                CombinedCoeff[i*b->effective+j]=this->coefficient.getEleAtPos(i)*b->coefficient.getEleAtPos(j);
                CombinedPower[i*b->effective+j]=this->power.getEleAtPos(i)+b->power.getEleAtPos(j);
            }
        }
        IntPolynomial* MultiplyResult=new IntPolynomial(CombinedCoeff,CombinedPower,nowEffective);
        delete[] CombinedCoeff;
        delete[] CombinedPower;
        return MultiplyResult->CombinedPoly();
    }
    void printPolynomial() 
    {
        if(effective==0)
        {
            cout<<0<<endl;
        }
        else{
        for(int i=0;i<effective;++i)
        {
            int coefficient=this->coefficient.getEleAtPos(i);
            int power=this->power.getEleAtPos(i);
            if(i==0)//分开处理首项和后续项系数
            {
                if(power==0)
                {
                    cout<<coefficient;
                }
                if(power>0)
                {
                    if(coefficient>0)
                    {
                        if(coefficient==1)
                        {
                            cout<<"x";
                        }
                        else
                        {
                            cout<<coefficient<<"x";
                        }
                    }
                    if(coefficient<0)
                    {
                        if(coefficient==-1)
                        {
                            cout<<"-x";
                        }
                        else
                        {
                            cout<<coefficient<<"x";
                        }
                    }
                }
                if(power>1)
                {
                    cout<<"^"<<power;
                }
            }
            if(i>0)
            {
                if(coefficient>0)
                {
                    if(coefficient==1)
                    {
                        cout<<"+x";
                    }
                    else
                    {
                        cout<<"+"<<coefficient<<"x";
                    }
                }
                if(coefficient<0)
                {
                    if(coefficient==-1)
                    {
                        cout<<"-x";
                    }
                    else
                    {
                        cout<<coefficient<<"x";
                    }
                }
                if(power!=1)
                {
                    cout<<"^"<<power;
                }
            }
        }
        cout<<endl; 
        }
    }
};

void test1(){    
    int p4c[5] = {-1,-5,6,1,-1};
    int p4d[5] = {0,3,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    p4.printPolynomial();
}

void test2(){
    int p1c[3] = {3,5,-6};
    int p1d[3] = {0,1,4};
    IntPolynomial p1(p1c,p1d,3);
    
    int p4c[5] = {-3,-5,6,1,-1};
    int p4d[5] = {1,3,7,9,11};
    IntPolynomial p4(p4c,p4d,5);
    
    p1.Add(&p4)->printPolynomial();
    p4.Subtract(&p1)->printPolynomial();
    
    p4.Add(&p4)->printPolynomial();
    p4.Subtract(&p4)->printPolynomial();
}

void test3(){
    int p1c[0] = {};
    int p1d[0] = {};
    IntPolynomial p1(p1c,p1d,0);
    
    int p2c[4] = {1,1,6,10};
    int p2d[4] = {0,3,20,40};
    IntPolynomial p2(p2c,p2d,4);
    
    p1.Multiply(&p2)->printPolynomial();
}

int main(){
    test1();
    return 0;
}
