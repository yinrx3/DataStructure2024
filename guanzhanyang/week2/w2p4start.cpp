#include <iostream>
using namespace std;
template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + n*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

class IntPolynomial{
    private:
        int total;
        int effective;
        VecList<int> coefficient;
        VecList<int> power;
    public:
        IntPolynomial():coefficient(),power(){
            effective=0;
            total=100;
        }
        IntPolynomial(int * c, int * d, int n)
        :effective(n),total(100+n*n),coefficient(c,n),power(d,n)
        {}
        ~IntPolynomial(){}
IntPolynomial* CombinedPoly(IntPolynomial* well)
    {
        //处理合并起来的数组，+直接两端顺序表叠加，-将后端乘负一相加，*用ij两轮循环得到没有经过合并同类项的叠加顺序表
        //先用bubble sort对power进行排序，将幂次从小到大，方便后续处理
        for(int i=0;i<well->effective-1;++i)
        {
            for(int j=i+1;j<well->effective;++j)
            {
                if(well->power.getEleAtPos(i)>well->power.getEleAtPos(j))
                {
                    // 交换系数和幂
                    int tempCoeff=well->coefficient.getEleAtPos(i);
                    int tempPower=well->power.getEleAtPos(i);
                    well->coefficient.setEleAtPos(i,well->coefficient.getEleAtPos(j));
                    well->power.setEleAtPos(i,well->power.getEleAtPos(j));
                    well->coefficient.setEleAtPos(j,tempCoeff);
                    well->power.setEleAtPos(j,tempPower);
                }
            }
        }
        //现在交换完了之后，这里合并的well中的power顺序表一定是升序
        //下面合并具有相同幂次的项目
        for(int i=0;i<well->effective-1;++i)
        {
            for(int j=0;j<well->effective;++j)
            {
                if(well->power.getEleAtPos(i)==well->power.getEleAtPos(j))
                {
                    int newCoeff=well->power.getEleAtPos(i)+well->power.getEleAtPos(j);
                    if(newCoeff!=0)
                    {
                        well->coefficient.setEleAtPos(i,newCoeff);
                    }
                    else
                    {
                        well->coefficient.deleteEleAtPos(i);
                        well->power.deleteEleAtPos(i);
                        --well->effective;
                        //这里不需要增加i的值，直接跳出循环，检查新的i。有点问题在这里?
                        continue;
                    }
                    well->coefficient.deleteEleAtPos(j);
                    well->power.deleteEleAtPos(j);
                    --well->effective;
                }
                else
                {
                    ++j;
                }
            }
        }
        return well;
    }


