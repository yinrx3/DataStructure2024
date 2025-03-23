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

/* UPLOAD START */

template <class T>
class BinarySearchTree{
    // T better have its comparison operators overloaded.
    // we assume no duplicate elements
    // use an empty root node
    private:
        BinTree<T>* root;
        int nodeCount;
        
        //这里实际上初始化当前节点 bt 为根节点的右子节点（假设根节点是空节点，实际数据从根的右子节点开始）。
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

        int countNodes(BinTree<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->getLChild()) + countNodes(node->getRChild());
    }

    // Helper function to calculate the number of ways to arrange the BST
    long long countWays(BinTree<T>* node, int mod_num) {
        if (node == nullptr) return 1;

        int leftCount = countNodes(node->getLChild());
        int rightCount = countNodes(node->getRChild());

        // Calculate the number of ways to arrange the left and right subtrees
        long long leftWays = countWays(node->getLChild(), mod_num);
        long long rightWays = countWays(node->getRChild(), mod_num);

        // Calculate the combination C(leftCount + rightCount, leftCount)
        long long combination = 1;
        for (int i = 1; i <= leftCount; ++i) {
            combination = (combination * (leftCount + rightCount - i + 1)) % mod_num;
            combination = (combination * modInverse(i, mod_num)) % mod_num;
        }

        // Total ways is the product of combination, leftWays, and rightWays
        long long totalWays = (combination * leftWays) % mod_num;
        totalWays = (totalWays * rightWays) % mod_num;

        return totalWays;
    }

    // Helper function to calculate the modular inverse
    long long modInverse(long long a, long long m) {
        long long m0 = m, t, q;
        long long x0 = 0, x1 = 1;
        if (m == 1) return 0;
        while (a > 1) {
            q = a / m;
            t = m;
            m = a % m;
            a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }
        
    public:
        BinarySearchTree(){
            root = new BinTree<T>();
            nodeCount = 0;
        }//这里用到了头空结点，类似于链表中的头空结点
        
        BinarySearchTree(T* arr, int n){ // insert whole array
            root = new BinTree<T>();
            nodeCount = 0;
            if(n==0) return;
            for(int i=0;i<n;i++){
                insertData(arr[i]);
            }
        }
        ~BinarySearchTree(){
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
        
        int numWaysToGetBST(int mod_num) {
            return countWays(root, mod_num);
    }
};

/* UPLOAD END */

void test1(){
    BinarySearchTree<int> bst;
    bst.insertData(4);
    bst.insertData(2);
    bst.insertData(1);
    bst.insertData(3);
    bst.insertData(6);
    bst.insertData(5);
    bst.insertData(7);
    cout << bst.numWaysToGetBST(10007) << endl; //80
    
    bst.insertData(10);
    bst.insertData(8);
    cout << bst.numWaysToGetBST(10007) << endl; //448
}

int main(){
    test1();
    return 0;
}