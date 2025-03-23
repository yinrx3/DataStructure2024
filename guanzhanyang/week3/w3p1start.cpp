#include <iostream>
using namespace std;

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

        LinkList<T>* unionWithAnotherSortedList(LinkList<T>* L) {
            LinkList<T>* newList = new LinkList<T>();
            DNode<T>* r1 = this->head->next; 
            DNode<T>* r2 = L->head->next;   
            DNode<T>* current = newList->head;

        while (r1 != nullptr && r2 != nullptr) {
            DNode<T>* newNode = new DNode<T>(); 
            if (r1->data < r2->data) {
            newNode->data = r1->data; 
            current->next = newNode;   
            r1 = r1->next;            
        } else if (r1->data > r2->data) {
            newNode->data = r2->data; 
            current->next = newNode;  
            r2 = r2->next;             
        } else {
            newNode->data = r1->data; 
            current->next = newNode;   
            r1 = r1->next;             
            r2 = r2->next;             
        }
        current = current->next; 
    }
    while (r1 != nullptr) {
        DNode<T>* newNode = new DNode<T>();
        newNode->data = r1->data; 
        current->next = newNode; 
        current = current->next;   
        r1 = r1->next;           
    }
    while (r2 != nullptr) {
        DNode<T>* newNode = new DNode<T>();
        newNode->data = r2->data; 
        current->next = newNode;  
        current = current->next;   
        r2 = r2->next;            
    }
    newList->length = this->getLength() + L->getLength(); // 可以根据新链表节点数量更新
    return newList;
}
        
};
/* UPLOAD END */

void test1(){
    int r[7] = {1,3,4,7,9,11,15};
    int s[3] = {-3,4,27};
    LinkList<int> *L1 = new LinkList<int>(r,7);
    LinkList<int> *L2 = new LinkList<int>(s,3);
    L1->unionWithAnotherSortedList(L2)->printList();
    cout<<endl;
    L1->printList();
    cout<<endl;
    L2->printList();
    cout << endl;
}

int main(){
    test1();
    return 0;
}