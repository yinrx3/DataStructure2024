#include <iostream>
using namespace std;
struct DNode
{
    int val;
    DNode* left;
    DNode* right;//下面重载两个DNode结点构造函数
    DNode():val(0),left(nullptr),right(nullptr){}
    DNode(int a):val(a),left(nullptr),right(nullptr){}
    DNode(int val,DNode* left,DNode* right):val(val),left(left),right(right){}
};
//下面实现一个以head为哨兵结点的双向链表(头空结点)
class DoubleLinkList{
    private:
        int length;
        DNode* head;
    public:
        //实现一个空双向链表(只有一个head头空哨兵结点)默认构造函数
        DoubleLinkList(){
            length=0;
            head=new DNode();
        }
        //将一个长为n的int型数组x复制进入双链表，带参数的构造函数
        //为了减小复杂度，使用头插法
        DoubleLinkList(int n,int* x){
            length=n;
            head=new DNode();
            for(int i=n-1;i>=0;--i){
                if(i==n-1){
                    DNode* tempD=new DNode(x[i],head,nullptr);
                    head->right=tempD;
                }
                else{
                    DNode* tempD=new DNode(x[i]);
                    tempD->right=head->right;
                    head->right->left=tempD;
                    tempD->left=head;
                    head->right=tempD;
                }
            }
        }
        //析构函数，与单链表一样操作即可
        ~DoubleLinkList(){
            while(head!=nullptr){
                DNode* deNode=head;
                head=head->right;
                delete deNode;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        //现在统一定义，双链表第一个非头空结点的位序记为1，即原数组第一个元素(数组中位序为0)
        //修改双链表指定位序的元素
        void setNodeAtPos(int Pos,int x){
            if(Pos>length||Pos<=0)
                cout<<"setNodeAtPos: Wrong Position!"<<endl;
            else{
                DNode* found=head;
                for(int i=0;i<Pos;++i){
                    found=found->right;
                }
                found->val=x;
            }
        }
        //删除双链表指定位序的元素
        void deNodeAtPos(int Pos){
            if(Pos>length||Pos<=0)
                cout<<"deNodeAtPos: Wrong Position!"<<endl;
            else{
                DNode* found=head;
                for(int i=0;i<Pos-1;++i){
                    found=found->right;
                }
                //先获取要删除元素的前一个元素
                if(Pos==length){//如果要删除的是最后一个元素
                    found->right->left=nullptr;
                    found->right=nullptr;
                    --length;
                }//要删除的元素后面还有元素
                else{
                    found->right->right->left=found;
                    found->right=found->right->right;
                }
            }
        }
        //插入双链表指定位序的元素
        //我们明确，插入的位序Pos,是在位序为Pos的元素后面插入一个数据，如果输入Pos=0,代表插入一个非空头结点
        void insertNodeAtPos(int Pos,int x){
            if(Pos>length||Pos<0)
                cout<<"insertNodeAtPos: Wrong Position!"<<endl;
            else{
                //先获取要插入位置的前面一个元素，即若Pos=0，要获取head
                DNode* found=head;
                for(int i=0;i<Pos;++i){
                    found=found->right;
                }//这里found就是找到的要插入位置的前面一个元素
                DNode* insNode=new DNode(x);
                if(Pos==length){//在队尾增加元素
                    found->right=insNode;
                    insNode->left=found;
                    ++length;
                }
                else{
                    insNode->right=found->right;
                    found->right->left=insNode;
                    insNode->left=found;
                    found->right=insNode;
                    ++length;
                }
            }
        }
        //打印双链表所有元素(除了头空哨兵结点)
        void printDoubleLinkList(){
            DNode* printNode=head->right;
            if(printNode==nullptr){
                cout<<"Empty DoubleLinkList!"<<endl;
            }
            else{
                while(printNode!=nullptr){
                    cout<<printNode->val<<" ";
                    printNode=printNode->right;
                }
                cout<<endl;
            }
        }
};
int main(){
    int x[0]={};
    DoubleLinkList p(0,x);
    p.printDoubleLinkList();
    p.insertNodeAtPos(0,2);
    p.printDoubleLinkList();
    cout<<p.getLength()<<endl;
    return 0;
}