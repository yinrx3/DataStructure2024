#include <iostream>
#include <string>
using namespace std;

/* UPLOAD START */

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

/* 
    priority queue with at most 10 different levels of priority
    Priority count starts from 0 (highest priority), 1 (next highest), etc...
*/

template <class T>
class SimplePriorityQueue{
    private:
        
    public:
        SimplePriorityQueue(){
            
        }
        SimplePriorityQueue(int numP){
            
        }
        ~SimplePriorityQueue(){
            
        }
        void enQueue(T x, int p){ //the int here is for priority
            
        }
        T deQueue(){
            
        }
        T peekQueue(){
            
        }
        bool isEmpty(){
            
        }
};

/* UPLOAD END */

int main(){
    
    SimplePriorityQueue<char> spq(6);
    cout << "Before insertion, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    int priors[16]={0,1,2,3,4,5,0,3,2,4,0,2,1,5,1,3};
    for(int i=0;i<16;i++){
        spq.enQueue('a'+i,priors[i]);
    }
    
    cout << "Front of queue is now " << spq.peekQueue() << endl;
    // Push out first 10 items
    for(int j=0;j<10;j++){
        cout << spq.deQueue() << " has left the queue" << endl;
    }
    cout << "Right now, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    cout << "Inserting some digits according to squares mod 6" << endl;
    for(int i=0;i<10;i++){
        spq.enQueue('0'+i,i*i%6);
    }
    
    // Empty the queues
    while(!spq.isEmpty()){
        cout << spq.deQueue() << " has left the queue" << endl;
    }
    cout << "Right now, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    for(int i=0;i<10;i++){
        spq.enQueue('0'+i,i%6);
    }
    
    cout << "Right now, queue is " << (spq.isEmpty()?"empty":"non-empty") << endl;
    return 0;
}