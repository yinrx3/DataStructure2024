#include <iostream>
using namespace std;

template <class T>
struct DNode {
    T data;
    DNode* next;
    DNode() : next(nullptr) {} // 默认构造函数
};

template <class T>
class LinkList {
private:
    int length;
    DNode<T>* head;

public:
    LinkList() {
        head = new DNode<T>;
        head->next = nullptr;
        length = 0;
    }

    LinkList(T* a, int n) {
        head = new DNode<T>;
        head->next = nullptr;
        for (int i = n - 1; i >= 0; i--) {
            DNode<T>* tmpNode = new DNode<T>;
            tmpNode->data = a[i];
            tmpNode->next = head->next;
            head->next = tmpNode;
        }
        length = n;
    }

    ~LinkList() {
        while (head != nullptr) {
            DNode<T>* tmpNode = head;
            head = head->next;
            delete tmpNode;
        }
    }

    int getLength() const {
        return length;
    }

    bool isEmpty() const {
        return length == 0;
    }

    void printList() const {
        DNode<T>* tmpNode = head->next;
        if (tmpNode == nullptr) { // 检查链表是否为空
            cout << "List is empty." << endl;
            return;
        }
        while (tmpNode != nullptr) {
            cout << tmpNode->data << " ";
            tmpNode = tmpNode->next;
        }
        cout << endl; // 添加换行
    }

    LinkList<T>* unionWithAnotherSortedList(LinkList<T>* L) {
        LinkList<T>* newList = new LinkList<T>();
        DNode<T>* r1 = this->head->next; // 当前链表的第一个元素
        DNode<T>* r2 = L->head->next;     // 另一个链表的第一个元素
        DNode<T>* current = newList->head; // 新链表的尾指针

        while (r1 != nullptr && r2 != nullptr) {
            if (r1->data < r2->data) {
                // 深拷贝节点
                DNode<T>* newNode = new DNode<T>;
                newNode->data = r1->data;
                current->next = newNode;
                current = newNode;
                r1 = r1->next;
            } else if (r1->data > r2->data) {
                // 深拷贝节点
                DNode<T>* newNode = new DNode<T>;
                newNode->data = r2->data;
                current->next = newNode;
                current = newNode;
                r2 = r2->next;
            } else { // 相等的情况，只添加一次
                DNode<T>* newNode = new DNode<T>;
                newNode->data = r1->data;
                current->next = newNode;
                current = newNode;
                r1 = r1->next;
                r2 = r2->next;
            }
        }

        // 将剩余部分添加到新链表
        while (r1 != nullptr) {
            DNode<T>* newNode = new DNode<T>;
            newNode->data = r1->data;
            current->next = newNode;
            current = newNode;
            r1 = r1->next;
        }

        while (r2 != nullptr) {
            DNode<T>* newNode = new DNode<T>;
            newNode->data = r2->data;
            current->next = newNode;
            current = newNode;
            r2 = r2->next;
        }

        // 更新新链表的长度
        newList->length = this->getLength() + L->getLength();
        return newList;
    }
};

void test1() {
    int r[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int s[9] = {-3, 4, 27, 35, 47, 56, 99, 100, 120};
    LinkList<int>* L1 = new LinkList<int>(r, 8);
    LinkList<int>* L2 = new LinkList<int>(s, 9);
    
    LinkList<int>* result = L1->unionWithAnotherSortedList(L2);
    cout << "Union List: ";
    result->printList(); // 打印并集
    cout << "Original List 1: ";
    L1->printList(); // 打印原始链表1
    cout << "Original List 2: ";
    L2->printList(); // 打印原始链表2

    // 清理内存
    delete L1;
    delete L2;
    delete result;
}

int main() {
    test1();
    return 0;
}
