//翻转链表
#include <iostream>
using namespace std;
struct ListNode {
    int val;//节点的值
    ListNode *next;//指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}//默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}//带数值的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution{
public:
    ListNode* reverseList(ListNode* head) 
    {
        ListNode* move=nullptr;
        ListNode* cur=head;
        while(cur)
        {
            ListNode* nex=cur->next;
            cur->next=move;
            move=cur;
            cur=nex;
        }
        return move;
    }
};