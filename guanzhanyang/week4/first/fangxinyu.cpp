#include <iostream>
using namespace std;

/* UPLOAD START */

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

// In the class below, we assume it is meaningful to put 0 as a value for the type T.
template <class T>
class SparseMatrix{
    private:
        int rows;
        int cols;
        VecList<T> values;
        VecList<int> rowIndex;
        VecList<int> colIndex;
    public:
        SparseMatrix(){
            // default is 10 rows, 10 columns
            rows = 10;
            cols = 10;
        }
        SparseMatrix(int r, int c){
            rows = r;
            cols = c;
        }
        ~SparseMatrix(){
            //No need to delete the elements in private.
        }
        void setEntry(int rPos, int cPos, T x){
            if(rPos > rows || rPos < 0 || cPos > cols || cPos < 0){
                throw runtime_error("Index out of bounds");
            }
            for(int i = 0; i < values.getLength(); ++i){
                if(rowIndex.getEleAtPos(i) == rPos && colIndex.getEleAtPos(i) == cPos){
                    if(x != 0){
                        values.setEleAtPos(i, x);
                    }
                    if(x == 0){
                        rowIndex.deleteEleAtPos(i);
                        colIndex.deleteEleAtPos(i);
                        values.deleteEleAtPos(i);
                    }
                    return;
                }
            }
            if(x != 0){
                rowIndex.insertEleAtPos(rowIndex.getLength(),rPos);
                colIndex.insertEleAtPos(colIndex.getLength(),cPos);
                values.insertEleAtPos(values.getLength(),x);
            }
        }
        T getEntry(int rPos, int cPos){
            if(rPos >= rows || rPos < 0 || cPos >= cols || cPos < 0){
                throw runtime_error("Index out of bounds");
            }
            for(int i = 0; i < values.getLength(); ++i){
                if(rowIndex.getEleAtPos(i) == rPos && colIndex.getEleAtPos(i) == cPos){
                    return values.getEleAtPos(i);
                }
            }
            return 0;
        }
        SparseMatrix<T> * add(SparseMatrix<T> * B){
            if(rows != B->rows || cols != B->cols){
                throw runtime_error("Matrices have incompatible sizes");
            }
            //把原先矩阵的值赋给结果矩阵
            SparseMatrix<T>* result = new SparseMatrix<T>(rows, cols);
            for(int i = 0; i < values.getLength(); ++i){
                result->setEntry(rowIndex.getEleAtPos(i), colIndex.getEleAtPos(i), values.getEleAtPos(i));
            }
            for(int i = 0; i < B->values.getLength(); ++i){
                T value = B->values.getEleAtPos(i);
                result->setEntry(B->rowIndex.getEleAtPos(i), B->colIndex.getEleAtPos(i), result->getEntry(B->rowIndex.getEleAtPos(i), B->colIndex.getEleAtPos(i)) + value);
            }
            return result;
        }
        SparseMatrix<T> * subtract(SparseMatrix<T> * B){
            if(rows != B->rows || cols != B->cols){
                throw runtime_error("Matrices have incompatible sizes");
            }
            //把原先矩阵的值赋给结果矩阵
            SparseMatrix<T>* result = new SparseMatrix<T>(rows, cols);
            for(int i = 0; i < values.getLength(); ++i){
                result->setEntry(rowIndex.getEleAtPos(i), colIndex.getEleAtPos(i), values.getEleAtPos(i));
            }
            for(int i = 0; i < B->values.getLength(); ++i){
                T value = B->values.getEleAtPos(i);
                result->setEntry(B->rowIndex.getEleAtPos(i), B->colIndex.getEleAtPos(i), result->getEntry(B->rowIndex.getEleAtPos(i), B->colIndex.getEleAtPos(i)) - value);
            }
            return result;
        }
        
        SparseMatrix<T> * multiply(SparseMatrix<T> * B){
            //perform multiplication if the sizes of the matrices are compatible.
            if(cols != B->rows){
                throw runtime_error("Matrices have incompatible sizes");
            }
            SparseMatrix<T>* result = new SparseMatrix<T>(rows, B->cols);
            for(int i = 0; i < colIndex.getLength(); ++i){
                for(int j = 0; j < B->rowIndex.getLength(); ++j){
                    if(colIndex.getEleAtPos(i) == B->rowIndex.getEleAtPos(j)){
                        T temp = result->getEntry(rowIndex.getEleAtPos(i), B->colIndex.getEleAtPos(j));
                        temp += values.getEleAtPos(i) * B->values.getEleAtPos(j);
                        result->setEntry(rowIndex.getEleAtPos(i), B->colIndex.getEleAtPos(j), temp);
                    }
                }
            }
            return result;
        }
        
        
        // Only call this function if you know the size of matrix is reasonable.
        void printMatrix(){
            for(int i = 0; i < rows; ++i){
                for(int j =0; j < cols; ++j){
                    cout << getEntry(i,j) << " ";
                }
                cout << endl;
            }
        }
        
        //This is for printing only non-zero entries
        void printNZMatrix(){
            T* rPol, * cPol, * value;
            int size = values.getLength();
            rPol = new T[size];
            cPol = new T[size];
            value = new T[size];
            for(int i = 0; i < size; ++i){
                rPol[i] = rowIndex.getEleAtPos(i);
                cPol[i] = colIndex.getEleAtPos(i);
                value[i] = values.getEleAtPos(i);
            }
            for(int j = 0; j < values.getLength(); ++j){
                for(int k = j + 1; k < values.getLength(); ++k){
                    if(rPol[j] > rPol[k]){
                        swap(rPol[j], rPol[k]);
                        swap(cPol[j], cPol[k]);
                        swap(value[j], value[k]);
                    }
                }
            }
            for(int j = 0; j < values.getLength(); ++j){
                for(int k = j + 1; k < values.getLength(); ++k){
                    if(rPol[j] == rPol[k]){
                        if(cPol[j] > cPol[k]){
                        swap(rPol[j], rPol[k]);
                        swap(cPol[j], cPol[k]);
                        swap(value[j], value[k]); 
                        }
                    }
                }
            }
            for(int i = 0; i < size; ++i){
                cout << rPol[i] << " " << cPol[i] << " " << value[i] << endl;
            }
            delete[] rPol;
            delete[] cPol;
            delete[] value;
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
