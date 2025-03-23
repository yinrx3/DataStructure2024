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
        while(cur!=nullptr)
        {
            ListNode* nex=cur->next;//也就是这里移动的只有cur,每一轮不断根据cur重新创建nex
            cur->next=move;
            move=cur;
            cur=nex;
        }//可以理解为称号的移动
        return move;
    }
};
// 辅助函数：打印链表
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

// 辅助函数：创建链表
ListNode* createList(const initializer_list<int>& values) {
    if (values.size() == 0) return nullptr;
    auto it = values.begin();
    ListNode* head = new ListNode(*it++);
    ListNode* current = head;
    for (; it != values.end(); ++it) {
        current->next = new ListNode(*it);
        current = current->next;
    }
    return head;
}

// 释放链表内存
void deleteList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // 创建链表 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = createList({1, 9, 3, 4, 98});
    
    // 创建 Solution 对象
    Solution solution;
    
    // 反转链表
    ListNode* reversedHead = solution.reverseList(head);
    
    // 打印反转后的链表
    printList(reversedHead);
    
    // 释放链表内存
    deleteList(reversedHead);
    
    return 0;
}