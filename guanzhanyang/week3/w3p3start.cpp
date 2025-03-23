#include <iostream>
using namespace std;

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack{
    private:
        DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

/* UPLOAD START */
class MinIntStack{
    private:
        LinkStack<int> stack;
        LinkStack<int> asistant;
    public:
        MinIntStack(){
            //保持为空即可
        }
        ~MinIntStack(){
            //仍然是默认调用，保持空即可
        }
        bool isEmpty(){
            return stack.isEmpty();
        }
        void push(int x){
            if(stack.isEmpty())
            {
                stack.push(x);
                asistant.push(x);
            }
            else
            {
                stack.push(x);
                if(x<=asistant.getTop())
                {
                    asistant.push(x);
                }
            }
            
        }
        int pop(){
            if(stack.isEmpty())
            {
                throw"Empty Stack!";
            }
            else
            {
                if(stack.getTop()==asistant.getTop())
                {
                    asistant.pop();
                    return stack.pop();
                }
                else
                {
                    return stack.pop();
                }
            }
        }
        int getTop(){
            if(stack.isEmpty())
            {
                throw"Empty Stack!";
            }
            else
            {
                return stack.getTop();
            }
        }
        int getMin(){
            if(stack.isEmpty())
            {
                throw"Empty Stack!";
            }
            else
            {
                return asistant.getTop();
            }
            
        }
        void printStack(){
            stack.printStack();
        }
};
/* UPLOAD END */

void test1(){
    MinIntStack S;
    S.push(6);
    cout << S.getMin() << endl;
    S.push(7);
    cout << S.getMin() << endl;
    S.push(8);
    cout << S.getMin() << endl;
    S.push(5);
    cout << S.getMin() << endl;

    S.printStack();
    S.push(3);
    cout << S.getMin() << endl;
    S.printStack();
    S.pop();
    cout << S.getMin() << endl;
    S.printStack();
    S.push(10);
    cout << S.getMin() << endl;
    S.printStack();
    S.pop();
    cout << S.getMin() << endl;
    S.printStack();
    S.pop();
    cout << S.getMin() << endl;
    S.printStack();
}

int main()
{
    test1();
    return 0;
}