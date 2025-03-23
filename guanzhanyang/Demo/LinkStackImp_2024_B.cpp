#include <iostream>
#include <string>
using namespace std;

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkList{
    private:
        int length;
        DNode<T>* head;
    public:
        LinkList(){
            head = new DNode<T>;
            head->next = NULL;
            length = 0;
        }
        LinkList(T* a, int n){
            head = new DNode<T>;
            head->next = NULL;
            for(int i=n-1;i>=0;i--){
                DNode<T> *tmpNode = new DNode<T>;
                tmpNode->next = head->next;
                tmpNode->data = a[i];
                head->next = tmpNode;
            }
            length = n;
        }
        ~LinkList(){
            while(head!=NULL){
                DNode<T>* tmpNode = head;
                head = head->next;
                delete tmpNode;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(i < 0 || i > length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<i;j++){
                tmpNode = tmpNode->next;
            }
            DNode<T>* newNode = new DNode<T>;
            newNode->data = x;
            newNode->next = tmpNode->next;
            tmpNode->next = newNode;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i < 0 || i >= length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<i;j++){
                tmpNode = tmpNode->next;
            }
            DNode<T>* delNode = tmpNode->next;
            tmpNode->next = delNode->next;
            T tmp = delNode->data;
            delete delNode;
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i < 0 || i >= length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<=i;j++){
                tmpNode = tmpNode->next;
            }
            tmpNode->data = x;
        }
        T getEleAtPos(int i){
            if(i < 0 || i >= length)
                throw "Bad position";
            DNode<T>* tmpNode = head;
            for(int j=0;j<=i;j++){
                tmpNode = tmpNode->next;
            }
            return tmpNode->data;
        }
        int locateEle(T x){
            DNode<T>* tmpNode = head->next;
            int count = 0;
            while(tmpNode!=NULL){
                if(tmpNode->data == x) return count;
                tmpNode = tmpNode->next;
                count++;
            }
            return -1;
        }
        void printList(){
            DNode<T>* tmpNode = head->next;
            while(tmpNode!=NULL){
                cout << tmpNode->data << " ";
                tmpNode = tmpNode->next;
            }
        }
};

template <class T>
class LinkStack{
    private:
        LinkList<T> L;
    public:
        LinkStack(){

        }
        ~LinkStack(){

        }
        int getLength(){
            return L.getLength();
        }
        bool isEmpty(){
            return L.isEmpty();
        }
        void push(T x){
            L.insertEleAtPos(0,x);
        }
        T pop(){
            return L.deleteEleAtPos(0);
        }
        T getTop(){
            return L.getEleAtPos(0);
        }
        void printStack(){
            cout << "Stack top: ";
            L.printList();
            cout << ":stack bottom" << endl;
        }
};

void test1(){
    LinkStack<int> S;
    cout << (S.isEmpty()?"Empty Stack":"Non-empty Stack") << endl;
    S.printStack();
    cout << "Inserting things:" << endl;
    S.push(15);
    S.push(10);
    S.printStack();
    cout << "Peeking top of stack: it is " << S.getTop() << endl;
    cout << "Popping top of stack: it returns " << S.pop() << endl;
    cout << "Peeking top of stack again: it is " << S.getTop() << endl;
    S.printStack();
    S.pop();
    cout << "All things popped. " << (S.isEmpty()?"Empty Stack":"Non-empty Stack") << endl;
    cout << "Inserting things:" << endl;
    S.push(15);
    S.push(10);
    S.printStack();
    cout << "Peeking top of stack: it is " << S.getTop() << endl;
    cout << "Popping top of stack: it returns " << S.pop() << endl;
    cout << "Peeking top of stack again: it is " << S.getTop() << endl;
    S.printStack();
}

int main(){
    test1();
    //test2();
    return 0;
}
