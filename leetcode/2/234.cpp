//比较回文链表
struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr){};
    ListNode(int x): val (x) ,next(nullptr){};
    ListNode(int x,ListNode* next): val(0) ,next(next){};
};
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head||!head->next)
            return true;
        //通过快慢指针方法找到链表的中间节点
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast&&fast->next)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        //翻转后半部分
        ListNode* backHalf=reverseList(slow);
        ListNode* frontHalf=head;
        //以下比较两个分链表
        while(backHalf)
        {
            if(backHalf->val!=frontHalf->val)
            {
                return false;
            }
            frontHalf=frontHalf->next;
            backHalf=backHalf->next;
        }
        return true;
    }
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