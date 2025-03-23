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

/* UPLOAD START */

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
            addEdge(e.start,e.end, e.weight);
        }
        void addEdge(T st, T en, int weight=1){
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
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " <<  adjMatrix[i][j]<<endl; 
                }
            }
            if(!directed) return;
            for(int i=0;i<numVer;i++){
                for(int j=0;j<i;j++){
                    if(adjMatrix[i][j] !=0) cout << sLeft << verList.getEleAtPos(i) << "," << verList.getEleAtPos(j) << sRight << ", weight = " <<  adjMatrix[i][j]<<endl; 
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
            T* tArr = new T[numVer];
            for(int i=0;i<numVer;i++){
                tArr[i] = verList.getEleAtPos(i);
            }
            AMGraph<T>* tmp = new AMGraph<T>(tArr,numVer);
            
            // that constructed a new graph. Now we need to put the edges in.
            bool* inS = new bool[numVer]; // if the vertex is in set S
            int* shortVer = new int[numVer]; // shortest vertice to point
            int count = 0; // how many vertices are in S.
            int lastIndex; // to know which edges we need to check for updates
            for(int i=0;i<numVer;i++){
                inS[i] = false;
                shortVer[i] = -1;
            }
            
            // we start Prim's algorithm now, with vertex 0 being the first one to be put into S.
            inS[0] = true;
            count = 1;
            lastIndex = 0;
            while(count < numVer){ // as long as not all vertices are in  S yet...
            
                int sIndex = -1;
                // update the shortVer array and find shortest
                for(int i=0;i<numVer;i++){
                    if(!inS[i] && adjMatrix[lastIndex][i]>0){
                        if(shortVer[i]==-1){
                            shortVer[i] = lastIndex;
                        }
                        if(adjMatrix[lastIndex][i] < adjMatrix[i][shortVer[i]])
                            shortVer[i] = lastIndex;
                    }
                    if(!inS[i] && shortVer[i]!=-1){ // valid candidate to put into S
                        if(sIndex == -1){
                            sIndex = i;
                        }
                        else if(adjMatrix[i][shortVer[i]] < adjMatrix[sIndex][shortVer[sIndex]]){
                            sIndex = i;
                        }
                            
                    }
                }
                
                inS[sIndex] = true;
                // cout << "Taking edge: (" << verList.Get(shortVer[sIndex]) << "," << verList.Get(sIndex) << "), weight = ";
                // cout << adjMatrix[shortVer[sIndex]][sIndex] << endl;
                tmp->addEdge(verList.getEleAtPos(shortVer[sIndex]),verList.getEleAtPos(sIndex),adjMatrix[shortVer[sIndex]][sIndex]);
                count++;
                lastIndex = sIndex;
            }
            return tmp;
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

        void distFromAllTo(T end){
            // use the same format as our demonstration of Dijkstra
			bool* isInS = new bool[numVer];
            int* dist = new int[numVer];
            int* lastNode = new int[numVer];
            for(int i=0;i<numVer;i++){
                isInS[i] = false;
                dist[i] = -1;//第i个结点可以到达end结点，否则是-1
                lastNode[i] = -1;
            }

            int endIndex = verList.locateEle(end);
            isInS[endIndex] = true;
            dist[endIndex] = 0;

            for(int i=0;i<numVer;i++){
                if(adjMatrix[i][endIndex]==0) continue;
                dist[i] = adjMatrix[i][endIndex];
                lastNode[i] = endIndex;
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
                    if(adjMatrix[i][tmpIndex]==0) continue;
                    int tDist = dist[tmpIndex] + adjMatrix[i][tmpIndex];
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
                LinkQueue<int> S;
                S.enQueue(i);
                int j=lastNode[i];
                while(j!=-1){
                    S.enQueue(j);
                    j = lastNode[j];
                }
                cout << verList.getEleAtPos(S.deQueue());
                while(!S.isEmpty()){
                    cout << " -> " << verList.getEleAtPos(S.deQueue());
                }
                cout << ", cost = " << dist[i] << endl;
            }
        }
        
        int numPathsDAG(){
            // our graph has one source and one sink
            //首先进行拓扑排序
            int* topSort=new int[numVer];
            TopologicalSort(topSort);
            //这里已经做好了拓扑排序
            //下面用动态规划做,现在这里源点的下标是topS[0] ,汇点是topS[numVer-1]
            int* dp=new int[numVer];
            for(int i=0;i<numVer;++i){
                dp[i]=0;
            }
            //dp数组代表从汇点到达第i个节点的路径数量，汇点到自身是1;
            dp[topSort[0]]=1;
            //dp[topSort[i]]=sum  dp[topSort[j]]  j=0,i-1
            
            for(int i=1;i<numVer;++i){
                for(int j=0;j<i;++j){
                    if(adjMatrix[topSort[j]][topSort[i]]!=0){
                        dp[topSort[i]]+=dp[topSort[j]];
                    }
                }
            }
            return dp[topSort[numVer-1]];
        }

        int* TopologicalSort(){
            //拓扑排序,针对有向无环图
            int* inDegrees=new int[numVer];
            for(int i=0;i<numVer;++i){
                inDegrees[i]=0;
                for(int j=0;j<numVer;++j){
                    if(adjMatrix[j][i]!=0){
                        ++inDegrees[i];
                    }
                }
            }
            //创建并初始化visited数组
            bool* visited=new bool[numVer];
            for(int i=0;i<numVer;++i){
                visited[i]=false;
            }
            //创建保存拓扑顺序(保存节点下标)的数组
            int* topSort=new int[numVer];
            //下面不断删除入度为0的边
            bool changed=true;
            int pos=0;
            while(changed){
                changed=false;
                for(int i=0;i<numVer;++i){
                    if(!visited[i]&&inDegrees[i]==0){
                        changed=true;
                        topSort[pos]=i;
                        visited[i]=true;
                        pos++;
                        for(int j=0;j<numVer;++j){
                            if(adjMatrix[i][j]!=0){
                                --inDegrees[j];
                            }
                        }
                    }
                } 
            }
            if(pos<numVer-1||pos==0) throw"Loop Existed";
            return topSort;
        }

        void TopologicalSort(int* topSort){
            int* inDegrees=new int[numVer];
            for(int i=0;i<numVer;++i){
                inDegrees[i]=0;
            }

            bool* visited=new bool[numVer];
            for(int i=0;i<numVer;++i){
                visited[i]=false;
            }
            //下面先进行入度计算,下面入度记为负数代表已经被访问过
            for(int i=0;i<numVer;++i){
                for(int j=0;j<numVer;++j){
                    if(adjMatrix[i][j]!=0){
                        ++inDegrees[j];
                    }
                }
            }
            //以上计算好了入度，为了方便删除，先将邻接矩阵进行一遍复制
            int** copyMatrix=new int*[numVer];
            for(int i=0;i<numVer;++i){
                copyMatrix[i]=new int[numVer];
                for(int j=0;j<numVer;++j){
                    copyMatrix[i][j]=adjMatrix[i][j];
                }
            }
            //下面不断进行拓扑排序，不断找出入度为0的，删除入度为0的结点
            int pos=0;
            while(pos<numVer){
                for(int i=0;i<numVer;++i){
                    if(!visited[i]&&inDegrees[i]==0){
                        topSort[pos]=i;
                        visited[i]=true;
                        pos++;
                        //下面将所有从i射出的边删掉
                        for(int j=0;j<numVer;++j){
                            if(copyMatrix[i][j]!=0){
                                --inDegrees[j];
                                copyMatrix[i][j]=0;
                            }
                        }
                    }
                }
            }
        }
        
        // question 4        
        AMGraph<T>* criticalEdge(){
            T* arr=new T[numVer];
            for(int i=0;i<numVer;++i){
                arr[i]=verList.getEleAtPos(i);
            }
            AMGraph<T>* result=new AMGraph<T>(arr,numVer);
            for(int i=0;i<numVer;++i){
                for(int j=i+1;j<numVer;++j){
                    if(adjMatrix[i][j]!=0){
                        //这里要对删除这里的i，j边作出判断
                        AMGraph<T>* compare=new AMGraph<T>(arr,numVer);
                        for(int a=0;a<numVer;++a){
                            for(int b=a+1;b<numVer;++b){
                                if(adjMatrix[a][b]!=0){
                                    compare->addEdge(verList.getEleAtPos(a),verList.getEleAtPos(b),adjMatrix[a][b]);
                                }
                            }
                        }
                        Edge<T> e;
                        e.weight=adjMatrix[i][j];
                        e.start=verList.getEleAtPos(i);
                        e.end=verList.getEleAtPos(j);
                        compare->removeEdge(e);
                        if(!compare->isConnected()){
                            result->addEdge(e);
                        }
                    }
                }
            }
            return result;
        }

        bool isConnected(){
            //从任意一个结点出发看是否是连通的，也就是能否遍历到所有节点
            bool* visited=new bool[numVer];
            for(int i=0;i<numVer;++i){
                visited[i]=false;
            }
            visited[0]=true;
            int numvisited=1;
            LinkQueue<int> q;
            q.enQueue(0);
            while(!q.isEmpty()){
                int Index=q.deQueue();
                for(int i=0;i<numVer;++i){
                    if(adjMatrix[Index][i]!=0&&!visited[i]){
                        q.enQueue(i);
                        visited[i]=true;
                        ++numvisited;
                    }
                }
            } 
            return numVer==numvisited;      
        }

        void printTopo(){
            int* topoSort=TopologicalSort();
            for(int i=0;i<numVer;++i){
                cout<<verList.getEleAtPos(topoSort[i])<<" ";
            }
            cout<<endl;
        }
};

/* UPLOAD END */

void test1(){
    char ver2[5] = {'A','B','C','D','E'};
    AMGraph<char> amg2(ver2, 5, true);
    amg2.addEdge('A','B',10);
    amg2.addEdge('A','D',30);
    amg2.addEdge('A','E',100);
    amg2.addEdge('B','C',50);
    amg2.addEdge('C','E',10);
    amg2.addEdge('D','C',20);
    amg2.addEdge('D','E',60);
    amg2.addEdge('E','A',100);

    amg2.printTopo();
    //cout << "Shortest paths to vertex E: " << endl;
    //amg2.distFromAllTo('E');
    
    cout << endl;
}

void test2(){
    int ver[8] = {0,1,2,3,4,5,6,7};
    AMGraph<int> amg(ver,8,true);
    amg.addEdge(0,3);
    amg.addEdge(0,4);
    amg.addEdge(3,1);
    amg.addEdge(4,1);
    amg.addEdge(0,1);
    amg.addEdge(1,5);
    amg.addEdge(1,6);
    amg.addEdge(1,7);
    amg.addEdge(5,2);
    amg.addEdge(6,2);
    amg.addEdge(7,2);
    amg.addEdge(1,2);

    cout << "Case 1: Number of ways to get from source to sink is " << amg.numPathsDAG() << endl;
    
    int ver2[5] = {1,2,3,4,5};
    AMGraph<int> amg2(ver2,5,true);
    amg2.addEdge(1,2);
    amg2.addEdge(1,3);
    amg2.addEdge(1,4);
    amg2.addEdge(1,5);
    amg2.addEdge(2,4);
    amg2.addEdge(3,4);
    amg2.addEdge(3,5);
    amg2.addEdge(4,5);
    cout << "Case 2: Number of ways to get from source to sink is " << amg2.numPathsDAG() << endl;
}

void test3(){

    int ver[6] = {0,1,2,3,4,5};
    AMGraph<int> amg1(ver,6);

    amg1.addEdge(0,1,1);
    amg1.addEdge(1,2,2);
    amg1.addEdge(2,3,3);
    amg1.addEdge(3,4,4);
    amg1.addEdge(4,5,5);
    AMGraph<int>* tmp = amg1.criticalEdge();
    tmp->printGraph();
    
    AMGraph<int> amg2(ver, 6);
    amg2.addEdge(0,1);
    amg2.addEdge(1,2);
    amg2.addEdge(0,2);
    amg2.addEdge(2,3);
    amg2.addEdge(3,4);
    amg2.addEdge(4,5);
    tmp = amg2.criticalEdge();
    tmp->printGraph();
}

int main(){
    test1();
 //   test2();
  //  test3();
    return 0;
}
