#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
class VecList {
private:
    int capacity;
    int length;
    T* arr;
    void doubleListSize() {
        T* oldArr = arr;
        arr = new T[2 * capacity];
        capacity = 2 * capacity;
        for (int i = 0; i < length; i++) {
            arr[i] = oldArr[i];
        }
        delete[] oldArr;
    }
public:
    VecList() {
        length = 0;
        capacity = 100;
        arr = new T[capacity];
    }
    VecList(T* a, int n) {
        length = n;
        capacity = 100 + 2 * n;
        arr = new T[capacity];
        for (int i = 0; i < n; i++) {
            arr[i] = a[i];
        }
    }
    ~VecList() {
        delete[] arr;
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void insertEleAtPos(int i, T x) {
        if (length == capacity)
            doubleListSize();
        if (i > length || i < 0)
            throw "Illegal position";
        for (int j = length; j > i; j--)
            arr[j] = arr[j - 1];
        arr[i] = x;
        length++;
    }
    T deleteEleAtPos(int i) {
        if (i >= length || i < 0)
            throw "Illegal position";
        T tmp = arr[i];
        for (int j = i; j < length - 1; j++)
            arr[j] = arr[j + 1];
        length--;
        return tmp;
    }
    void setEleAtPos(int i, T x) {
        if (i >= length || i < 0)
            throw "Illegal position";
        arr[i] = x;
    }
    T getEleAtPos(int i) {
        if (i >= length || i < 0)
            throw "Illegal position";
        return arr[i];
    }
    int locateEle(T x) {
        for (int i = 0; i < length; i++) {
            if (arr[i] == x)
                return i;
        }
        return -1;
    }
    void insertLast(T x) {
        insertEleAtPos(length, x);
    }
    void printList() {
        for (int i = 0; i < length; i++)
            cout << arr[i] << " ";
    }
};

template <class T>
struct DNode {
    T data;
    DNode<T>* next;
};

template <class T>
class LinkStack {
private:
    DNode<T>* top;
    int length;
public:
    LinkStack() {
        top = NULL;
        length = 0;
    }
    ~LinkStack() {
        while (top != NULL) {
            DNode<T>* tmp = top;
            top = top->next;
            delete tmp;
        }
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void push(T x) {
        DNode<T>* tmp = new DNode<T>;
        tmp->data = x;
        tmp->next = top;
        top = tmp;
        length++;
    }
    T pop() {
        if (length == 0) throw "Stack Empty!";
        DNode<T>* tmp = top;
        top = top->next;
        T tmpData = tmp->data;
        delete tmp;
        length--;
        return tmpData;
    }
    T getTop() {
        if (length == 0) throw "Stack Empty!";
        return top->data;
    }
    void printStack() {
        cout << "Stack top: ";
        DNode<T>* tmp = top;
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << ":stack bottom" << endl;
    }
};

template <class T>
class LinkQueue {
private:
    DNode<T>* front;
    DNode<T>* back;
    int length;
public:
    LinkQueue() {
        front = new DNode<T>;
        front->next = NULL;
        back = front;
        length = 0;
    }
    ~LinkQueue() {
        while (front != NULL) {
            back = front;
            front = front->next;
            delete back;
        }
    }
    int getLength() {
        return length;
    }
    bool isEmpty() {
        return length == 0;
    }
    void enQueue(T x) {
        DNode<T>* tmpN = new DNode<T>;
        tmpN->data = x;
        tmpN->next = NULL;
        back->next = tmpN;
        back = tmpN;
        length++;
    }
    T deQueue() {
        if (length == 0) throw "Queue Empty!";
        DNode<T>* tmpN = front->next;
        front->next = tmpN->next;
        T tmpD = tmpN->data;
        delete tmpN;
        length--;
        if (length == 0) back = front;
        return tmpD;
    }
    T peekQueue() {
        if (length == 0) throw "Queue Empty!";
        return front->next->data;
    }
    void printQueue() {
        cout << "Front of queue: ";
        DNode<T>* tmp = front->next;
        while (tmp != NULL) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << ": back of queue" << endl;
    }
};

template <class T>
struct Edge {
    T start;
    T end;
};

/* UPLOAD START */

template <class T>
class AMGraph { //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
private:
    int numVer, numEdge;
    VecList<T> verList; // list of vertices
    int** adjMatrix;
    bool directed;

