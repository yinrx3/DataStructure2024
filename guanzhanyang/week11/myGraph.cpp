#include <iostream>
#include <iomanip>
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
        void insertLast(T x){
            insertEleAtPos(length,x);
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
struct Edge{
    T start;
    T end;
};

template<class T>
class AMGraph{
    private:
        int numVer,numEdge;
        VecList<T> verList;//存储所有结点的名字的向量表
        int** adjMatrix;
        bool directed;

        void printBFShelp(int vInd,bool* visited){
            LinkQueue<int> q;//这里传入进来的vInd是目前正在处理的节点所对应的位序
            q.enQueue(vInd);
            cout<<verList.getEleAtPos(vInd)<<" ";
            visited[vInd]=true;//表示已经被访问过了
            while(!q.isEmpty()){
                int temp=q.deQueue();
                for(int i=0;i<numVer;++i){
                    if(adjMatrix[temp][i]==1&&!visited[i]){
                        cout<<verList.getEleAtPos(i)<<" ";
                        visited[i]=true;
                        q.enQueue(i);
                    }
                }
            }
        }

        void printDFShelp(int vInd,bool* visited){
            cout<<verList.getEleAtPos(vInd)<<" ";
            visited[vInd]=true;
            for(int i=0;i<numVer;++i){
                if(adjMatrix[vInd][i]==1&&!visited[i]){
                    printDFShelp(i,visited);
                }
            }
        }
    public:
        AMGraph(){}//默认初始化函数
        AMGraph(T* arr,int n,bool dir=false)
        {
            //这里T* arr指的是所有结点名字的向量表
            //首先要给这里的邻接矩阵分配空间
            adjMatrix=new int*[n];
            for(int i=0;i<n;++i){
                adjMatrix[i]=new int[n];
            }
            //以上就已经给邻接矩阵分配好了空间
            directed=dir;
            numVer=n;
            numEdge=0;
            //这里实际上初始化的是有n个结点的孤立图
            //下面要把结点的名字复制到向量表里面
            for(int i=0;i<n;++i){
                verList.insertLast(arr[i]);
                for(int j=0;j<n;++j){
                    adjMatrix[i][j]=0;//因为是只有n个结点的孤立图
                }
            }
        }
        //下面是根据点的集合和边的集合
        AMGraph(T* arr,int n,Edge<T>** eArr,int e,bool dir=false){
            //这里需要说明的是Edge<T>** eArr是指针的数组
            adjMatrix=new int*[n];
            for(int i=0;i<n;++i){
                adjMatrix[i]=new int[n];
            }
            //上面就给邻接矩阵分配好了空间
            directed = dir;
            numVer = n;
            numEdge = e;
            //复制几个参数

            for(int i=0;i<n;++i){
                verList.insertLast(arr[i]);
                for(int j=0;j<n;++j){
                    adjMatrix[i][j]=0;
                }
            }
            //先复制所有的结点然后邻接矩阵初始化为0
            //下面根据边的集合将邻接矩阵相应地地方改成1
            for(int i=0;i<e;++e){
                int sIndex=verList.locateEle(eArr[i]->start);
                int eIndex=verList.locateEle(eArr[i]->end);
                adjMatrix[sIndex][eIndex]=1;
                if(!directed) adjMatrix[eIndex][sIndex]=1;
            }
        }
        ~AMGraph(){
            for(int i=0;i<numVer;++i){
                delete[] adjMatrix[i];
            }
            delete[] adjMatrix;
        }
        //下面要实现两个加边操作
        void addEdge(Edge<T> e){
            int sIndex=verList.locateEle(e.start);
            int eIndex=verList.locateEle(e.end);
            if(adjMatrix[sIndex][eIndex]==0) ++numEdge;
            adjMatrix[sIndex][eIndex]=1;
            if(!directed) adjMatrix[sIndex][eIndex]=1;

        }
        void addEdge(T st,T en){
            int sIndex=verList.locateEle(st);
            int eIndex=verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]==0) ++numEdge;
            adjMatrix[sIndex][eIndex]=1;
            if(!directed) adjMatrix[sIndex][eIndex]=1;
        }
        void removeEdge(Edge<T> e){
            int sIndex=verList.locateEle(e.start);
            int eIndex=verList.locateEle(e.end);
            if(adjMatrix[sIndex][eIndex]==1) --numVer;
            adjMatrix[sIndex][eIndex]=0;
            if(!directed) adjMatrix[eIndex][sIndex]=0;
        }
        void removeEdge(T st,T en){
            int sIndex=verList.locateEle(st);
            int eIndex=verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]==1) --numVer;
            adjMatrix[sIndex][eIndex]=0;
            if(!directed) adjMatrix[eIndex][sIndex]=0;
        }
        void printGraph(){
            cout<<"Vertices:"<<endl;
            for(int i=0;i<numVer;++i){
                cout<<verList.getEleAtPos(i)<<" ";
            }
            cout<<endl;
            cout<<"Edges:"<<endl;
            char sLeft=(directed?'<':'(');
            char sRight=(directed?'>':')');
            for(int i=0;i<numVer;++i){
                for(int j=i+1;j<numVer;++j){
                    if(adjMatrix[i][j]==1){
                        cout<<sLeft<<verList.getEleAtPos(i)<<','<<verList.getEleAtPos(j)<<sRight<<endl;
                    }
                }
            }
            if(!directed) return ;
            for(int i=0;i<numVer;++i){
                for(int j=0;j<i;++j){
                    if(adjMatrix[i][j]==1){
                        cout<<sLeft<<verList.getEleAtPos(i)<<','<<verList.getEleAtPos(j)<<sRight<<endl;
                    }
                }
            }
        }
        int** getMatrix(){
            return adjMatrix;
        }
        //下面是广度优先搜索，也就是遍历BFS
        void printBFS(){
            bool* visited=new bool[numVer];
            for(int i=0;i<numVer;++i){
                visited[i]=false;
            }
            for(int i=0;i<numVer;++i){
                if(!visited[i]) printBFShelp(i,visited);
            }
            cout<<endl;
        }
        //下面是深度优先搜索
        void printDFS(){
            bool* visited=new bool[numVer];
            for(int i=0;i<numVer;++i){
                visited[i]=false;
            }
            for(int i=0;i<numVer;++i){
                if(!visited[i]) printDFShelp(i,visited);
            }
            cout<<endl;
        }
};


