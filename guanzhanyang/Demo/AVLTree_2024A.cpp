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
            int hL = (left!=NULL ? left->height : 0);
            int hR = (right!=NULL ? right->height : 0);
            height = (hL > hR ? hL : hR) + 1;
            if(parent!=NULL) parent->updateHeights();
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
        int getHeight(){
            return height;
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
            if(nodeCount==0) return root;
            BinTree<T>* btP = root;
            BinTree<T>* bt = root->getRChild();
            while(bt!=NULL){
                if(bt->getData()==x) return btP;
                if(bt->getData() < x){
                    btP = bt;
                    bt = bt->getRChild();
                }
                else{
                    btP = bt;
                    bt = bt->getLChild();
                }
            }
            return btP;
        }

        void rotateLeft(BinTree<T>* btA){
            BinTree<T>* btP = btA->getParent();
            BinTree<T>* btB = btA->getRChild();
            btB->setParent(NULL);
            btA->setParent(NULL);
            if(btP->getLChild()==btA){
                btA->addRChild(btB->getLChild());
                btB->addLChild(btA);
                btP->addLChild(btB);
            }
            else{
                btA->addRChild(btB->getLChild());
                btB->addLChild(btA);
                btP->addRChild(btB);
            }
        }

        void rotateRight(BinTree<T>* btA){
            BinTree<T>* btP = btA->getParent();
            BinTree<T>* btB = btA->getLChild();
            btB->setParent(NULL);
            btA->setParent(NULL);
            if(btP->getLChild()==btA){
                btA->addLChild(btB->getRChild());
                btB->addRChild(btA);
                btP->addLChild(btB);
            }
            else{
                btA->addLChild(btB->getRChild());
                btB->addRChild(btA);
                btP->addRChild(btB);
            }
        }

        void balanceTree(BinTree<T>* bt){
            if(bt==root) return;
            BinTree<T>* btP = bt->getParent();
            int hL = (bt->getLChild()!=NULL ? bt->getLChild()->getHeight() : 0);
            int hR = (bt->getRChild()!=NULL ? bt->getRChild()->getHeight() : 0);
            //cout << bt->getData() << " " << hL << " " << hR << endl;
            if(hL - hR >= 2){
                BinTree<T>* btL = bt->getLChild();
                int hLL = (btL->getLChild()!=NULL ? btL->getLChild()->getHeight() : 0);
                int hLR = (btL->getRChild()!=NULL ? btL->getRChild()->getHeight() : 0);
                if(hLL >= hLR){ // type LL
                    rotateRight(bt);
                }
                else{ // type LR
                    rotateLeft(bt->getLChild());
                    rotateRight(bt);
                }
            }
            else if(hL - hR <= -2){
                BinTree<T>* btR = bt->getRChild();
                int hRL = (btR->getLChild()!=NULL ? btR->getLChild()->getHeight() : 0);
                int hRR = (btR->getRChild()!=NULL ? btR->getRChild()->getHeight() : 0);
                if(hRR >= hRL){ // type RR
                    rotateLeft(bt);
                }
                else{ // type RL
                    rotateRight(bt->getRChild());
                    rotateLeft(bt);
                }
            }
            if(btP!=root){
                balanceTree(btP);
            }
        }

    public:
        AVLTree(){
            root = new BinTree<T>;
            nodeCount = 0;
        }

        AVLTree(T* arr, int n){ // insert whole array
            root = new BinTree<T>;
            nodeCount = 0;
            for(int i=0;i<n;i++){
                insertData(arr[i]);
            }
        }
        ~AVLTree(){
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
            if(btP == root || btP->getData() < x){
                if(btP->getRChild()==NULL){
                    nodeCount++;
                    btP->addRChild(x);
                    balanceTree(btP);
                }
            }
            else{
                if(btP->getLChild()==NULL){
                    nodeCount++;
                    btP->addLChild(x);
                    balanceTree(btP);
                }
            }
        }
        bool searchData(T x){
            if(nodeCount==0) return false;
            BinTree<T>* btP = findParent(x);
            if(btP == root || btP->getData() < x){
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
            BinTree<T>* bt = (btP->getData() > x ? btP->getLChild() : btP->getRChild());
            if(btP == root) bt = btP->getRChild();

            if(bt->getLChild()==NULL && bt->getRChild()==NULL){
                BinTree<T>* btNULL = NULL;
                if(btP->getLChild()==bt){
                    btP->addLChild(btNULL);
                }
                else{
                    btP->addRChild(btNULL);
                }
                balanceTree(btP);
                delete bt;
                nodeCount--;
            }
            else if(bt->getLChild()!=NULL && bt->getRChild()==NULL){
                if(btP->getLChild()==bt){
                    btP->addLChild(bt->getLChild());
                }
                else{
                    btP->addRChild(bt->getLChild());
                }
                balanceTree(btP);
                delete bt;
                nodeCount--;
            }
            else if(bt->getLChild()==NULL && bt->getRChild()!=NULL){
                if(btP->getLChild()==bt){
                    btP->addLChild(bt->getRChild());
                }
                else{
                    btP->addRChild(bt->getRChild());
                }
                balanceTree(btP);
                delete bt;
                nodeCount--;
            }
            else{
                BinTree<T>* btLeftLargest = bt->getLChild();
                while(btLeftLargest->getRChild()!=NULL){
                    btLeftLargest = btLeftLargest->getRChild();
                }
                T data = bt->getData();
                bt->setData(btLeftLargest->getData());
                btLeftLargest->setData(data);
                BinTree<T>* btLLP = btLeftLargest->getParent();
                if(btLLP!=bt){
                    btLLP->addRChild(btLeftLargest->getLChild());
                }
                else{
                    btLLP->addLChild(btLeftLargest->getLChild());
                }
                balanceTree(btLLP);
                delete btLeftLargest;
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
    AVLTree<int> bst;
    bst.insertData(8);
    bst.insertData(3);
    bst.insertData(10);
    bst.insertData(1);
    bst.insertData(6);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
    bst.insertData(4);
    bst.printPreOrder();
    cout << endl;
    bst.printInOrder();
    cout << endl;
    bst.printLevelOrder();
    cout << endl << endl;
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