    void BFShelper(int st, bool* visited) {
        visited[st] = true;
        cout << verList.getEleAtPos(st) << " ";
        LinkQueue<int> q;
        q.enQueue(st);
        while (!q.isEmpty()) {
            int tmp = q.deQueue();
            for (int k = 0; k < numVer; k++) {
                // investigate adjMatrix[tmp][k]
                if (adjMatrix[tmp][k] == 0) continue;
                if (visited[k]) continue;
                visited[k] = true;
                cout << verList.getEleAtPos(k) << " ";
                q.enQueue(k);
            }
        }
    }

    void DFShelper(int st, bool* visited) {
        visited[st] = true;
        cout << verList.getEleAtPos(st) << " ";
        for (int k = 0; k < numVer; k++) {
            if (adjMatrix[st][k] == 0) continue;
            if (visited[k]) continue;
            DFShelper(k, visited);
        }
    }
    void DFS(int st, bool* visited) {
        visited[st] = true;
        for (int k = 0; k < numVer; k++) {
            if (adjMatrix[st][k] == 0) continue;
            if (visited[k]) continue;
            DFS(k, visited);
        }
    }
   
    bool DFSBi(int st,int*record) {
        for (int k = 0; k< numVer; k++) {
            if (adjMatrix[st][k] == 1) {
                if (record[k] == 0) {
                    record[k] = (record[st] == 1) ? -1 : 1;
                    if (!DFSBi(k, record))return false;
                }
                else if (record[k] == record[st]) { return false; }

            }
        }
        return true;
    }
public:
    AMGraph() { // we don't want this used.
    }
    AMGraph(T* arr, int n, bool dir = false) {
        // n for number of vertices
        // default for undirected graph
        // edges to be added later.

        numVer = n;
        numEdge = 0;
        for (int i = 0; i < n; i++) {
            verList.insertLast(arr[i]);
        }
        directed = dir;

        adjMatrix = new int* [n];
        for (int i = 0; i < n; i++) {
            adjMatrix[i] = new int[n];
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;
        }
    }
    AMGraph(T* arr, int n, Edge<T>** eArr, int e, bool dir = false) {
        // n for number of vertices
        // default for undirected graph
        // edges to be added now. 

        numVer = n;
        numEdge = 0;
        for (int i = 0; i < n; i++) {
            verList.insertLast(arr[i]);
        }
        directed = dir;

        adjMatrix = new int* [n];
        for (int i = 0; i < n; i++) {
            adjMatrix[i] = new int[n];
            for (int j = 0; j < n; j++)
                adjMatrix[i][j] = 0;
        }

        for (int i = 0; i < e; i++) {
            addEdge(eArr[i]->start, eArr[i]->end);
        }
    }
    ~AMGraph() {
        for (int i = 0; i < numVer; i++) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }
    void addEdge(Edge<T> e) {
        addEdge(e.start, e.end);
    }
    void addEdge(T st, T en) {
        int sIndex = verList.locateEle(st);
        int eIndex = verList.locateEle(en);
        if (adjMatrix[sIndex][eIndex] != 0) return;
        numEdge++;
        adjMatrix[sIndex][eIndex] = 1;
        if (!directed) adjMatrix[eIndex][sIndex] = 1;
    }
    void removeEdge(Edge<T> e) {
        removeEdge(e.start, e.end);
    }
    void removeEdge(T st, T en) {
        int sIndex = verList.locateEle(st);
        int eIndex = verList.locateEle(en);
        if (adjMatrix[sIndex][eIndex] == 0) return;
        numEdge--;
        adjMatrix[sIndex][eIndex] = 0;
        if (!directed) adjMatrix[eIndex][sIndex] = 0;
    }
    void printGraph() {
        cout << "Vertices:" << endl;
        for (int i = 0; i < numVer; i++)
            cout << verList.getEleAtPos(i) << " ";

        cout << endl << "Edges:" << endl;
        char sLeft = (directed ? '<' : '(');
        char sRight = (directed ? '>' : ')');
        for (int i = 0; i < numVer; i++) {
            for (int j = i + 1; j < numVer; j++) {
                if (adjMatrix[i][j] == 1) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << endl;
            }
        }
        if (!directed) return;
        for (int i = 0; i < numVer; i++) {
            for (int j = 0; j < i; j++) {
                if (adjMatrix[i][j] == 1) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << endl;
            }
        }
    }
    int** getMatrix() {
        return adjMatrix;
    }
    //BFS
    void printBFS() {
        bool visited[numVer];
        for (int i = 0; i < numVer; i++)
            visited[i] = false;

        for (int i = 0; i < numVer; i++)
            if (!visited[i])
                BFShelper(i, visited);
        cout << endl;
    }
    //DFS
    void printDFS() {
        bool visited[numVer];
        for (int i = 0; i < numVer; i++)
            visited[i] = false;

        for (int i = 0; i < numVer; i++)
            if (!visited[i])
                DFShelper(i, visited);
        cout << endl;
    }
    bool ifsingle(int i) {

        for (int j = 0; j < numVer; j++)
        {
            if (adjMatrix[i][j] != 0) return false;
        }
        return true;
    }
    bool ifalldone(bool* visited)
    {
        for (int i = 0; i < numVer; i++)
        {
            if (visited[i] == false) return false;
        }
        return true;
    }
    bool ifconnected()
    {
        bool *visited=new bool[numVer];
        for (int i = 0; i < numVer; i++)
            visited[i] = false;

                DFS(0, visited);
       int result= ifalldone(visited);
       delete[]visited;
       return result;
    }