// put something that multiplies matrix, just for demonstrating meaning of A^k
// another that multiplies matrix.
void printMatrix(int ** mat, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << setw(7) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// multiply 2 square matrices
int** mulMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = 0;
            for(int k=0;k<n;k++){
                tmp[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return tmp;
}

int** addMatrix(int ** mat1, int ** mat2, int n){
    int** tmp = new int*[n];
    for(int i=0;i<n;i++){
        tmp[i] = new int[n];
        for(int j=0;j<n;j++){
            tmp[i][j] = mat1[i][j]+mat2[i][j];
        }
    }
    return tmp;
}

int main(){
    int ver[9] = {1,2,3,4,5,6,7,8,9};
    Edge<int>* edges[10];
    edges[0] = new Edge<int>{1,2};
    edges[1] = new Edge<int>{1,3};
    edges[2] = new Edge<int>{1,4};
    edges[3] = new Edge<int>{2,3};
    edges[4] = new Edge<int>{2,4};
    edges[5] = new Edge<int>{3,4};
    edges[6] = new Edge<int>{5,8};
    edges[7] = new Edge<int>{5,9};
    edges[8] = new Edge<int>{6,8};
    edges[9] = new Edge<int>{9,6};
    
    AMGraph<int> amg1(ver,9,edges,10);
    AMGraph<int> amg2(ver,9,edges,10,true);
    
    //amg1.addEdge(7,3);
    //amg1.addEdge(7,4);
    
    //amg2.addEdge(3,7);
    //amg2.addEdge(7,9);
    //amg2.removeEdge(6,8);
    
    cout << "Graph 1: " << endl;
    amg1.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg1.getMatrix(),9);
    cout << "BFS:" << endl;
    amg1.printBFS();
    cout << "DFS:" << endl;
    amg1.printDFS();
    
    cout << "Graph 2: " << endl;
    amg2.printGraph();
    cout << "Adjacency Matrix:" << endl;
    printMatrix(amg2.getMatrix(),9);
    cout << "BFS:" << endl;
    amg2.printBFS();
    cout << "DFS:" << endl;
    amg2.printDFS();
    
    cout << "Below is demonstration for powers of Adjacency matrix (for graph 1)" << endl;
    int** amg1_m1 = amg1.getMatrix();
    int** amg1_m2 = mulMatrix(amg1_m1,amg1_m1,9);
    int** amg1_m3 = mulMatrix(amg1_m1,amg1_m2,9);
    int** amg1_m4 = mulMatrix(amg1_m1,amg1_m3,9);
    int** amg1_m5 = mulMatrix(amg1_m1,amg1_m4,9);
    int** amg1_m6 = mulMatrix(amg1_m1,amg1_m5,9);
    int** amg1_m7 = mulMatrix(amg1_m1,amg1_m6,9);
    int** amg1_m8 = mulMatrix(amg1_m1,amg1_m7,9);
    int** amg1_m9 = mulMatrix(amg1_m1,amg1_m8,9);
    int** result = addMatrix(amg1_m1,amg1_m2,9);
    result = addMatrix(amg1_m3,result,9);
    result = addMatrix(amg1_m4,result,9);
    result = addMatrix(amg1_m5,result,9);
    result = addMatrix(amg1_m6,result,9);
    result = addMatrix(amg1_m7,result,9);
    result = addMatrix(amg1_m8,result,9);
    result = addMatrix(amg1_m9,result,9);
    printMatrix(result,9);
}
