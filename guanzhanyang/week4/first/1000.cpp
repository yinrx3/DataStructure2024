#include <iostream>
using namespace std;

/* UPLOAD START */

template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize()
        {
            T* oldArr=arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++)
            {
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
            capacity = 100 + 2*n;
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
        bool isEmpty()
        {
            return length==0;
        }
        void insertEleAtPos(int i, T x)
        {
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i)
        {
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x)
        {
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        void changeEleAtPos(int i,int j)
        {
            T x;
            x=arr[i];
            arr[i]=arr[j];
            arr[j]=x;
        }
        T getEleAtPos(int i)
        {
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x)
        {
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList()
        {
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

template<class T>
struct Triple
{
    int irow;
    int icol;
    T val;
};

// In the class below, we assume it is meaningful to put 0 as a value for the type T.
template <class T>
class SparseMatrix{
    private:
        VecList<Triple<T>> matrix;
        int row;
        int col;
    public:
        SparseMatrix(){
            // default is 10 rows, 10 columns
            row=10;
            col=10;
        }
        SparseMatrix(int r, int c){
            row=r;
            col=c;
        }
        ~SparseMatrix(){}

        void setEntry(int rPos, int cPos, T x){
            Triple<T> data;
            data.irow=rPos;
            data.icol=cPos;
            data.val=x;

            bool found=false;//判断原来的存储表里面是否有相同位序的
            for(int i=0;i<matrix.getLength();++i)
            {
                Triple<T> compare=matrix.getEleAtPos(i);
                if(compare.icol==cPos&&compare.irow==rPos)
                {
                    if(x!=0)
                    {
                        matrix.setEleAtPos(i,data);
                        found=true;
                        break;
                    }
                    else
                    {
                        matrix.deleteEleAtPos(i);
                    }
                    
                }
            }
            if(!found)
            {
                if(x==0){}
                else
                {
                    matrix.insertEleAtPos(matrix.getLength(),data);//直接插入到表尾，这样节省复杂度
                }
                
            }
        }

        T getEntry(int rPos, int cPos){
            bool found=false;//检查要查找的是不是稀疏元素
            for(int i=0;i<matrix.getLength();++i)
            {
                Triple<T> compare=matrix.getEleAtPos(i);
                if(compare.icol==cPos&&compare.irow==rPos)
                {
                    found=true;
                    return compare.val;
                }
            }
            if(!found)
            {
                return 0;
            }
        }

        SparseMatrix<T>* combineVecList()
        {
            int i=0;
            while(i<this->matrix.getLength())
            {
                Triple<T> pi=this->matrix.getEleAtPos(i);
                int j=i+1;
                bool deletedpi=false;//标记是否已经删除pi
                while(j<this->matrix.getLength())
                {
                    Triple<T> pj=this->matrix.getEleAtPos(j);
                    if(pi.icol==pj.icol&&pi.irow==pj.irow)
                    {
                        if(pi.val+pj.val!=0)
                        {
                            pi.val+=pj.val;
                            this->matrix.setEleAtPos(i,pi);
                            this->matrix.deleteEleAtPos(j);
                        }
                        else
                        {
                            
                            deletedpi=true;
                            this->matrix.deleteEleAtPos(j);
                            this->matrix.deleteEleAtPos(i);
                            break;
                        }

                    }
                    else{
                        j++;
                    }
                }
                if(deletedpi)
                {
                    i--;
                }
                i++;
            }
            return this;
        }


        SparseMatrix<T> * add(SparseMatrix<T> * B){
            if(this->row!=B->row||this->col!=B->col)
            {
                throw"Matrices have incompatible sizes";
            }
            else
            {
                SparseMatrix<T>* result=new SparseMatrix<T>();
                result->col=B->col;
                result->row=B->row;
                for(int i=0;i<this->matrix.getLength();++i)
                {
                    Triple<T> cur=this->matrix.getEleAtPos(i);
                    result->matrix.insertEleAtPos(result->matrix.getLength(),cur);
                }
                for(int j=0;j<B->matrix.getLength();++j)
                {
                    Triple<T> cur=B->matrix.getEleAtPos(j);
                    result->matrix.insertEleAtPos(result->matrix.getLength(),cur);
                }
                result->combineVecList();
                return result;
            }
        }
        SparseMatrix<T> * subtract(SparseMatrix<T> * B)
        {
            if(this->row!=B->row||this->col!=B->col)
            {
                throw"Matrices have incompatible sizes";
            }
            else
            {
                SparseMatrix<T>* result=new SparseMatrix<T>();
                result->col=B->col;
                result->row=B->row;
                for(int i=0;i<this->matrix.getLength();++i)
                {
                    Triple<T> cur=this->matrix.getEleAtPos(i);
                    result->matrix.insertEleAtPos(result->matrix.getLength(),cur);
                }
                for(int j=0;j<B->matrix.getLength();++j)
                {
                    Triple<T> cur=B->matrix.getEleAtPos(j);
                    cur.val=(-1)*cur.val;
                    result->matrix.insertEleAtPos(result->matrix.getLength(),cur);
                }
                return result->combineVecList();
            }
        }
        
        SparseMatrix<T> * multiply(SparseMatrix<T> * B){
            //perform multiplication if the sizes of the matrices are compatible.
            if(this->col!=B->row)
            {
                throw"Matrices have incompatible sizes";
            }
            else
            {
                SparseMatrix<T>* result=new SparseMatrix<T>();
                result->col=B->col;
                result->row=this->row;
                for(int i=0;i<this->matrix.getLength();++i)
                {
                    for(int j=0;j<B->matrix.getLength();++j)
                    {
                        Triple<T> cpi=this->matrix.getEleAtPos(i);
                        Triple<T> cpj=B->matrix.getEleAtPos(j);
                        if(cpi.icol==cpj.irow)
                        {
                            Triple<T> resuij;
                            resuij.irow=cpi.irow;
                            resuij.icol=cpj.icol;
                            resuij.val=cpi.val*cpj.val;
                            result->matrix.insertEleAtPos(result->matrix.getLength(),resuij);
                        }
                    }
                }
                return result->combineVecList();
            }

        }

SparseMatrix<T>* sortMatrix() {
    int length = this->matrix.getLength();
    
    // 冒泡排序
    for (int i = 0; i < length - 1; ++i) {
        for (int j = 0; j < length - 1 - i; ++j) {
            Triple<T> current = this->matrix.getEleAtPos(j);
            Triple<T> next = this->matrix.getEleAtPos(j + 1);

            // 按先行后列的顺序进行比较
            if ((next.irow < current.irow) || 
                (next.irow == current.irow && next.icol < current.icol)) {
                // 交换元素的位置
                this->matrix.changeEleAtPos(j, j + 1); // 假设这是正确的交换逻辑
            }
        }
    }
    
    return this;
}
        
        // Only call this function if you know the size of matrix is reasonable.
        void printMatrix(){
            for(int i=0;i<this->row;++i)
            {
                for(int j=0;j<this->col;++j)
                {
                    cout<<this->getEntry(i,j)<<" ";
                }
                cout<<endl;
            }
        }
        
        //This is for printing only non-zero entries
        void printNZMatrix(){
            this->sortMatrix();
            for(int i=0;i<this->matrix.getLength();++i)
            {
                Triple<T> screen=this->matrix.getEleAtPos(i);
                cout<<screen.irow<<" "<<screen.icol<<" "<<screen.val<<endl;
            }
        }
};

/* UPLOAD END */

int main(){
    SparseMatrix<int> X, Y;
    X.setEntry(1,3,4);
    X.setEntry(7,8,2);
    X.setEntry(3,3,6);
    Y.setEntry(1,6,4);
    Y.setEntry(1,3,4);
    Y.setEntry(7,7,2);
    Y.setEntry(3,1,5);
    Y.setEntry(3,3,6);
    X.printMatrix();
    cout << endl;
    Y.printMatrix();
    cout << endl;
    Y.printNZMatrix();
    cout << endl;
    X.add(&Y)->printMatrix();
    cout << endl;
    X.subtract(&Y)->printMatrix();
    cout << endl;
    Y.multiply(&X)->printMatrix();
    return 0;
}
