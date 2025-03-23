#include <iostream>
using namespace std;
struct ListNode {
    int val;//节点的值
    ListNode *next;//指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}//默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}//带数值的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
int main()
{
    ListNode node1(1);
    ListNode node2(2,&node1);
    ListNode node3(3,&node2);
    ListNode node4(7,&node3);
    ListNode node5(8,&node4);
    ListNode node6(0,&node5);
    ListNode node7(-1,&node6);
    ListNode node8(6,&node7);
    ListNode node9(23,&node8);
    //以上将链表链接成了3->2->1
    //打印链表的数值
    ListNode* current=&node9;
    while(current!=nullptr)
    {
        cout<<current->val<<" ";
        current=current->next;
    }
    cout<<endl;
    return 0;
}