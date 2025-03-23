//分隔链表
#include <iostream>
using namespace std;
struct ListNode {
    int val;//节点的值
    ListNode *next;//指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}//默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}//带数值的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* small=new ListNode(0);
        ListNode* large=new ListNode(0);
        ListNode* smallhead=small;//这里定义两个哑节点
        ListNode* largehead=large;
        while(head)
        {
            if(head->val<x)
            {
                small->next=head;
                small=small->next;
            }
            else
            {
                large->next=head;
                large=large->next;
            }
            head=head->next;
        }
        large->next=nullptr;
        small->next=largehead->next;
        return smallhead->next;
    }
};
