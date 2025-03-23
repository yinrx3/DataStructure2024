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

template <class T>
struct graphNode{
    T data;
    VecList<graphNode<T>*>* ins;
    VecList<graphNode<T>*>* outs;
};

template <class T>
class LGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer;
        VecList<graphNode<T>*> verList;
        bool directed;
        
        int findIndex(T x){
            for(int i=0;i<numVer;i++){
                if(verList.getEleAtPos(i)->data == x)
                    return i;
            }
            return -1;
        }
        
        void BFShelper(int st, bool* visited){
        	visited[st] = true;
        	LinkQueue<int> q;
        	q.enQueue(st);
        	cout << verList.getEleAtPos(st)->data << " ";
        	while(!q.isEmpty()){
        	    int tmp = q.deQueue();
        	    graphNode<T>* tmpNode = verList.getEleAtPos(tmp);
        	    for(int j=0;j<tmpNode->outs->getLength();j++){
        	        int target = verList.locateEle(tmpNode->outs->getEleAtPos(j));
        	        if(visited[target]) continue;
        	        visited[target] = true;
        	        cout << verList.getEleAtPos(target)->data << " ";
        	        q.enQueue(target);
        	    }
        	}
		}
		
		void DFShelper(int st, bool* visited){
			visited[st] = true;
			graphNode<T>* tmpNode = verList.getEleAtPos(st);
			cout << verList.getEleAtPos(st)->data << " ";
			for(int j=0;j<tmpNode->outs->getLength();j++){
			    int target = verList.locateEle(tmpNode->outs->getEleAtPos(j));
			    if(visited[target]) continue;
			    DFShelper(target,visited);
			}
		}
		
    public:
        LGraph(){ // we don't want this used.
        }
        LGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.
            
            numVer = 0;
            directed = dir;
            for(int i=0;i<n;i++){
                addVertex(arr[i]);
            }
        }
        LGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added now. 
            
            numVer = 0;
            directed = dir;
            for(int i=0;i<n;i++){
                addVertex(arr[i]);
            }
			
			for(int i=0;i<e;i++){
				addEdge(eArr[i]->start,eArr[i]->end);
			}
        }
        ~LGraph(){
            for(int i=0;i<numVer;i++){
                delete verList.getEleAtPos(i)->ins;
                delete verList.getEleAtPos(i)->outs;
                delete verList.getEleAtPos(i);
            }
        }
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end);
        }
        void addEdge(T st, T en){
            int sIndex = findIndex(st);
            int eIndex = findIndex(en);
            graphNode<T>* sNode = verList.getEleAtPos(sIndex);
            graphNode<T>* eNode = verList.getEleAtPos(eIndex);
            if(sNode->outs->locateEle(eNode)==-1)
                sNode->outs->insertLast(eNode);
            if(eNode->ins->locateEle(sNode)==-1)
                eNode->ins->insertLast(sNode);
            if(!directed){
                if(eNode->outs->locateEle(sNode)==-1)
                    eNode->outs->insertLast(sNode);
                if(sNode->ins->locateEle(eNode)==-1)
                    sNode->ins->insertLast(eNode);
            }
        }
        void removeEdge(Edge<T> e){
            removeEdge(e.start,e.end);            
        }
        void removeEdge(T st, T en){
            int sIndex = findIndex(st);
            int eIndex = findIndex(en);
            graphNode<T>* sNode = verList.getEleAtPos(sIndex);
            graphNode<T>* eNode = verList.getEleAtPos(eIndex);
            if(sNode->outs->locateEle(eNode)!=-1)
                sNode->outs->deleteEleAtPos(sNode->outs->locateEle(eNode));
            if(eNode->ins->locateEle(sNode)!=-1)
                eNode->ins->deleteEleAtPos(eNode->ins->locateEle(sNode));
            if(!directed){
                if(eNode->outs->locateEle(sNode)!=-1)
                    eNode->outs->deleteEleAtPos(eNode->outs->locateEle(sNode));
                if(sNode->ins->locateEle(eNode)!=-1)
                    sNode->ins->deleteEleAtPos(sNode->ins->locateEle(eNode));
            }
        }
        
        void addVertex(T x){
            numVer++;
            graphNode<T>* tmpNode = new graphNode<T>;
            tmpNode->data = x;
            tmpNode->ins = new VecList<graphNode<T>*>;
            tmpNode->outs = new VecList<graphNode<T>*>;
            verList.insertLast(tmpNode);
        }
        
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.getEleAtPos(i)->data << " ";
            cout << endl << "Edges:" << endl;
            char sLeft = (directed ? '<' : '(');
            char sRight = (directed ? '>' : ')');
            for(int i=0;i<numVer;i++){
                graphNode<T>* tmpNode = verList.getEleAtPos(i);
                for(int j=(directed ? 0 : i+1);j<numVer;j++){
                    graphNode<T>* targetNode = verList.getEleAtPos(j);
                    if(tmpNode->outs->locateEle(targetNode)!=-1)
                        cout << sLeft << tmpNode->data << "," << targetNode->data << sRight << endl;
                }
            }
        }
        int** getMatrix(){
            int** adjMatrix;
            adjMatrix = new int*[numVer];
            for(int i=0;i<numVer;i++){
                adjMatrix[i] = new int[numVer];
                for(int j=0;j<numVer;j++){
                    if(verList.getEleAtPos(i)->outs->locateEle(verList.getEleAtPos(j))!=-1)
                        adjMatrix[i][j] = 1;
                    else
                        adjMatrix[i][j] = 0;
                }
            }
            return adjMatrix;
        }
        //BFS
        void printBFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
                visited[i] = false;
            for(int i=0;i<numVer;i++)
                if(!visited[i])
                    BFShelper(i,visited);
            cout << endl;
        }
        //DFS
        void printDFS(){
            bool visited[numVer];
            for(int i=0;i<numVer;i++)
                visited[i] = false;
            for(int i=0;i<numVer;i++)
                if(!visited[i])
                    DFShelper(i,visited);
            cout << endl;
        }
};

void printMatrix(int ** mat, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << setw(7) << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void test0(){
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
    
    LGraph<int> amg1(ver,9,edges,10);
    LGraph<int> amg2(ver,9,edges,10,true);
    
    amg1.addEdge(7,3);
    amg1.addEdge(7,4);
    
    amg2.addEdge(3,7);
    amg2.addEdge(7,9);
    amg2.removeEdge(6,8);
    amg2.addVertex(10);
    amg2.addEdge(10,5);
    amg2.addVertex(11);
    amg2.addEdge(5,11);
    
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
    printMatrix(amg2.getMatrix(),11);
    cout << "BFS:" << endl;
    amg2.printBFS();
    cout << "DFS:" << endl;
    amg2.printDFS();
    
}

int main(){
    test0();
    return 0;
}
