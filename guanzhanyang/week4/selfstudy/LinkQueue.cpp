#include <iostream>
using namespace std;

template<class T>
struct DNode
{
    T data;
    DNode<T>* next;
};

template<class T>
class LinkQueue
{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue()
        {
            front=new DNode<T>;
            front->next=nullptr;
            back=front;
            length=0;
        }
        ~LinkQueue()
        {
            while(front!=nullptr)
            {
                back=front;
                front=front->next;
                delete back;
            }
        }
        int getlength()
        {
            return length;
        }
        bool isEmpty()
        {
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
        T deQueue()
        {
            if(length==0)
            {
                throw"Empty Queue!";
            }
            DNode<T>* tempN=front->next;//首先保存最后需要被传出去的指针
            //现在再处理头空节点
            front->next=tempN->next;
            //注意最后被传出去的类型是T
            T tempD=tempN->data;
            delete tempN;
            --length;
            if(length==0)
            {
                front=back;
            }
            return tempD;
        }
        void printQueue()
        {
            cout << "Front of queue: ";
            DNode<T>* cur=front->next;
            while(cur!=nullptr)
            {
                cout<<cur->data<<" ";
                cur=cur->next;
            }
            cout << ": back of queue" << endl;
        }

        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }//这个函数用来查看队列最前端元素
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



