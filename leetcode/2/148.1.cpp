#include <iostream>
using namespace std;

struct ListNode {
    int val; // 节点的值
    ListNode *next; // 指向下一个节点的指针
    ListNode() : val(0), next(nullptr) {} // 默认构造函数
    ListNode(int x) : val(x), next(nullptr) {} // 带数值的构造函数
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head; // 如果链表为空或只有一个节点，直接返回

        ListNode dummy(0); // 创建一个虚拟头节点
        dummy.next = head;
        ListNode* sortHead = &dummy;

        while (head != nullptr) {
            // 查找最小值节点和其前驱节点
            ListNode* minNodePrev = nullptr;
            ListNode* minNode = head;
            ListNode* current = head;
            ListNode* prev = nullptr;

            while (current->next != nullptr) {
                if (current->next->val < minNode->val) {
                    minNode = current->next;
                    minNodePrev = current;
                }
                current = current->next;
            }

            // 如果最小值节点不是当前节点
            if (minNode != head) {
                // 将最小值节点从链表中移除
                if (minNodePrev) minNodePrev->next = minNode->next;
                // 插入到已排序链表的尾部
                minNode->next = nullptr;
                sortHead->next = minNode;
                sortHead = sortHead->next;
            } else {
                // 如果最小值节点就是当前节点，则直接移动到已排序链表
                sortHead->next = head;
                sortHead = sortHead->next;
                head = head->next;
                sortHead->next = nullptr;
            }
        }

        return dummy.next; // 返回排序后的链表
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