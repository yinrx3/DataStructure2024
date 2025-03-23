#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode* next;
    ListNode():val(0),next(nullptr){};
    ListNode(int x):val(x),next(nullptr){};
    ListNode(int x,ListNode* next):val(x),next(next){};
};
//定义了一个结构体，实际上是定义了一个类
