#include <iostream>
#include <stack>
using namespace std;
class MyQueue{
    private:
        stack<int> instack,outstack;
    public:
        MyQueue(){}//保持默认初始化即可
        void push(int x){
            instack.push(x);
        }
        int pop(){
            if(outstack.empty()){
                while(!instack.empty()){
                    outstack.push(instack.top());
                    instack.pop();
                }
            }
            int result=outstack.top();
            outstack.pop();
            while(!outstack.empty()){
                instack.push(outstack.top());
                outstack.pop();
            }
            return result;
        }
        int peek(){
            if(outstack.empty()){
                while(!instack.empty()){
                    outstack.push(instack.top());
                    instack.pop();
                }
            }
            int result=outstack.top();
            int sizeout=outstack.size();
            for(int i=0;i<sizeout;++i){
                instack.push(outstack.top());
                outstack.pop();
            }
            return result;
        }
        bool empty(){
            return instack.empty();
        }
};
int main()
{
    MyQueue myQueue;
    myQueue.push(1); // queue is: [1]
    myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
    cout<<myQueue.peek()<<endl; // return 1
    cout<<myQueue.pop()<<endl; // pop 1, queue is [2]
    cout<<myQueue.peek()<<endl; // return 2
    myQueue.empty(); // return false
}