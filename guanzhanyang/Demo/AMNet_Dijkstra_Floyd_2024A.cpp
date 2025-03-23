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
    int weight;
};

template <class T>
class AMGraph{ //we need the number of vertices fixed if we are using this approach
    //our edges don't contain weights here.
    private:
        int numVer, numEdge;
        VecList<T> verList; // list of vertices
        int** adjMatrix;
        bool directed;

        void BFShelper(int st, bool* visited){
        	visited[st] = true;
        	cout << verList.getEleAtPos(st) << " ";
        	LinkQueue<int> q;
        	q.enQueue(st);
        	while(!q.isEmpty()){
        		int tmp = q.deQueue();
        		for(int k=0;k<numVer;k++){
        			// investigate adjMatrix[tmp][k]
        			if(adjMatrix[tmp][k]==0) continue;
        			if(visited[k]) continue;
        			visited[k] = true;
        			cout << verList.getEleAtPos(k) << " ";
        			q.enQueue(k);
				}
			}
		}

		void DFShelper(int st, bool* visited){
			visited[st] = true;
			cout << verList.getEleAtPos(st) << " ";
			for(int k=0;k<numVer;k++){
				if(adjMatrix[st][k]==0) continue;
				if(visited[k]) continue;
				DFShelper(k,visited);
			}
		}
    public:
        AMGraph(){ // we don't want this used.
        }
        AMGraph(T* arr, int n, bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added later.

            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;

			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;
			}
        }
        AMGraph(T* arr, int n, Edge<T>** eArr, int e,bool dir=false){
            // n for number of vertices
            // default for undirected graph
            // edges to be added now.

            numVer = n;
			numEdge = 0;
			for(int i=0;i<n;i++){
				verList.insertLast(arr[i]);
			}
			directed = dir;

			adjMatrix = new int*[n];
			for(int i=0;i<n;i++){
				adjMatrix[i] = new int[n];
				for(int j=0;j<n;j++)
					adjMatrix[i][j] = 0;
			}

			for(int i=0;i<e;i++){
				addEdge(eArr[i]->start,eArr[i]->end, eArr[i]->weight);
			}
        }
        ~AMGraph(){
            for(int i=0;i<numVer;i++){
            	delete [] adjMatrix[i];
			}
			delete [] adjMatrix;
        }
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end, e.weight);
        }
        void addEdge(T st, T en, int weight){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]!=0) return;
            numEdge++;
            adjMatrix[sIndex][eIndex] = weight;
            if(!directed) adjMatrix[eIndex][sIndex] = weight;
        }
        void removeEdge(Edge<T> e){
            removeEdge(e.start,e.end);
        }
        void removeEdge(T st, T en){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]==0) return;
            numEdge--;
            adjMatrix[sIndex][eIndex] = 0;
            if(!directed) adjMatrix[eIndex][sIndex] = 0;
        }
        void printGraph(){
            cout << "Vertices:" << endl;
            for(int i=0;i<numVer;i++)
                cout << verList.getEleAtPos(i) << " ";

            cout << endl << "Edges:" << endl;
            char sLeft = (directed ? '<' : '(');
            char sRight = (directed ? '>' : ')');
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j] != 0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight=" << adjMatrix[i][j] <<endl;
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] != 0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight=" << adjMatrix[i][j] <<endl;
                }
            }
        }
        int** getMatrix(){
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

        AMGraph<T>* PrimMST(){ // all edges have positive weight
            T vers[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* amg = new AMGraph<T>(vers,numVer);

            bool isInU[numVer];
            int dist[numVer]; // minimal distance from some point of U to a vertex outside U
            int fromWhichU[numVer];

            isInU[0] = true;
            dist[0] = 0;
            for(int i=1;i<numVer;i++){
                isInU[i] = false;
                dist[i] = (adjMatrix[0][i]!=0 ? adjMatrix[0][i] : -1);
                fromWhichU[i] = (adjMatrix[0][i]!=0 ? 0 : -1);
            }

            int countU = 1;

            while(countU < numVer){
                // find minimal weight edge
                int tmpW = -1; // minimal weight
                int tmpV = -1; // corresponding vertex
                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;
                    if(tmpW==-1){
                        tmpW = dist[i];
                        tmpV = i;
                    }
                    else{
                        if(dist[i]!=-1 && dist[i] < tmpW){
                            tmpW = dist[i];
                            tmpV = i;
                        }
                    }
                }

                // now we have minimal weight, and vertex
                // add it into U.
                isInU[tmpV] = true;
                amg->addEdge(verList.getEleAtPos(tmpV),verList.getEleAtPos(fromWhichU[tmpV]),tmpW);
                countU++;

                // update dist, fromWhichU
                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;
                    if(adjMatrix[i][tmpV]!=0){
                        if(dist[i]==-1){
                            dist[i] = adjMatrix[i][tmpV];
                            fromWhichU[i] = tmpV;
                        }
                        else if(dist[i] > adjMatrix[i][tmpV]){
                            dist[i] = adjMatrix[i][tmpV];
                            fromWhichU[i] = tmpV;
                        }
                    }
                }
                cout << "At step " << countU-1 << endl;
                amg->printGraph();
            }

            return amg;
        }

        AMGraph<T>* KruskalMST(){
            T vers[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* amg = new AMGraph<T>(vers,numVer);

            int edgeSt[numEdge];
            int edgeEn[numEdge];
            int weight[numEdge];

            int index = 0;
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j]==0) continue;
                    edgeSt[index] = i;
                    edgeEn[index] = j;
                    weight[index] = adjMatrix[i][j];
                    index++;
                }
            }

            for(int i=0;i<numEdge;i++){
                for(int j=0;j+1<numEdge;j++){
                    if(weight[j] > weight[j+1]){
                        int tmp = weight[j];
                        weight[j] = weight[j+1];
                        weight[j+1] = tmp;
                        tmp = edgeSt[j];
                        edgeSt[j] = edgeSt[j+1];
                        edgeSt[j+1] = tmp;
                        tmp = edgeEn[j];
                        edgeEn[j] = edgeEn[j+1];
                        edgeEn[j+1] = tmp;
                    }
                }
            }

            // edges arranged in increasing order.

            // add edges from smallest to largest, ensuring not forming loops
            int componentNum[numVer];
            for(int i=0;i<numVer;i++){
                componentNum[i] = i;
            }
            int compNum = numVer;
            index = 0;

            while(compNum > 1){
                // look at edge, at index.
                // examine if edgeSt[index] and edgeEn[index] is in the same component
                if(componentNum[edgeSt[index]] == componentNum[edgeEn[index]]){
                    index++;
                    continue;
                }

                // add Edge
                amg->addEdge(verList.getEleAtPos(edgeSt[index]), verList.getEleAtPos(edgeEn[index]), weight[index]);

                // put things into the same component
                int numToSetTo = componentNum[edgeSt[index]];
                int numNeedingChange = componentNum[edgeEn[index]];
                for(int i=0;i<numVer;i++){
                    if(componentNum[i]==numNeedingChange)
                        componentNum[i] = numToSetTo;
                }
                compNum--;
                index++;

                cout << "At step " << index << ":" << endl;
                amg->printGraph();
            }
            return amg;
        }

        void printDijkstra(T st){ // positive weights
            bool* isInS = new bool[numVer];
            int* dist = new int[numVer];
            int* lastNode = new int[numVer];
            for(int i=0;i<numVer;i++){
                isInS[i] = false;
                dist[i] = -1;
                lastNode[i] = -1;
            }

            int sIndex = verList.locateEle(st);
            isInS[sIndex] = true;
            dist[sIndex] = 0;

            for(int i=0;i<numVer;i++){
                if(adjMatrix[sIndex][i]==0) continue;
                dist[i] = adjMatrix[sIndex][i];
                lastNode[i] = sIndex;
            }

            int numInS = 1;
            while(numInS < numVer){
                int tmpIndex = -1;
                int shortSoFar = -1;
                for(int i=0;i<numVer;i++){
                    if(isInS[i]) continue;
                    if(dist[i]==-1) continue;
                    if(shortSoFar==-1 || dist[i] < shortSoFar){
                        tmpIndex = i;
                        shortSoFar = dist[i];
                    }
                }

                if(tmpIndex==-1){
                    break;
                }

                // add shortest into S
                isInS[tmpIndex] = true;
                numInS++;

                for(int i=0;i<numVer;i++){
                    if(isInS[i]) continue;
                    if(adjMatrix[tmpIndex][i]==0) continue;
                    int tDist = dist[tmpIndex] + adjMatrix[tmpIndex][i];
                    if(dist[i]==-1 || tDist < dist[i]){
                        dist[i] = tDist;
                        lastNode[i] = tmpIndex;
                    }
                }
            }

            cout << left << setw(18) << "Vertice name" << "Path" << endl;
            for(int i=0;i<numVer;i++){
                cout << left << setw(18) << verList.getEleAtPos(i);
                if(dist[i]==-1){
                    cout << "Unreachable" << endl;
                    continue;
                }
                LinkStack<int> S;
                S.push(i);
                int j=lastNode[i];
                while(j!=-1){
                    S.push(j);
                    j = lastNode[j];
                }
                cout << verList.getEleAtPos(S.pop());
                while(!S.isEmpty()){
                    cout << " -> " << verList.getEleAtPos(S.pop());
                }
                cout << ", cost = " << dist[i] << endl;
            }
        }

        int** distances(){
            // compute distance between any 2 nodes
            // Floyd's version
            // positive weights
            int** dists = new int*[numVer];
            for(int i=0;i<numVer;i++){
                dists[i] = new int[numVer];
                for(int j=0;j<numVer;j++){
                    dists[i][j] = (adjMatrix[i][j] > 0 ? adjMatrix[i][j] : -1);
                }
                dists[i][i] = 0;
            }

            for(int k=0;k<numVer;k++){
                for(int i=0;i<numVer;i++){
                    for(int j=0;j<numVer;j++){
                        if(dists[i][k]==-1 || dists[k][j]==-1) continue;
                        int tDist = dists[i][k]+dists[k][j];
                        if(dists[i][j]==-1 || tDist < dists[i][j])
                            dists[i][j] = tDist;
                    }
                }
            }
            return dists;
        }

        T** preNodeDist(T bad){
            // compute distance between any 2 nodes
            // Floyd's version
            // positive weights
            int** dists = new int*[numVer];
            T** preNodes = new T*[numVer];
            for(int i=0;i<numVer;i++){
                dists[i] = new int[numVer];
                preNodes[i] = new T[numVer];
                for(int j=0;j<numVer;j++){
                    dists[i][j] = (adjMatrix[i][j] > 0 ? adjMatrix[i][j] : -1);
                    if(dists[i][j] > 0) preNodes[i][j] = verList.getEleAtPos(i);
                    else preNodes[i][j] = bad;
                }
                dists[i][i] = 0;
            }

            for(int k=0;k<numVer;k++){
                for(int i=0;i<numVer;i++){
                    for(int j=0;j<numVer;j++){
                        if(dists[i][k]==-1 || dists[k][j]==-1) continue;
                        int tDist = dists[i][k]+dists[k][j];
                        if(dists[i][j]==-1 || tDist < dists[i][j]){
                            dists[i][j] = tDist;
                            preNodes[i][j] = preNodes[k][j];
                        }
                    }
                }
            }
            return preNodes;

        }
};

