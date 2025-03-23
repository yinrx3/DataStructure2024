#include <iostream>
using namespace std;

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
            length = 0;
            back = front;
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
            return length==0; // return front==back;
        }
        void enQueue(T x){
            length++;
            DNode<T>* newNode = new DNode<T>;
            newNode->data = x;
            newNode->next = NULL;
            back->next = newNode;
            back = newNode;
        }
        T deQueue(){
            if(length==0) throw "Empty queue";
            DNode<T>* delNode = front->next;
            front->next = delNode->next;
            T data = delNode->data;
            delete delNode;
            length--;
            if(length==0) back = front;
            return data;
        }
        T peekQueue(){
            if(length==0) throw "Empty queue";
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

int main(){
    LinkQueue<int> Q;
    cout << "Is queue empty? " << (Q.isEmpty() ? "Yes" : "No") << endl;
    for(int i=1;i<=10;i++)
        Q.enQueue(i);
    cout << "After inserting 10 items, is queue empty? " << (Q.isEmpty() ? "Yes" : "No") << endl;
    cout << "The actual queue: " << endl;
    Q.printQueue();
    cout << "Front of queue is currently " << Q.peekQueue() << endl;
    for(int j=1;j<=5;j++)
        cout << Q.deQueue() << " is leaving the queue." << endl;
    cout << "Latest look of the queue:" << endl;
    Q.printQueue();
    for(int j=1;j<=5;j++)
        cout << Q.deQueue() << " is leaving the queue." << endl;
    cout << "Is queue empty? " << (Q.isEmpty() ? "Yes" : "No") << endl;
    for(int i=1;i<=10;i++)
        Q.enQueue(i+10);
    cout << "After inserting 10 items, is queue empty? " << (Q.isEmpty() ? "Yes" : "No") << endl;
    cout << "The actual queue: " << endl;
    Q.printQueue();
}
