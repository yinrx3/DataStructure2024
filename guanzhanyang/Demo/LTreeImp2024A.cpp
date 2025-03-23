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
class LTree{
    private:
        T data;
        VecList<LTree<T> *> children;
    public:
        LTree(){

        }
        LTree(T x){
            data = x;
        }
        ~LTree(){

        }
        void addChild(LTree<T>* lt){
            children.insertEleAtPos(children.getLength(),lt);
        }
        void addChild(T x){
            LTree<T>* newTree = new LTree<T>(x);
            addChild(newTree);
        }
        LTree<T>* getChild(T x){
            for(int i=0;i<children.getLength();i++){
                if(children.getEleAtPos(i)->data == x)
                    return children.getEleAtPos(i);
            }
            return NULL;
        }
        void setData(T x){
            data = x;
        }
        T getData(){
            return data;
        }
        void printPreOrder(){
            cout << data << " ";
            for(int i=0;i<children.getLength();i++){
                children.getEleAtPos(i)->printPreOrder();
            }
        }
        void printPostOrder(){
            for(int i=0;i<children.getLength();i++){
                children.getEleAtPos(i)->printPostOrder();
            }
            cout << data << " ";
        }
        void printLevelOrder(){
            LinkQueue<LTree<T>*> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                LTree<T>* tmpTree = q.deQueue();
                cout << tmpTree->data << " ";
                for(int i=0;i<tmpTree->children.getLength();i++){
                    q.enQueue(tmpTree->children.getEleAtPos(i));
                }
            }
        }
};

int main(){
    LTree<char> testTree('A');
    testTree.addChild('B');
    LTree<char> testTree2('C');
    testTree2.addChild('G');
    testTree.addChild(&testTree2);
    LTree<char> * tmpTreeB = testTree.getChild('B');
    tmpTreeB->addChild('D');
    tmpTreeB->addChild('E');
    tmpTreeB->addChild('F');
    LTree<char> * tmpTreeE = tmpTreeB->getChild('E');
    tmpTreeE->addChild('H');
    tmpTreeE->addChild('I');
    //print trees now
    testTree.printPreOrder();
    cout << endl;
    testTree.printPostOrder();
    cout << endl;
    testTree.printLevelOrder();
    cout << endl;
    return 0;
}