    // question 1
    bool isCycleGraph() {
        // assume undirected graph
        if (numVer != numEdge||!ifconnected())return false;
        for (int i = 0; i < numVer; i++)
        {
            int degree = 0;
            for (int j = 0; j < numVer; j++)
            {
                degree += adjMatrix[i][j];
            }
            if (degree != 2)return false;
         }

        return true;
    }

    // question 2
   
    bool existsEulerianPath() {
        // assume undirected
        int  odd = 0;
        VecList<int>empty;
        for (int i = 0; i < numVer; i++) {
            int a = 0;
            for (int j = 0; j < numVer; j++)
            {
                a += adjMatrix[i][j];
            }
            if (a % 2 != 0) odd++;
            else if (a == 0) empty.insertLast(i);
        }
        if (odd!=2&&odd!=0)return false;
        
        T* temp = new T[numVer - empty.getLength()];
        int idx = 0;
        for (int i = 0; i < numVer; i++) {
            if (empty.locateEle(i) == -1) { temp[idx++] = verList.getEleAtPos(i); }
        }
        AMGraph<T>* tmp = new AMGraph<T>(temp,numVer-empty.getLength());
        delete[]temp;
        for (int i = 0; i < numVer; i++) {
            if (empty.locateEle(i) == -1) {
                for (int j = 0; j < numVer; j++) {
                    if (empty.locateEle(j) == -1) {
                        if (adjMatrix[i][j] == 1) {
                            tmp->addEdge(verList.getEleAtPos(i), verList.getEleAtPos(j));
                        }
                    }
                }
            }
        }
        bool f = tmp->ifconnected();
        delete tmp;
        return f;
    }

    //returns whether it's bipartite or not, and print the two groups if it is.
            // starting graph is connected and undirected.
    bool isBipartite() { //ques 3
        // TODO
        int* record = new int[numVer];
        for (int i = 0; i < numVer; i++) {
            record[i] = 0;
        }
        bool now = true;
        for (int i = 0; i < numVer; i++) {
            if (record[i] == 0) {
                now = now && DFSBi(i, record);
                if (!now)break;
            }
        }
        if (now) {
            for (int i = 0; i < numVer; i++) { cout << verList.getEleAtPos(i) << ": group " << ((record[i] == 1) ? 2 : 1 )<< endl; }
        }
        delete[]record;
        return now;
    }

