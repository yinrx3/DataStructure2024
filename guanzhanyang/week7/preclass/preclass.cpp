#include <iostream>


template<class T>
class BinTree{
    private:
    T data;
    BinTree<T>* left;
    BinTree<T>* right;
    public:
    BinTree(){
        left=nullptr;
        right=nullptr;
    }
    BinTree(T x){
        data=x;
        left=nullptr;
        right=nullptr;
    }
    ~BinTree(){}
    void addLChild(BinTree<T>* bt){
        left=bt;
    }
    void addLChild(T x){
        BinTree<T>* newTree=now BinTree<T>(x);
        addLChild(newTree);
    }
    void addRChild(BinTree<T>* bt){
        right=bt;
    }
    void addRChild(T x){
        BinTree<T>* newTree=now BinTree<T>(x);
        addRChild(newTree);
    }
    void printPreOrderR(){
        cout<<data;
        if(left!=nullptr){left->printPreOrderR;}
        if(right!=nullptr){right->printPreOrderR;}
    }
    void printPostOrder(){
        if(right!=nullptr){right->printPreOrderR;}
        if(left!=nullptr){left->printPreOrderR;}
        cout<<data<<" ";
    }
    void printInOrder(){
        if(right!=nullptr){right->printPreOrderR;}
        cout<<data<<" ";
        if(left!=nullptr){left->printPreOrderR;}
    }
    void printLevelOrder(){
        
    }
};