#include <iostream>
#include <string>
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

void test2(){
    // RPN evaluator, space separated between numbers and/or operators
    LinkStack<int> S;
    string x;
    
    do{
        cin >> x;
        if(x=="="){
            if(S.getLength()!=1){
                cout << "Bad expression!" << endl;
            }
            else{
                cout << "Expression evaluated to " << S.pop() << endl;
            }
        }
        else if(x=="+"){
            if(S.getLength()<=1){
                cout << "Bad expression!" << endl;
            }
            else{
                S.push(S.pop()+S.pop());
            }
        }
        else if(x=="-"){
            if(S.getLength()<=1){
                cout << "Bad expression!" << endl;
            }
            else{
                int b = S.pop();
                S.push(S.pop() - b);
            }
        }
        else if(x=="*"){
            if(S.getLength()<=1){
                cout << "Bad expression!" << endl;
            }
            else{
                S.push(S.pop() * S.pop());
            }
        }
        else if(x=="/"){
            if(S.getLength()<=1){
                cout << "Bad expression!" << endl;
            }
            else{
                int b = S.pop();
                S.push(S.pop() / b);
            }
        }
        else{
            S.push(stoi(x));
        }
    }while(x!="=");
}

int main(){
    //test1();
    test2();
    return 0;
}