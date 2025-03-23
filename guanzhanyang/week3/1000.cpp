#include <iostream>
using namespace std;

template <class T>
struct DNode {
    T data;
    DNode<T>* next;
};

template <class T>
class LinkList {
private:
    int length;
    DNode<T>* head;

public:
    LinkList() {
        head = new DNode<T>;
        head->next = nullptr;
        length = 0;
    }

    LinkList(T* a, int n) {
        head = new DNode<T>;
        head->next = nullptr;
        for (int i = n - 1; i >= 0; i--) {
            DNode<T>* tmpNode = new DNode<T>;
            tmpNode->next = head->next;
            tmpNode->data = a[i];
            head->next = tmpNode;
        }
        length = n;
    }

    ~LinkList() {
        while (head != nullptr) {
            DNode<T>* tmpNode = head;
            head = head->next;
            delete tmpNode;
        }
    }

    int getLength() {
        return length;
    }

    bool isEmpty() {
        return length == 0;
    }

    void insertEleAtPos(int i, T x) {
        if (i < 0 || i > length)
            throw "Bad position";
        DNode<T>* tmpNode = head;
        for (int j = 0; j < i; j++) {
            tmpNode = tmpNode->next;
        }
        DNode<T>* newNode = new DNode<T>;
        newNode->data = x;
        newNode->next = tmpNode->next;
        tmpNode->next = newNode;
        length++;
    }

    T deleteEleAtPos(int i) {
        if (i < 0 || i >= length)
            throw "Bad position";
        DNode<T>* tmpNode = head;
        for (int j = 0; j < i; j++) {
            tmpNode = tmpNode->next;
        }
        DNode<T>* delNode = tmpNode->next;
        tmpNode->next = delNode->next;
        T tmp = delNode->data;
        delete delNode;
        length--;
        return tmp;
    }

    void printList() {
        DNode<T>* tmpNode = head->next;
        while (tmpNode != nullptr) {
            cout << tmpNode->data << " ";
            tmpNode = tmpNode->next;
        }
        cout << endl; // 添加换行
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




void test1(){
    int r[3] = {-9,-8,-1};
    int s[9] = {-1,4,27,35,47,56,99,100,120};
    LinkList<int> *L1 = new LinkList<int>(r,3);
    LinkList<int> *L2 = new LinkList<int>(s,9);
    L1->unionWithAnotherSortedList(L2)->printList();
    L1->printList();
    L2->printList();
    cout<<L1->unionWithAnotherSortedList(L2)->getLength()<<endl;
}

int main(){
    test1();
    return 0;
}