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

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack{
    private:
        DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

template <class T>
class LinkQueue{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue(){
            front = new DNode<T>;
            front->next = NULL;
            back = front;
            length = 0;
        }
        ~LinkQueue(){
            while(front!=NULL){
                back = front;
                front = front->next;
                delete back;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void enQueue(T x){
            DNode<T>* tmpN = new DNode<T>;
            tmpN->data = x;
            tmpN->next = NULL;
            back->next = tmpN;
            back = tmpN;
            length++;
        }
        T deQueue(){
            if(length==0) throw "Queue Empty!";
            DNode<T>* tmpN = front->next;
            front->next = tmpN->next;
            T tmpD = tmpN->data;
            delete tmpN;
            length--;
            if(length==0) back = front;
            return tmpD;
        }
        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }
        void printQueue(){
            cout << "Front of queue: ";
            DNode<T>* tmp = front->next;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ": back of queue" << endl;
        }
};

/* Questions 1,2,4 UPLOAD START */

template <class T>
class BinTree{
    private:
        T data;
        BinTree<T>* left;
        BinTree<T>* right;
    public:
        BinTree(){
            left = NULL;
            right = NULL;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
        }
        ~BinTree(){
            
        }
        void addLChild(BinTree<T>* bt){
            left = bt;
        }
        void addLChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
        }
        void addRChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addRChild(bt);
        }
        T getData(){
            return data;
        }
        void setData(T x){
            data = x;
        }
        BinTree<T>* getLChild(){
            return left;
        }
        BinTree<T>* getRChild(){
            return right;
        }
        void printPreOrderR(){
            cout << data << " ";
            if(left!=NULL) left->printPreOrderR();
            if(right!=NULL) right->printPreOrderR();
        }
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
        }
        void printLevelOrder(){
            LinkQueue<BinTree<T> *> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                BinTree<T>* tmpN = q.deQueue();
                cout << tmpN->data << " ";
                if(tmpN->left!=NULL) q.enQueue(tmpN->left);
                if(tmpN->right!=NULL) q.enQueue(tmpN->right);
            }
        }
        
        
        bool isLeaf(){
            return left==NULL && right==NULL;
        }
        int leafNodeCount(){ // question 1
            
        }
        
        bool isComplete(){ // question 2
            
        }
		
		void printSnakeLevelOrder(){ // question 4
            // TODO
            
        }
        
};

/* Questions 1,2,4 UPLOAD END */

/* Question 3 UPLOAD START */
template <class T>
BinTree<T>* buildFromPreIn(T* preArr, T* inArr, int n){
    
}
/* Question 3 UPLOAD END */

void test1(){
    BinTree<int> *treeK = new BinTree<int>(1);
    cout << treeK->leafNodeCount() << endl;
    treeK->addLChild(2);
    treeK->addRChild(3);
    cout << treeK->leafNodeCount() << endl;
    treeK->getLChild()->addLChild(4);
    treeK->getLChild()->addRChild(5);
    treeK->getRChild()->addLChild(6);
    treeK->getRChild()->addRChild(7);
    cout << treeK->leafNodeCount() << endl;
    treeK->getLChild()->getLChild()->addLChild(8);
    treeK->getLChild()->getLChild()->addRChild(9);
    cout << treeK->leafNodeCount() << endl;
    
}
/*
void test2(){
    BinTree<int> *treeK = new BinTree<int>(1);
    cout << weightedPathLength(treeK) << endl;
    treeK->addLChild(2);
    cout << weightedPathLength(treeK) << endl;
    treeK->addRChild(3);
    cout << weightedPathLength(treeK) << endl;
    treeK->getLChild()->addLChild(4);
    treeK->getLChild()->addRChild(5);
    treeK->getRChild()->addLChild(6);
    treeK->getRChild()->addRChild(7);
    cout << weightedPathLength(treeK) << endl;
    treeK->getLChild()->getLChild()->addLChild(8);
    treeK->getLChild()->getLChild()->addRChild(9);
    cout << weightedPathLength(treeK) << endl;
}
*/
void test3(){
    BinTree<int> *treeK = new BinTree<int>(1);
    treeK->addLChild(2);
    treeK->addRChild(3);
    treeK->getLChild()->addLChild(4);
    treeK->getLChild()->addRChild(5);
    treeK->getRChild()->addLChild(6);
    treeK->getRChild()->addRChild(7);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
    
    treeK->getLChild()->getLChild()->addLChild(8);
    treeK->getLChild()->getLChild()->addRChild(9);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
    
    treeK->getLChild()->getRChild()->addRChild(11);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
    
    treeK->getLChild()->getLChild()->getLChild()->addLChild(16);
    cout << (treeK->isComplete() ? "Yes" : "No") << " ";
}

void test4(){
    BinTree<char> * tmp1, *tmp5;
    BinTree<int> *tmp2, *tmp3, *tmp4;
    
    int t2p[3] = {1,2,3};
    int t2i[3] = {2,1,3};
    
    tmp2 = buildFromPreIn(t2p,t2i,3);
    tmp2->printPreOrderR();
    cout << endl;
    tmp2->printInOrderR();
    cout << endl;
    tmp2->printPostOrderR();
    cout << endl;
    tmp2->printLevelOrder();
    cout << endl;
    
    char t1p[7] = {'A','B','D','G','C','E','F'};
    char t1i[7] = {'D','G','B','A','E','C','F'};
    
    tmp1 = buildFromPreIn(t1p,t1i,7);
    tmp1->printPreOrderR();
    cout << endl;
    tmp1->printInOrderR();
    cout << endl;
    tmp1->printPostOrderR();
    cout << endl;
    tmp1->printLevelOrder();
    cout << endl;
    
}

int main(){
    test1();
 //   test2();
    test3();
    test4();
    return 0;
}