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
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode* dummy=new ListNode(0,head);
        ListNode* first=head;
        ListNode* second=dummy;
        for(int i=0;i<n;++i)
        {
            first=first->next;
        }
        while(first)
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
//这个是错误的删除节点之后，链表的新头节点是 dummy->next。这步操作确保了即使原始头节点被删除，链表的头部指针也被正确更新