#include <iostream>
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

int main(){
    int r[3] = {1,2,3};
    LinkList<int> L(r,3);
    cout << "Current List: " << endl;
    L.printList();
    cout << endl;
    try{
        L.insertEleAtPos(1,4);
        L.insertEleAtPos(4,5);
        L.insertEleAtPos(5,6);
        L.insertEleAtPos(6,7);
    }
    catch(const char* s){
        cout << s << endl;
    }
    cout << "After adding elements:" << endl;
    L.printList();
    cout << endl << "Searching for position of 3: " << L.locateEle(3) << endl;
    cout << "Searching for position of 4: " << L.locateEle(4) << endl;
    cout << "Searching for position of 8: " << L.locateEle(8) << endl;
    cout << "Element at position 4: " << L.getEleAtPos(4) << endl;
    try{
        L.deleteEleAtPos(0);
        L.getEleAtPos(10);
    }
    catch(const char* s){
        cout << s << endl;
    }
    cout << "Now we have deleted element at position 0: " << endl;
    L.printList();
    cout << endl;
    
    LinkList<int> L2(r,3);
    for(int i=3;i<=300;i++){
        L2.insertEleAtPos(i,i+1);
    }
    L2.printList();
    return 0;
}