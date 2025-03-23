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