// put something that multiplies matrix, just for demonstrating meaning of A^k
// another that multiplies matrix.
template <class T>
void printMatrix(T** mat, int n){
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

void test(){
    int ver[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(ver,6);
    amg1.addEdge(0,1,34);
    amg1.addEdge(0,5,19);
    amg1.addEdge(0,2,46);
    amg1.addEdge(5,2,25);
    amg1.addEdge(5,3,25);
    amg1.addEdge(5,4,26);
    amg1.addEdge(2,3,17);
    amg1.addEdge(3,4,38);
    amg1.addEdge(1,4,12);

    //amg1.printGraph();

    cout << endl << "Dijkstra starting at vertex 0: " << endl;
    amg1.printDijkstra(0);

    cout << endl << "All distances:" << endl;
    printMatrix(amg1.distances(),6);

    cout << endl << "All prev node:" << endl;
    printMatrix(amg1.preNodeDist(-1),6);

    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B',10);
    amg2.addEdge('A','D',30);
    amg2.addEdge('A','E',100);
    amg2.addEdge('B','C',50);
    amg2.addEdge('C','E',10);
    amg2.addEdge('D','C',20);
    amg2.addEdge('D','E',60);
    cout << endl << "Dijkstra starting at vertex A: " << endl;
    amg2.printDijkstra('A');

    cout << endl << "All distances:" << endl;
    printMatrix(amg2.distances(),5);

    cout << endl << "All prev node:" << endl;
    printMatrix(amg2.preNodeDist(' '),5);
}

int main(){
    test();
    return 0;
}
