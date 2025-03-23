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
    public:
        BinTree(){
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        BinTree(T x){
            data = x;
            left = NULL;
            right = NULL;
            parent = NULL;
        }
        ~BinTree(){

        }
        void addLChild(BinTree<T>* bt){
            left = bt;
            if(bt==NULL) return;
            bt->parent = this;
        }
        void addLChild(T x){
            BinTree<T>* bt = new BinTree<T>(x);
            addLChild(bt);
        }
        void addRChild(BinTree<T>* bt){
            right = bt;
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
class BinarySearchTree{
    // T better have its comparison operators overloaded.
    // we assume no duplicate elements
    // use an empty root node
    private:
        BinTree<T>* root;
        int nodeCount;

        BinTree<T>* findParent(T x){
            BinTree<T>* btP = root;
            BinTree<T>* bt = root->getRChild();
            if(nodeCount==0){
                return root;
            }
            while(bt!=NULL){
                if(bt->getData()==x) return btP;
                if(bt->getData() > x){
                    btP = bt;
                    bt = bt->getLChild();
                }
                else{
                    btP = bt;
                    bt = bt->getRChild();
                }
            }
            return btP;
        }
    public:
        BinarySearchTree(){
            root = new BinTree<T>;
            nodeCount = 0;
        }

        BinarySearchTree(T* arr, int n){ // insert whole array
            root = new BinTree<T>;
            nodeCount = 0;
            for(int i=0;i<n;i++){
                insertData(arr[i]);
            }
        }
        ~BinarySearchTree(){
            LinkQueue<BinTree<T>*> q;
            q.enQueue(root);
            while(!q.isEmpty()){
                BinTree<T>* tmp = q.deQueue();
                if(tmp->getLChild()!=NULL) q.enQueue(tmp->getLChild());
                if(tmp->getRChild()!=NULL) q.enQueue(tmp->getRChild());
                delete tmp;
            }
        }
        bool isEmpty(){
            return nodeCount==0;
        }
        void insertData(T x){
            BinTree<T>* btP = findParent(x);
            if(nodeCount==0){
                root->addRChild(x);
                nodeCount++;
                return;
            }
            if(btP->getData() < x){
                if(btP->getRChild()==NULL){
                    btP->addRChild(x);
                    nodeCount++;
                }
            }
            else{
                if(btP->getLChild()==NULL){
                    btP->addLChild(x);
                    nodeCount++;
                }
            }
        }
        bool searchData(T x){
            if(nodeCount==0) return false;
            BinTree<T>* btP = findParent(x);
            if(btP==root){
                return btP->getRChild()->getData()==x;
            }
            if(btP->getData() < x){
                if(btP->getRChild()==NULL) return false;
                if(btP->getRChild()->getData()==x) return true;
                else return false;
            }
            else{
                if(btP->getLChild()==NULL) return false;
                if(btP->getLChild()->getData()==x) return true;
                else return false;
            }
        }
        bool deleteData(T x){
            if(nodeCount==0) return false;
            if(!searchData(x)) return false;

            BinTree<T>* btP = findParent(x);
            BinTree<T>* bt = (btP->getData() < x ? btP->getRChild() : btP->getLChild());
            if(btP==root) bt = root->getRChild();
            if(bt->getLChild()==NULL && bt->getRChild()==NULL){
                if(root==btP || btP->getData()<x){
                    BinTree<T>* btNULL = NULL;
                    btP->addRChild(btNULL);
                    nodeCount--;
                }
                else{
                    BinTree<T>* btNULL = NULL;
                    btP->addLChild(btNULL);
                    nodeCount--;
                }
                delete bt;
            }
            else if(bt->getLChild()==NULL && bt->getRChild()!=NULL){
                if(root==btP || btP->getData() < x){
                    btP->addRChild(bt->getRChild());
                    nodeCount--;
                }
                else{
                    btP->addLChild(bt->getRChild());
                    nodeCount--;
                }
                delete bt;
            }
            else if(bt->getLChild()!=NULL && bt->getRChild()==NULL){
                if(root==btP || btP->getData() < x){
                    btP->addRChild(bt->getLChild());
                    nodeCount--;
                }
                else{
                    btP->addLChild(bt->getLChild());
                    nodeCount--;
                }
                delete bt;
            }
            else{
                BinTree<T>* btLeftBiggest = bt->getLChild();
                while(btLeftBiggest->getRChild()!=NULL){
                    btLeftBiggest = btLeftBiggest->getRChild();
                }
                BinTree<T>* btLeftBiggestParent = btLeftBiggest->getParent();
                T data = bt->getData();
                bt->setData(btLeftBiggest->getData());
                btLeftBiggest->setData(data);
                if(btLeftBiggestParent!=bt){
                    btLeftBiggestParent->addRChild(btLeftBiggest->getLChild());
                }
                else{
                    btLeftBiggestParent->addLChild(btLeftBiggest->getLChild());
                }
                delete btLeftBiggest;
                nodeCount--;
            }
            return true;
        }
        void printInOrder(){
            cout << "In order: ";
            if(root->getRChild()!=NULL) root->getRChild()->printInOrderR();
            cout << endl;
        }
        void printPreOrder(){
            cout << "Pre order: ";
            if(root->getRChild()!=NULL) root->getRChild()->printPreOrderR();
            cout << endl;
        }
        void printPostOrder(){
            cout << "Post order: ";
            if(root->getRChild()!=NULL) root->getRChild()->printPostOrderR();
            cout << endl;
        }

        void printLevelOrder(){
            cout << "Level order: ";
            if(root->getRChild()!=NULL) root->getRChild()->printLevelOrder();
            cout << endl;
        }
};

void test0(){
    BinarySearchTree<int> bst;
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

    cout << "Insert 9 and remove 10: " << endl;
    bst.insertData(9);
    bst.deleteData(10);
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
    BinarySearchTree<int> bst(a,3);
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
