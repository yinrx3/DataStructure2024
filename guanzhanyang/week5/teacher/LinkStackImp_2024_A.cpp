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
            DNode<T>* tmp;
            while(top!=NULL){
                tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0; // return top==NULL;
        }
        void push(T x){
            DNode<T>* newTop = new DNode<T>;
            newTop->data = x;
            newTop->next = top;
            top = newTop;
            length++;
        }
        T pop(){
            if(isEmpty()) throw "Stack Empty";
            DNode<T>* tmpNode = top;
            top = top->next;
            T data = tmpNode->data;
            delete tmpNode;
            length--;
            return data;
        }
        T getTop(){
            if(isEmpty()) throw "Stack Empty";
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
    string s;
    LinkStack<int> calcStack;

    do{
        cin >> s;
        if(s=="+"){
            int b, a;
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            b = calcStack.pop();
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            a = calcStack.pop();
            calcStack.push(a+b);
        }
        else if(s=="-"){
            int b, a;
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            b = calcStack.pop();
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            a = calcStack.pop();
            calcStack.push(a-b);
        }
        else if(s=="*"){
            int b, a;
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            b = calcStack.pop();
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            a = calcStack.pop();
            calcStack.push(a*b);
        }
        else if(s=="/"){
            int b, a;
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            b = calcStack.pop();
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            a = calcStack.pop();
            calcStack.push(a/b);
        }
        else if(s=="="){
            if(calcStack.isEmpty()){
                cout << "Invalid expression" << endl;
                return;
            }
            cout << calcStack.pop() << endl;
        }
        else{
            int a = stoi(s); // string to int
            calcStack.push(a);
        }
    }while(s!="=");

}

int main(){
    //test1();
    test2();
    return 0;
}
