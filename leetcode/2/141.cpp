//环形链表
#include <iostream>
using namespace std;
struct ListNode {
    int val;//节点的值
    ListNode *next;//指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}//默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}//带数值的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution 
{
public:
    bool hasCycle(ListNode *head) 
    {
        if(!head||!head->next)
            return false;
        ListNode* slow=head;
        ListNode* fast=head->next;
        fast=head;
        while(slow!=fast)
        {
            if(fast->next==nullptr||fast==nullptr)
            {
                return false;
            }
            fast=fast->next->next;
            slow=slow->next;
        }
        return true;
    }
};