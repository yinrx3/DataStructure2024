//排序链表
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
    ListNode* sortList(ListNode* head) {

        ListNode* sortmove=new ListNode(0,nullptr);
        ListNode* sortHead=new ListNode(0,sortmove);
        
        //问题在于取得当前最小元素的位序
        


        int x=10*10*10*10*10+1;
        ListNode* dummy=new ListNode(x,head);
        while(head!=nullptr)
        {
            int number=0;
            ListNode* outcir=dummy;
            while(outcir!=nullptr)//通过这个取得最小元以及它的位序
            {
                if(outcir->val<=x)
                {
                    x=outcir->val;
                    ListNode* incir=dummy;
                    while(incir!=outcir)
                    {
                        ++number;
                        incir=incir->next;
                    }
                }
                outcir=outcir->next;
            }
            ListNode* cur=new ListNode(0,head);
            for(int i=0;i<number;++i)
            {
                cur=cur->next;
            }
            sortmove->next=cur;
            sortmove=sortmove->next;
            ListNode* precur=new ListNode(0,head);
            for(int i=0;i<number;++i)
            {
                precur=precur->next;
            }
            precur->next=precur->next->next;

        }
        return sortHead->next;

    }
};



// 主函数
int main() {
    Solution solution;

    // 创建一个测试链表 4 -> 2 -> 1 -> 3
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);

    // 排序链表
    ListNode* sortedHead = solution.sortList(head);

    // 打印排序后的链表
    ListNode* current = sortedHead;
    while (current != nullptr) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << endl;

    // 释放内存
    while (sortedHead != nullptr) {
        ListNode* temp = sortedHead;
        sortedHead = sortedHead->next;
        delete temp;
    }

    return 0;
}
