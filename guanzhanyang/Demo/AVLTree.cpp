#include <iostream>
using namespace std;

template <class T>
class VecList{
    private:
        int capacity;
        int length;
        T* arr;
        void doubleListSize(){
            T * oldArr = arr;
            arr = new T[2*capacity];
            capacity = 2 * capacity;
            for(int i=0;i<length;i++){
                arr[i] = oldArr[i];
            }
            delete [] oldArr;
        }
    public:
        VecList(){
            length = 0;
            capacity = 100;
            arr = new T[capacity];
        }
        VecList(T* a, int n){
            length = n;
            capacity = 100 + 2*n;
            arr = new T[capacity];
            for(int i=0;i<n;i++){
                arr[i] = a[i];
            }
        }
        ~VecList(){
            delete [] arr;
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void insertEleAtPos(int i, T x){
            if(length==capacity)
                doubleListSize();
            if(i > length || i < 0)
                throw "Illegal position";
            for(int j=length;j>i;j--)
                arr[j] = arr[j-1];
            arr[i] = x;
            length++;
        }
        T deleteEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            T tmp = arr[i];
            for(int j=i;j<length-1;j++)
                arr[j] = arr[j+1];
            length--;
            return tmp;
        }
        void setEleAtPos(int i, T x){
            if(i >= length || i < 0)
                throw "Illegal position";
            arr[i] = x;
        }
        T getEleAtPos(int i){
            if(i >= length || i < 0)
                throw "Illegal position";
            return arr[i];
        }
        int locateEle(T x){
            for(int i=0;i<length;i++){
                if(arr[i]==x)
                    return i;
            }
            return -1;
        }
        void printList(){
            for(int i=0;i<length;i++)
                cout << arr[i] << " ";
        }
};

