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
				addEdge(eArr[i]->start,eArr[i]->end,eArr[i]->weight);
			}
        }
        ~AMGraph(){
            for(int i=0;i<numVer;i++){
            	delete [] adjMatrix[i];
			}
			delete [] adjMatrix;
        }
        void addEdge(Edge<T> e){
            addEdge(e.start,e.end,e.weight);
        }
        void addEdge(T st, T en, int w = 1){
            int sIndex = verList.locateEle(st);
            int eIndex = verList.locateEle(en);
            if(adjMatrix[sIndex][eIndex]!=0) return;
            numEdge++;
            adjMatrix[sIndex][eIndex] = w;
            if(!directed) adjMatrix[eIndex][sIndex] = w;
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
                    if(adjMatrix[i][j] != 0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " << adjMatrix[i][j] <<endl;
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight<< ", weight = " << adjMatrix[i][j]  <<endl;
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

        AMGraph<T>* PrimMST(){
            T* vers = new T[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* result = new AMGraph<T>(vers,numVer,directed);

            bool* isInU = new bool[numVer];
            int* shortWithU = new int[numVer];
            int* shortVer = new int[numVer];

            for(int i=0;i<numVer;i++){
                isInU[i] = false;
                shortWithU[i] = -1;
                shortVer[i] = -1;
            }

            isInU[0] = true;
            for(int i=0;i<numVer;i++){
                if(adjMatrix[0][i]==0) continue;
                shortWithU[i] = adjMatrix[0][i];
                shortVer[i] = 0;
            }

            int numInU = 1;
            while(numInU < numVer){
                int tmpDist = -1;
                int tmpVer = -1;
                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;
                    if(shortWithU[i]==-1) continue;
                    if(tmpDist==-1 || shortWithU[i] < tmpDist){
                        tmpDist = shortWithU[i];
                        tmpVer = i;
                    }
                }

                //cout << "Chosen " << verList.getEleAtPos(tmpVer) << endl;

                numInU++;
                isInU[tmpVer] = true;
                result->addEdge(verList.getEleAtPos(tmpVer),
                                verList.getEleAtPos(shortVer[tmpVer]),tmpDist);
                //result->printGraph();

                for(int i=0;i<numVer;i++){
                    if(isInU[i]) continue;
                    if(adjMatrix[tmpVer][i]==0) continue;
                    if(shortWithU[i]==-1 || adjMatrix[tmpVer][i] < shortWithU[i]){
                        shortWithU[i] = adjMatrix[tmpVer][i];
                        shortVer[i] = tmpVer;
                    }
                }
            }
            return result;
        }

        AMGraph<T>* KruskalMST(){
            T* vers = new T[numVer];
            for(int i=0;i<numVer;i++){
                vers[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* result = new AMGraph<T>(vers,numVer,directed);

            Edge<T>* edges = new Edge<T>[numEdge];
            int pos = 0;
            for(int i=0;i<numVer;i++){
                for(int j=i+1;j<numVer;j++){
                    if(adjMatrix[i][j]==0) continue;
                    edges[pos].start = verList.getEleAtPos(i);
                    edges[pos].end = verList.getEleAtPos(j);
                    edges[pos].weight = adjMatrix[i][j];
                    pos++;
                }
            }

            // sort in ascending order
            for(int i=0;i<numEdge;i++){
                for(int j=0;j<numEdge-1;j++){
                    if(edges[j].weight > edges[j+1].weight){
                        Edge<T> e = edges[j];
                        edges[j] = edges[j+1];
                        edges[j+1] = e;
                    }
                }
            }

            int numCC = numVer;
            int* compNum = new int[numVer];
            for(int i=0;i<numVer;i++){
                compNum[i] = i;
            }

            pos = 0;
            while(numCC > 1){
                Edge<T> e = edges[pos];
                int sCompNum = compNum[verList.locateEle(e.start)];
                int eCompNum = compNum[verList.locateEle(e.end)];
                if(sCompNum==eCompNum){
                    cout << "Dropping edge: (" << e.start << "," << e.end << "), weight = " << e.weight << endl;
                    pos++;
                    continue;
                }

                numCC--;
                cout << "Adding edge: (" << e.start << "," << e.end << "), weight = " << e.weight << endl;
                result->addEdge(e.start,e.end,e.weight);
                int combinedNum = (sCompNum < eCompNum ? sCompNum : eCompNum);
                for(int i=0;i<numVer;i++){
                    if(compNum[i]==sCompNum || compNum[i]==eCompNum){
                        compNum[i] = combinedNum;
                    }
                }
                pos++;
            }

            return result;
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

        void myPrintBayResult(){
            int* inDegrees=new int[numVer];
            for(int i=0;i<numVer;++i){
                inDegrees[i]=0;
            }
            //下面先进行入度计算,下面入度记为负数代表已经被访问过
            for(int i=0;i<numVer;++i){
                for(int j=0;j<numVer;++j){
                    if(adjMatrix[i][j]!=0){
                        ++inDegrees[j];
                    }
                }
            }
            int* Bay=new int[numVer];
            for(int i=0;i<numVer;++i){
                Bay[i]=0;//初始奖金全部记为0
            }
            int numCount=0;
            bool ifcontinue=true;
            bool* visited=new bool[numVer];
            for(int i=0;i<numVer;++i){
                visited[i]=false;
            }
            
            while(numCount<numVer&&ifcontinue){
                ifcontinue=false;
                //下面找是否有入度为0的
                for(int i=0;i<numVer;++i){
                    if(inDegrees[i]==0&&!visited[i]){
                        ifcontinue=true;
                        visited[i]=true;
                        ++numCount;
                        //首先降低与i相连边的入度
                        for(int j=0;j<numVer;++j){
                            if(adjMatrix[i][j]!=0&&!visited[j]){
                                --inDegrees[j];
                                //假如j节点和i相连
                                Bay[j]=(Bay[j]>adjMatrix[i][j]+Bay[i])?Bay[j]:adjMatrix[i][j]+Bay[i];
                                //Bay[j]=max(Bay[j],adjMatrix[i][j]);
                            }
                        }
                    }
                }
            }
            if(numCount!=numVer){
                cout<<"No possible solution!"<<endl;
                return ;
            }
            cout<<"Results:"<<endl;
            cout<<left<<setw(10)<<"Person" << "Pay" << endl;
            for(int i=0;i<numVer;++i){
                cout<<left<<setw(10)<<verList.getEleAtPos(i)<<Bay[i]<<endl; 
            }
        }
};

int main(){
    int m=0,n=0;
    cin>>m>>n;
    int* arr=new int[m];
    for(int i=0;i<m;++i){
        arr[i]=i+1;
    }
    //这里做好了员工表格，也就是图的结点
    //下面要做的是边
    Edge<int>* edges[n];
    for(int i=0;i<n;++i){
        int p=0,q=0,r=0;
        cin>>p>>q>>r;
        edges[i]=new Edge<int> {p,q,r};
    }
    AMGraph<int> result(arr,m,edges,n,true);
    
    //如果成环，那么就没有解
    result.myPrintBayResult();
    return 0;
}