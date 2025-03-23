//k个一组翻转链表
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
        ListNode* prev=nullptr;
        ListNode* cur=head;
        while(cur!=nullptr)
        {
            ListNode* nex=cur->next;
            cur->next=prev;
            prev=cur;
            cur=nex;
        }
        return prev;//返回新的头节点
    }
    ListNode* reverseKGroup(ListNode* head, int k) 
    {
        if(head==nullptr||k==1)
            return head;
        //下面计算链表长度
        int length=0;
        ListNode* temp=head;
        while(temp!=nullptr)
        {
            length++;
            temp=temp->next;
        }
        //下面写一个伪头结点
        ListNode* dummy=new ListNode(0);
        dummy->next=head;
        ListNode* prevGroupEnd=dummy;
        while(length>=k)
        {
            ListNode* GroupStart=prevGroupEnd->next;
            ListNode* GroupEnd=GroupStart;
            for(int i=1;i<k;++i)
            {
                GroupEnd=GroupEnd->next;
            }
            ListNode* nextGroupStart=GroupEnd->next;
            GroupEnd->next=nullptr;//现在断开当前节点的末尾
            //下面调用函数翻转当前组
            ListNode* newGroupStart=reverseList(GroupStart);
            //下面将刚刚断开的片段和大链表重新连接起来
            prevGroupEnd->next=newGroupStart;
            GroupStart->next=nextGroupStart;
            //下面更新prev
            prevGroupEnd=GroupStart;
            length-=k;
        }
        ListNode* result=dummy->next;
        delete dummy;
        return result;
    }
};