template <class T>
struct DNode{
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack{
    private:
        DNode<T>* top;
        int length;
    public:
        LinkStack(){
            top = NULL;
            length = 0;
        }
        ~LinkStack(){
            while(top!=NULL){
                DNode<T>* tmp = top;
                top = top->next;
                delete tmp;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void push(T x){
            DNode<T>* tmp = new DNode<T>;
            tmp->data = x;
            tmp->next = top;
            top = tmp;
            length++;
        }
        T pop(){
            if(length==0) throw "Stack Empty!";
            DNode<T>* tmp = top;
            top = top->next;
            T tmpData = tmp->data;
            delete tmp;
            length--;
            return tmpData;
        }
        T getTop(){
            if(length==0) throw "Stack Empty!";
            return top->data;
        }
        void printStack(){
            cout << "Stack top: ";
            DNode<T>* tmp = top;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ":stack bottom" << endl;
        }
};

template <class T>
class LinkQueue{
    private:
        DNode<T>* front;
        DNode<T>* back;
        int length;
    public:
        LinkQueue(){
            front = new DNode<T>;
            front->next = NULL;
            back = front;
            length = 0;
        }
        ~LinkQueue(){
            while(front!=NULL){
                back = front;
                front = front->next;
                delete back;
            }
        }
        int getLength(){
            return length;
        }
        bool isEmpty(){
            return length==0;
        }
        void enQueue(T x){
            DNode<T>* tmpN = new DNode<T>;
            tmpN->data = x;
            tmpN->next = NULL;
            back->next = tmpN;
            back = tmpN;
            length++;
        }
        T deQueue(){
            if(length==0) throw "Queue Empty!";
            DNode<T>* tmpN = front->next;
            front->next = tmpN->next;
            T tmpD = tmpN->data;
            delete tmpN;
            length--;
            if(length==0) back = front;
            return tmpD;
        }
        T peekQueue(){
            if(length==0) throw "Queue Empty!";
            return front->next->data;
        }
        void printQueue(){
            cout << "Front of queue: ";
            DNode<T>* tmp = front->next;
            while(tmp!=NULL){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << ": back of queue" << endl;
        }
};

template <class T>
class BinTree{
    private:
        T data;
        BinTree<T>* left;
        BinTree<T>* right;
        BinTree<T>* parent;
        int height;
        void updateHeights(){
            int hL = (left==NULL ? 0 : left->height);
            int hR = (right==NULL ? 0 : right->height);
            height = (hL > hR ? hL : hR) + 1;
            if(parent!=NULL)
                parent->updateHeights();
        }
    public:
        BinTree(){
            left = NULL;
            right = NULL;
            parent = NULL;
            height = 1;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
            parent = NULL;
            height = 1;
        }
        ~BinTree(){
            
        }
        void addLChild(BinTree<T>* bt){
            left = bt;
            updateHeights();
            if(bt==NULL) return;
            bt->parent = this;
        }
        void addLChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
            updateHeights();
            if(bt==NULL) return;
            bt->parent = this;
        }
        void addRChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addRChild(bt);
        }
        T getData(){
            return data;
        }
        void setData(T x){
            data = x;
        }
        int getHeight(){
            return height;
        }
        BinTree<T>* getLChild(){
            return left;
        }
        BinTree<T>* getRChild(){
            return right;
        }
        BinTree<T>* getParent(){
            return parent;
        }
        void setParent(BinTree<T>* bt){
            parent = bt;
        }
        void printPreOrderR(){
            cout << data << " ";
            if(left!=NULL) left->printPreOrderR();
            if(right!=NULL) right->printPreOrderR();
        }
        void printPostOrderR(){
            if(left!=NULL) left->printPostOrderR();
            if(right!=NULL) right->printPostOrderR();
            cout << data << " ";
        }
        void printInOrderR(){
            if(left!=NULL) left->printInOrderR();
            cout << data << " ";
            if(right!=NULL) right->printInOrderR();
        }
        void printLevelOrder(){
            LinkQueue<BinTree<T> *> q;
            q.enQueue(this);
            while(!q.isEmpty()){
                BinTree<T>* tmpN = q.deQueue();
                cout << tmpN->data << " ";
                if(tmpN->left!=NULL) q.enQueue(tmpN->left);
                if(tmpN->right!=NULL) q.enQueue(tmpN->right);
            }
        }
};

template <class T>
class AVLTree{
    // T better have its comparison operators overloaded.
    // we assume no duplicate elements
    // use an empty root node
    private:
        BinTree<T>* root;
        int nodeCount;
        
        BinTree<T>* findParent(T x){
            if(nodeCount==0){
                return NULL;
            }
            BinTree<T>* bt = root->getRChild();
            BinTree<T>* btParent = bt->getParent();
            while(bt!=NULL){
                if(bt->getData()==x){
                    return bt->getParent();
                }
                else if(bt->getData() > x){
                    btParent = bt;
                    bt = bt->getLChild();
                }
                else{
                    btParent = bt;
                    bt = bt->getRChild();
                }
            }
            return btParent;
        }
        
        void rotateLeft(BinTree<T>* bt){
            if(bt->getParent()->getLChild()==bt){
                BinTree<T>* btP = bt->getParent();
                bt->setParent(NULL);
                BinTree<T>* btB = bt->getRChild();
                btB->setParent(NULL);
                bt->addRChild(btB->getLChild());
                btB->addLChild(bt);
                btP->addLChild(btB);
            }
            else{
                BinTree<T>* btP = bt->getParent();
                bt->setParent(NULL);
                BinTree<T>* btB = bt->getRChild();
                btB->setParent(NULL);
                bt->addRChild(btB->getLChild());
                btB->addLChild(bt);
                btP->addRChild(btB);
            }
        }
        
        void rotateRight(BinTree<T>* bt){
            if(bt->getParent()->getLChild()==bt){
                BinTree<T>* btP = bt->getParent();
                bt->setParent(NULL);
                BinTree<T>* btB = bt->getLChild();
                btB->setParent(NULL);
                bt->addLChild(btB->getRChild());
                btB->addRChild(bt);
                btP->addLChild(btB);
            }
            else{
                BinTree<T>* btP = bt->getParent();
                bt->setParent(NULL);
                BinTree<T>* btB = bt->getLChild();
                btB->setParent(NULL);
                bt->addLChild(btB->getRChild());
                btB->addRChild(bt);
                btP->addRChild(btB);
            }
        }
        
        void balanceTree(BinTree<T>* bt){
            if(bt==root) return;
            int hL = (bt->getLChild()==NULL ? 0 : bt->getLChild()->getHeight());
            int hR = (bt->getRChild()==NULL ? 0 : bt->getRChild()->getHeight());
            if(hL - hR >= 2){
                BinTree<T>* btL = bt->getLChild();
                int hLL = (btL->getLChild()==NULL ? 0 : btL->getLChild()->getHeight());
                int hLR = (btL->getRChild()==NULL ? 0 : btL->getRChild()->getHeight());
                if(hLL >= hLR){
                    // LL type
                    rotateRight(bt);
                }
                else{
                    rotateLeft(btL);
                    rotateRight(bt);
                }
            }
            else if(hR - hL >= 2){
                BinTree<T>* btR = bt->getRChild();
                int hRL = (btR->getLChild()==NULL ? 0 : btR->getLChild()->getHeight());
                int hRR = (btR->getRChild()==NULL ? 0 : btR->getRChild()->getHeight());
                if(hRR >= hRL){
                    // RR type
                    rotateLeft(bt);
                }
                else{
                    rotateRight(btR);
                    rotateLeft(bt);
                }
            }
            if(bt->getParent()!=NULL)
                balanceTree(bt->getParent());
        }
        
    public:
        AVLTree(){
            root = new BinTree<T>();
            nodeCount = 0;
        }
        
        AVLTree(T* arr, int n){ // insert whole array
            root = new BinTree<T>();
            nodeCount = 0;
            if(n==0) return;
            for(int i=0;i<n;i++){
                insertData(arr[i]);
            }
        }
        ~AVLTree(){
            // LinkQueue destroying every node
            LinkQueue<BinTree<T>*> q;
            q.enQueue(root);
            while(!q.isEmpty()){
                BinTree<T>* bt = q.deQueue();
                if(bt->getLChild()!=NULL) q.enQueue(bt->getLChild());
                if(bt->getRChild()!=NULL) q.enQueue(bt->getRChild());
                delete bt;
            }
        }
        bool isEmpty(){
            return nodeCount==0;
        }
        void insertData(T x){
            if(nodeCount==0){
                nodeCount++;
                root->addRChild(x);
                return;
            }
            if(searchData(x)) return;
            BinTree<T>* btP = findParent(x);
            if(btP->getData()<x) btP->addRChild(x);
            if(btP->getData()>x) btP->addLChild(x);
            nodeCount++;
            balanceTree(btP);
        }
        bool searchData(T x){
            if(nodeCount==0) return false;
            BinTree<T>* btP = findParent(x);
            if(btP==root) return true;
            if(btP->getData()<x) return (btP->getRChild()!=NULL);
            if(btP->getData()>x) return (btP->getLChild()!=NULL);
        }
        bool deleteData(T x){
            if(nodeCount==0) return false;
            if(!searchData(x)) return false;
            // there is a thing to delete
            BinTree<T>* btP = findParent(x);
            if(btP == root){
                btP = btP->getRChild();
            }
            else{
                if(btP->getData()<x) btP = btP->getRChild();
                else if(btP->getData()>x) btP = btP->getLChild();
            }
            // this is the node to delete.
            // we will find the number that's barely smaller than btP's number.
            
            // only right child exists
            if(btP->getLChild()==NULL){
                if(btP->getParent()->getLChild()==btP){
                    btP->getParent()->addLChild(btP->getRChild());
                }
                else{
                    btP->getParent()->addRChild(btP->getRChild());
                }
                balanceTree(btP->getParent());
                delete btP;
            }
            else{
                BinTree<T>* btS = btP->getLChild();
                while(btS->getRChild()!=NULL){
                    btS = btS->getRChild();
                }
                btP->setData(btS->getData());
                if(btS->getParent()==btP) btP->addLChild(btS->getLChild());
                else btS->getParent()->addRChild(btS->getLChild());
                balanceTree(btS->getParent());
                delete btS;
            }
            
            nodeCount--;
            return true;
        }
        void printInOrder(){
            cout << "In Order: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printInOrderR();
            cout << endl;
        }
        void printPreOrder(){
            cout << "PreOrder: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printPreOrderR();
            cout << endl;
        }
        void printPostOrder(){
            cout << "Post Order: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printPostOrderR();
            cout << endl;
        }
        
        void printLevelOrder(){
            cout << "Level Order: ";
            if(root->getRChild()!=NULL)
                root->getRChild()->printLevelOrder();
            cout << endl;
        }
};

void test0(){
    AVLTree<int> bst;
    bst.insertData(8);
    bst.insertData(3);
    bst.insertData(10);
    bst.insertData(1);
    bst.insertData(6);
    bst.insertData(4);
    bst.insertData(7);
    bst.insertData(14);
    bst.insertData(13);
    // print preorder and inorder, for uniquely looking at this BST.
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
    
    cout << "Remove 1:" << endl;
    bst.deleteData(1);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
    
    cout << "Remove 14:" << endl;
    bst.deleteData(14);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
    
    cout << "Remove 8:" << endl;
    bst.deleteData(8);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
}

void test1(){
    int a[3] = {1,2,3};
    AVLTree<int> bst(a,3);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
    
    cout << "Remove all: " << endl;
    bst.deleteData(4);
    bst.deleteData(1);
    bst.deleteData(2);
    bst.deleteData(3);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
    cout << "Insert again: " << endl;
    for(int i=1;i<=7;i++){
        bst.insertData(i);
    }
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
}

int main(){
    test0();
    test1();
    return 0;
}