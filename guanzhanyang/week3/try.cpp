#include <iostream>
using namespace std;
template <class T>
class LinkList
{
    private:
    int length;
    DNode<T>* head;
    public:
    LinkList()
    {
        length=0;
        head=new DNode<T>;
        head->next=nullptr;
    }
    LinkList(T* a, int n)
    {
        length=n;
        head=new DNode<T>;
        
    }
};