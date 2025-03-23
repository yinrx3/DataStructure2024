#include <iostream>
using namespace std;
//预测   翻转链表
/* UPLOAD START */
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
        LinkList()
        {
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

        void reverselist()
        {
            DNode<T>* pre=nullptr;
            DNode<T>* cur=head->next;
            DNode<T>* temp;
            while(cur){
                temp=cur->next;
                cur->next=pre;
                pre=cur;
                cur=temp;
            }
            head->next=pre;
        }
};


int main()
{
    int r[7] = {1,3,4,7,9,11,15};
    LinkList<int> *L1 = new LinkList<int>(r,7);
    L1->reverselist();
    L1->printList();
    return 0;
}