    // question 4
    bool DFSLOOPundirected(int st, bool*visited,int dad) {
        visited[st] = true;
        for (int k = 0; k < numVer; k++) {
            if (adjMatrix[st][k] == 1)
            {
                if (!visited[k])
                {
                    if (DFSLOOPundirected(k, visited, st))return true;
                }
                else if (k!=dad&&visited[k]) return true;
            }
        }
     
        return false;
    }
    bool DFSLOOPdirected(int st, bool* visited, bool* In) {
        visited[st] = true;
        In[st] = true;
        for (int k = 0; k < numVer; k++) {
            if (adjMatrix[st][k] == 1)
            {
                if (!visited[k])
                {
                    if (DFSLOOPdirected(k, visited, In))return true;
                }
                else if (In[k]) return true;
            }
        }
        In[st] = false;
        return false;
    }
    int length(bool* visited) {
        int length = 0;
        for (int i = 0; i < numVer; i++)
        {
            if (visited[i])length++;
        }
        return length;
    }
    bool loopTest()
    {
        bool* visited = new bool[numVer];
      
        for (int i = 0; i < numVer; i++)
        {
            visited[i] = false;
           
        }
        bool cycle = false;
        if (directed) {
            bool* In = new bool[numVer];
            for (int i = 0; i < numVer; i++)
            {
                In[i] = false;

            }
            for (int i = 0; i < numVer; i++) {
                if (!visited[i])
                {
                    if (DFSLOOPdirected(i, visited, In)) {
                        cycle = true;
                        break;
                    }
                }
            }
            delete[] In;
        }
        else {
            for (int i = 0; i < numVer; i++)
            {
                if (!visited[i]) {
                    if (DFSLOOPundirected(i, visited, -1)) {
                        cycle = true;
                        break;
                    }
                }
            }
        }
        delete[]visited;
        return cycle;
    }
};

/* UPLOAD END */

void test1() {
    int tmp[6] = { 0,1,2,3,4,5 };
    AMGraph<int> amg1(tmp, 6);
    for (int i = 0; i < 6; i++) {
        amg1.addEdge(i, ((i + 1) % 6));
    }
    cout << "Graph 1 is " << (amg1.isCycleGraph() ? "" : "not ") << "a cycle graph" << endl;

    amg1.removeEdge(4, 5);
    amg1.addEdge(4, 0);
    cout << "Graph 3 is " << (amg1.isCycleGraph() ? "" : "not ") << "a cycle graph" << endl;
}

void test4() {
    char ver2[5] = { 'A','B','C','D','E' };
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A', 'B');
    amg2.addEdge('A', 'D');
    amg2.addEdge('A', 'E');
    amg2.addEdge('B', 'C');
    amg2.addEdge('C', 'E');
    amg2.addEdge('D', 'C');
    amg2.addEdge('D', 'E');

    cout << "Are there loops in this graph? " << (amg2.loopTest() ? "Yes" : "No") << endl;

    amg2.addEdge('E', 'A');
    cout << "Are there loops in this graph? " << (amg2.loopTest() ? "Yes" : "No") << endl;

    int ver[9] = { 5,6,7,8,9,1,2,3,4 };
    Edge<int>* edges[10];
    edges[0] = new Edge<int>{ 1,2 };
    edges[1] = new Edge<int>{ 1,3 };
    edges[2] = new Edge<int>{ 1,4 };
    edges[3] = new Edge<int>{ 2,3 };
    edges[4] = new Edge<int>{ 2,4 };
    edges[5] = new Edge<int>{ 3,4 };
    edges[6] = new Edge<int>{ 5,8 };
    edges[7] = new Edge<int>{ 5,9 };
    edges[8] = new Edge<int>{ 6,8 };
    edges[9] = new Edge<int>{ 9,6 };

    AMGraph<int> amg1(ver, 9, edges, 10);
    cout << "Are there loops in this graph? " << (amg1.loopTest() ? "Yes" : "No") << endl;

}

void test2() {
    int ver[9] = { 5,6,7,8,9,1,2,3,4 };
    AMGraph<int> amg0(ver, 9);
    cout << "Eulerian path? " << (amg0.existsEulerianPath() ? "Yes" : "No") << endl;
    Edge<int>* edges[10];
    edges[0] = new Edge<int>{ 1,2 };
    edges[1] = new Edge<int>{ 1,3 };
    edges[2] = new Edge<int>{ 1,4 };
    edges[3] = new Edge<int>{ 2,3 };
    edges[4] = new Edge<int>{ 2,4 };
    edges[5] = new Edge<int>{ 3,4 };
    edges[6] = new Edge<int>{ 5,8 };
    edges[7] = new Edge<int>{ 5,9 };
    edges[8] = new Edge<int>{ 6,8 };
    edges[9] = new Edge<int>{ 9,6 };
    AMGraph<int> amg05(ver, 9, edges, 5);
    cout << "Eulerian path? " << (amg05.existsEulerianPath() ? "Yes" : "No") << endl;

    AMGraph<int> amg1(ver, 9, edges, 10);
    cout << "Eulerian path? " << (amg1.existsEulerianPath() ? "Yes" : "No") << endl;
}

int test3() {
    int ver[5] = { 1,2,3,4,5 };
    AMGraph<int> amg1(ver, 5);
    amg1.addEdge(3, 4);
    amg1.addEdge(3, 5);
    amg1.addEdge(1, 3);
    amg1.addEdge(2, 4);
    amg1.addEdge(2, 5);
    cout << (amg1.isBipartite() ? "Bipartite" : "Not bipartite") << endl;

    amg1.addEdge(1, 4);
    cout << (amg1.isBipartite() ? "Bipartite" : "Not bipartite") << endl;

    return 0;
}

int main() {
// test1();
   //test2();
 //  test3();
  test4();
    return 0;
}