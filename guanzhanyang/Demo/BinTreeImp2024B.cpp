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
            BinTree<T>* newTree = new BinTree<T>(x);
            addLChild(newTree);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
        }
        void addRChild(T x){
            BinTree<T>* newTree = new BinTree<T>(x);
            addRChild(newTree);
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
            LinkQueue<BinTree<T>*> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                BinTree<T>* tmp = q.deQueue();
                cout << tmp->data << " ";
                if(tmp->left!=NULL) q.enQueue(tmp->left);
                if(tmp->right!=NULL) q.enQueue(tmp->right);
            }
        }

        void printPreOrderNR(){
            LinkStack<BinTree<T>*> S;
            BinTree<T>* cur = this;
            while(cur!=NULL || !S.isEmpty()){
                if(cur!=NULL){
                    cout << cur->data << " ";
                    if(cur->right!=NULL) S.push(cur->right);
                    cur = cur->left;
                }
                else if(!S.isEmpty()){
                    cur = S.pop();
                }
            }
        }

        void printInOrderNR(){
            LinkStack<BinTree<T>*> S;
            BinTree<T>* cur = this;
            while(cur!=NULL || !S.isEmpty()){
                if(cur!=NULL){
                    S.push(cur);
                    cur = cur->left;
                }
                else{
                    cur = S.pop();
                    cout << cur->data << " ";
                    cur = cur->right;
                }
            }
        }

        void printPostOrderNR(){
            LinkStack<BinTree<T>*> S;
            LinkStack<int> S_aux;
            BinTree<T>* cur = this;
            while(cur!=NULL || !S.isEmpty()){
                if(cur!=NULL){
                    S.push(cur);
                    S_aux.push(1);
                    cur = cur->left;
                }
                else{
                    cur = S.pop();
                    int tmp = S_aux.pop();
                    if(tmp==1){
                        // first
                        S.push(cur);
                        S_aux.push(2);
                        cur = cur->right;
                    }
                    else{
                        // second
                        cout << cur->data << " ";
                        cur = NULL;
                    }
                }
            }
        }
};

void test0(){
    BinTree<char> bt('A');
    bt.addLChild('B');
    bt.getLChild()->addRChild('C');
    bt.addRChild('D');
    BinTree<char>* btDp = bt.getRChild();
    btDp->addLChild('E');
    btDp->addRChild('F');
    btDp->getRChild()->addLChild('G');
    btDp->getRChild()->getLChild()->addRChild('H');
    btDp->getRChild()->addRChild('I');

    cout << "Preorder: ";
    bt.printPreOrderR();
    cout << endl;
    cout << "In order: ";
    bt.printInOrderR();
    cout << endl;
    cout << "Post order: ";
    bt.printPostOrderR();
    cout << endl;
    cout << "Level order: ";
    bt.printLevelOrder();
    cout << endl;

    cout << "Preorder: ";
    bt.printPreOrderNR();
    cout << endl;
    cout << "In order: ";
    bt.printInOrderNR();
    cout << endl;
    cout << "Post order: ";
    bt.printPostOrderNR();
    cout << endl;
}

int main(){
    test0();
    return 0;
}