     int getDegree() {
    if (effective == 0) {
        return -1; // 如果没有有效项，返回 -1
    }

    int maxDegree = power.getEleAtPos(0); // 假设第一个元素是最大的幂

    for (int i = 1; i < effective; ++i) {
        int currentDegree = power.getEleAtPos(i);
        if (currentDegree > maxDegree) {
            maxDegree = currentDegree; // 更新最大幂
        }
    }

    return maxDegree;
}



IntPolynomial* Add(IntPolynomial* b) {
    int nownumber = this->effective + b->effective;
    int* combinedCoeff = new int[nownumber];
    int* combinedPower = new int[nownumber];

    // 复制当前多项式的系数和幂次
    for (int i = 0; i < this->effective; ++i) {
        combinedCoeff[i] = this->coefficient.getEleAtPos(i);
        combinedPower[i] = this->power.getEleAtPos(i);
    }

    // 复制参数多项式的系数和幂次
    for (int i = 0; i < b->effective; ++i) {
        combinedCoeff[this->effective + i] = b->coefficient.getEleAtPos(i);
        combinedPower[this->effective + i] = b->power.getEleAtPos(i);
    }

    // 创建新的多项式
    IntPolynomial* result = new IntPolynomial(combinedCoeff, combinedPower, nownumber);
    result->CombinedPoly(result);

    delete[] combinedCoeff;
    delete[] combinedPower;
    
    return result;
}
        IntPolynomial* Subtract(IntPolynomial* b) {
    int nownumber = this->effective + b->effective;
    int* combinedCoeff = new int[nownumber];
    int* combinedPower = new int[nownumber];

    // 复制当前多项式的系数和幂次
    for (int i = 0; i < this->effective; ++i) {
        combinedCoeff[i] = this->coefficient.getEleAtPos(i);
        combinedPower[i] = this->power.getEleAtPos(i);
    }

    // 复制参数多项式的系数和幂次，并取负
    for (int i = 0; i < b->effective; ++i) {
        combinedCoeff[this->effective + i] = -b->coefficient.getEleAtPos(i);
        combinedPower[this->effective + i] = b->power.getEleAtPos(i);
    }

    // 创建新的多项式
    IntPolynomial* result = new IntPolynomial(combinedCoeff, combinedPower, nownumber);
    result->CombinedPoly(result);

    delete[] combinedCoeff;
    delete[] combinedPower;
    return result;
}




IntPolynomial* Multiply(IntPolynomial* b) {
    int nownumber = this->effective * b->effective;
    int* combinedCoeff = new int[nownumber];
    int* combinedPower = new int[nownumber];

    // 初始化临时数组
    for (int i = 0; i < nownumber; ++i) {
        combinedCoeff[i] = 0;
        combinedPower[i] = 0;
    }

    // 计算乘积
    int index = 0;
    for (int i = 0; i < this->effective; ++i) {
        for (int j = 0; j < b->effective; ++j) {
            combinedCoeff[index] = this->coefficient.getEleAtPos(i) * b->coefficient.getEleAtPos(j);
            combinedPower[index] = this->power.getEleAtPos(i) + b->power.getEleAtPos(j);
            ++index;
        }
    }

    // 合并同类项
    int* finalCoeff = new int[nownumber];
    int* finalPower = new int[nownumber];
    int finalSize = 0;

    for (int i = 0; i < nownumber; ++i) {
        bool merged = false;
        for (int k = 0; k < finalSize; ++k) {
            if (finalPower[k] == combinedPower[i]) {
                finalCoeff[k] += combinedCoeff[i];
                merged = true;
                break;
            }
        }
        if (!merged) {
            finalCoeff[finalSize] = combinedCoeff[i];
            finalPower[finalSize] = combinedPower[i];
            ++finalSize;
        }
    }

    // 对结果按幂次进行排序
    for (int i = 0; i < finalSize - 1; ++i) {
        for (int j = i + 1; j < finalSize; ++j) {
            if (finalPower[i] > finalPower[j]) {
                std::swap(finalPower[i], finalPower[j]);
                std::swap(finalCoeff[i], finalCoeff[j]);
            }
        }
    }

    // 创建结果多项式
    IntPolynomial* result = new IntPolynomial(finalCoeff, finalPower, finalSize);

    // 清理内存
    delete[] combinedCoeff;
    delete[] combinedPower;
    delete[] finalCoeff;
    delete[] finalPower;

    return result;
}
    void printPolynomial() {
        if(effective==0)
        {
            cout<<0<<endl;
        }
        for(int i=0;i<effective;++i)
        {
            int coefficient=this->coefficient.getEleAtPos(i);
            int power=this->power.getEleAtPos(i);
            if(i==0)//分开处理首项和后续项系数
            {
                if(coefficient==0)
                {
                    continue;//首项系数为0直接不输出就好，跳出当前判断
                }
                if(coefficient!=0)
                {
                    cout<<coefficient;
                    if(power==1)
                    {
                        cout<<"x";
                    }
                    else if(power==0){}
                    else
                    {
                        cout<<"x^"<<power;
                    }
                }
            }
            if(i>0)
            {
                if(coefficient==0)
                {
                    continue;
                }
                if(coefficient!=0)
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
                    if(power==1)
                    {
                        continue;
                    }
                    if(power!=1)
                    {
                        cout<<"^"<<power;
                    }
                }
            }
        }
        cout<<endl;
    }
};



/* UPLOAD END */

void test1(){    
    int p4c[5] = {-3,-5,6,1,-1};
    int p4d[5] = {1,3,7,9,11};
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
    int p1c[3] = {1,-1,5};
    int p1d[3] = {0,3,7};
    IntPolynomial p1(p1c,p1d,3);
    
    int p2c[4] = {1,1,6,10};
    int p2d[4] = {0,3,20,40};
    IntPolynomial p2(p2c,p2d,4);
    
    p1.Multiply(&p2)->printPolynomial();
}

int main(){
    test1();
    test2();
    test3();
    return 0;
}