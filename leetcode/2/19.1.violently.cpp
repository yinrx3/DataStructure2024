//暴力法删除倒数i个链表
#include <iostream>
using namespace std;
struct ListNode {
    int val;//节点的值
    ListNode *next;//指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {}//默认构造函数
    ListNode(int x) : val(x), next(nullptr) {}//带数值的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
//暴力法，先遍历一遍链表得到链表长度，再遍历一遍找到要删除的节点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) 
    {
        ListNode* dummy=new ListNode(0,head);//增加一个哑节点
        int length=getLength(head);
        ListNode* cur=dummy;
        for(int i=1;i<length-n+1;++i)
        {
            cur=cur->next;
        }
        cur->next=cur->next->next;
        ListNode* ans=dummy->next;
        delete dummy;
        return ans;
    }
    int getLength(ListNode* head)
    {
        int length=0;
        while(head!=nullptr)
        {
            ++length;
            head=head->next;
        }
        return length;
    }
};
//分析时间复杂度
