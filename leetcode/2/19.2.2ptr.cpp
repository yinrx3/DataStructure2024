//快慢指针法删除倒数i个节点
#include <iostream>
using namespace std;
struct ListNode {
    int val;//节点的值
    ListNode *next;//指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}//默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}//带数值的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//快慢指针，时间复杂度更低
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        ListNode* dummy=new ListNode(0,head);
        ListNode* first=head;
        ListNode* second=dummy;
        for(int i=0;i<n;++i)
        {
            first=first->next;
        }
        while(first!=nullptr)
        {
            first=first->next;
            second=second->next;
        }
        second->next=second->next->next;
        ListNode* ans=dummy->next;
        delete dummy;
        return ans;
    }
};