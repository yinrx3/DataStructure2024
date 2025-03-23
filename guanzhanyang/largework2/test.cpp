#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
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

        void printListArrow(){
            for(int i=0;i<length-1;++i){
                cout<< arr[i] <<" -> ";
            }
            cout<<arr[length-1];
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
        AMGraph(AMGraph<T>& other) {
        numVer = other.numVer;
        numEdge = other.numEdge;
        directed = other.directed;

        for (int i = 0; i < numVer; i++) {
            verList.insertLast(other.verList.getEleAtPos(i));
        }

        adjMatrix = new int*[numVer];
        for (int i = 0; i < numVer; i++) {
            adjMatrix[i] = new int[numVer];
            for (int j = 0; j < numVer; j++) {
                adjMatrix[i][j] = other.adjMatrix[i][j];
            }
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

        void printKSSP(T st,T en,int k,VecList<T>* blacklist,int maxStops){
            //maxStops只用与最后检查，也就是总路径节点数量小于等于maxStops+2，只有在最后的输出阶段才会使用到
            //这里传入的maxstops一定是大于等于-1的整数值
            VecList<VecList<T>*>* paths=new VecList<VecList<T>*>;//这里是类似于多维数组，paths储存前k短路径
            VecList<T>* initialPath=this->Dijkstra(st,en,blacklist);
            if(maxStops==-1){
                if(initialPath->getLength()==0){
                    cout<<"There are 0 paths."<<endl; 
                    return ;
                }
            }
            else{
                if(initialPath->getLength()>maxStops+2){
                    cout<<"There are 0 paths."<<endl; 
                    return ;
                }
            }
            
            paths->insertLast(initialPath);//将目前最短的路径给放进去
            //到这里其实说明满足  黑名单条件以及中继节点个数的最短的路径是存在的
            
            //下面不断通过偏离路径的方法获得建立候选路径集合然后不断添加进去
            
            for(int i=1;i<k;++i){
                //由于我们最短的已经找到了，也就是i=0已经确定下来了，下面从i=1开始
                VecList<VecList<T>*>* candidates=new VecList<VecList<T>*>   ;
                //上面这个用来存储候选路径

                //我们从已经得到的最短路径入手不断找稍微长一点点的最短路径
                for(int j=0;j<paths->getLength();++j){
                    VecList<T>* pathToDo=new VecList<T>;
                    pathToDo=paths->getEleAtPos(j);
                    //这样就获取到了某一条路径

                    //下面是将这个路劲里面的，除去终点以外的所有节点当做偏离节点
                    for(int l=0;l<pathToDo->getLength()-1;++l){
                        T vi=pathToDo->getEleAtPos(l);
                        //其中这个vi不能在黑名单里面
                        if(blacklist->locateEle(vi)!=-1) continue;//跳过vi在黑名单里面的

                        //下面复制从st到vi的路径
                        VecList<T>* rootPath=new VecList<T>;
                        for(int m=0;m<=l;m++){
                            rootPath->insertLast(pathToDo->getEleAtPos(m));
                        }

                        //下面要做的是得到从vi到en的最短路径，同时避免黑名单

                        AMGraph<T>* tmpGraph=new AMGraph<T>(*this);//创建一个新图
                        //这个新图对应某个偏离节点vi，这个偏离节点vi是在某个前面k-1个里面路径pathToDo里面选出来的
                        for(int m=0;m<paths->getLength();++m){
                            VecList<T>* knownPath=paths->getEleAtPos(m);
                            for(int n=0;n<knownPath->getLength()-1;++n){
                                tmpGraph->removeEdge(knownPath->getEleAtPos(n),knownPath->getEleAtPos(n+1));
                            }
                        }
                        
                        //从vi到en用Dijkstra算法计算最短路径
                        VecList<T>* spurPath=tmpGraph->Dijkstra(vi,en,blacklist);
                        if(spurPath->getLength()>0){
                            //下面拼接rootPath和spurPath
                            VecList<T>* candidatePath=new VecList<T>;
                            for(int m=0;m<rootPath->getLength();++m){
                                candidatePath->insertLast(rootPath->getEleAtPos(m));
                            }
                            for(int m=1;m<spurPath->getLength();++m){
                                candidatePath->insertLast(spurPath->getEleAtPos(m));
                            }

                            //再次检查路径是否包含黑名单结点
                            bool isValid=true;
                            for(int m=0;m<candidatePath->getLength();++m){
                                if(blacklist->locateEle(candidatePath->getEleAtPos(m))!=-1){
                                    isValid=false;
                                    break;
                                }
                            }

                            if(isValid){
                                if(maxStops==-1){
                                    //表示长度没有限制 
                                    candidates->insertLast(candidatePath);
                                }
                                else if(candidatePath->getLength()<=maxStops+2){
                                    candidates->insertLast(candidatePath);
                                }
                            }
                        }
                    }
                }
            
                //到这里所有的候选路径已经找完了

                if(candidates->getLength()==0){
                    //表示没有新的候选路径
                    break;//终止所有循环
                }

                //否则选择最短的候选路径

                int minIndex=0;//默认candidas里面位序为0的是最短的
                for(int j=1;j<candidates->getLength();++j){
                    if(this->getPathLength(candidates->getEleAtPos(j))<this->getPathLength(candidates->getEleAtPos(minIndex))){
                        minIndex=j;
                    }
                }

                paths->insertLast(candidates->getEleAtPos(minIndex));
            }

            //下面就是打印工作了
            cout<<"There are "<< paths->getLength()<<" paths."<<endl;
            for(int i=0;i<paths->getLength();++i){
                cout<<"Path "<<i<<": ";

                paths->getEleAtPos(i)->printListArrow();
                cout<<", distance = "<<this->getPathLength(paths->getEleAtPos(i))<<endl;
            }

        }

        VecList<T>* Dijkstra(T st,T en,VecList<T>* blacklist){
            //这里如果是没有路径，就返回一个空向量表
            if(blacklist->locateEle(st)!=-1||blacklist->locateEle(en)!=-1){
                VecList<T>* shortestPathl=new VecList<T>;
                return shortestPathl;
            }

            bool* isInU=new bool[numVer];
            int* dist=new int[numVer];
            int* preNode=new int[numVer];
            for(int i=0;i<numVer;++i){
                isInU[i]=false;
                dist[i]=INT_MAX;
                preNode[i]=-1;
            }//以上完成了最基本的初始化过程，下面将st添加进集合U

            int sIndex=verList.locateEle(st);
            dist[sIndex]=0;
            isInU[sIndex]=true;

            //下面处理与sIndex直接相连接的结点与路径

            for(int i=0;i<numVer;++i)
            {
                if(isInU[i]) continue;
                if(blacklist->locateEle(verList.getEleAtPos(i))!=-1) continue;//跳过在黑名单里面的
                if(adjMatrix[sIndex][i]==0) continue;
                dist[i]=adjMatrix[sIndex][i];
                preNode[i]=sIndex;
            }

            //下面进入循环
            int numInU=1;

            while(numInU<numVer){
                int tmpIndex=-1;
                int MinDist=INT_MAX;
                for(int i=0;i<numVer;++i){
                    //首先要找一个结点进入集合U
                    if(isInU[i]) continue;//跳过已经在集合里面的
                    if(dist[i]==INT_MAX) continue;//跳过暂时没有路径连接的
                    if(blacklist->locateEle(verList.getEleAtPos(i))!=-1) continue;//跳过在黑名单里面的
                    if(dist[i]<INT_MAX){
                        tmpIndex=i;
                        MinDist=dist[i];
                    }
                }

                if(tmpIndex==-1) break;

                //将目前找到的放进集合U

                isInU[tmpIndex]=true;
                ++numInU;

                for(int i=0;i<numVer;++i){
                    //下面修改通过新的集合U到达st
                    if(isInU[i]) continue;
                    if(adjMatrix[tmpIndex][i]==0) continue;
                    if(blacklist->locateEle(verList.getEleAtPos(i))!=-1) continue;//跳过在黑名单里面的
                    int tDist=dist[tmpIndex]+adjMatrix[tmpIndex][i];
                    if(tDist<dist[i]){
                        dist[i]=tDist;
                        preNode[i]=tmpIndex;
                    }
                }
            }

            //这里就完成了找最短路径问题

            VecList<T>* shortestPath=new VecList<T>;
            if(dist[verList.locateEle(en)]==INT_MAX) return shortestPath;
            //到原始节点st距离依然是 无穷大，那么说明在当前黑名单下没有找到最短路径

            //否则最短路径一定存在，下面将最短路径对应的结点名字依次写进去

            LinkStack<T> s;
            s.push(en);
            int j=preNode[verList.locateEle(en)];
            while(j!=-1){
                s.push(verList.getEleAtPos(j));
                j=preNode[j];
            }

            //现在就已经将所有节点放进栈里面了，下面全部拿出来放进向量表里面

            while(!s.isEmpty()){
                shortestPath->insertLast(s.pop());
            }

            return shortestPath;
        }

        int getPathLength(VecList<T>* path){
            if(path->getLength()==0) return -1;
            int length=0;
            for(int i=0;i<path->getLength()-1;++i){
                T u=path->getEleAtPos(i);
                T v=path->getEleAtPos(i+1);
                length+=adjMatrix[verList.locateEle(u)][verList.locateEle(v)];
            }
            return length;
            //这样空路径就返回值-1，单个节点就返回值0
        }
};

void doDemo(){
    int m=0,n=0;
    cin>>m>>n;
    string* Vertice=new string[m];
    for(int i=0;i<m;++i){
        cin>>Vertice[i];
    }
    AMGraph<string> result(Vertice,m);//这里默认为无向图
    //下面要添加边进去
    for(int i=0;i<n;++i){
        string s1,s2;
        int weight=1;
        cin>>s1>>s2>>weight;
        result.addEdge(s1,s2,weight);
    }
    //到这里为止，所有的边就加进去了
    int maxStops=-1;
    bool isContinue=true;
    VecList<string>* blacklist=new VecList<string>;

    while(isContinue){
        cout<<"Please enter your next request."<<endl;
        cout<<"Options include: ban X, unban X, maxTrans Y, paths A B k, quit."<<endl;
        string tmpStr;
        cin>>tmpStr;
        if(tmpStr=="ban"){
            cin>>tmpStr;
            if(blacklist->locateEle(tmpStr)!=-1) continue;//如果已经在黑名单里面，代表输入的没用
            blacklist->insertLast(tmpStr);
        }
        else if(tmpStr=="unban"){
            cin>>tmpStr;
            if(blacklist->locateEle(tmpStr)==-1) continue;//黑名单里面没找到、
            blacklist->deleteEleAtPos(blacklist->locateEle(tmpStr));
        }
        else if(tmpStr=="maxTrans"){
            cin>>maxStops;
            if(maxStops<-1){
                cout<<"Invalid restriction, lifting max transition restriction."<<endl;
            }
        }
        else if(tmpStr=="paths"){
            string st,en;
            int k=0;
            cin>>st>>en>>k;
            if(k<=0) cout<<"Invalid number of paths."<<endl;
            else{
                result.printKSSP(st,en,k,blacklist,maxStops);
            }
        }
        else if(tmpStr=="quit"){
            isContinue=false;
        }
        else{
            cout<<"No such option."<<endl;
        }
    } 

}

void test(){
    int m=0,n=0;
    cin>>m>>n;
    string* Vertice=new string[m];
    for(int i=0;i<m;++i){
        cin>>Vertice[i];
    }
    AMGraph<string> result(Vertice,m);//这里默认为无向图
    //下面要添加边进去
    for(int i=0;i<n;++i){
        string s1,s2;
        int weight=1;
        cin>>s1>>s2>>weight;
        result.addEdge(s1,s2,weight);
    }
    //到这里为止，所有的边就加进去了

    result.printGraph();

    
    bool isContinue=true;
    VecList<string>* blacklist=new VecList<string>;

    while(isContinue){
        cout<<"Please enter your next request."<<endl;
        cout<<"Options include: ban X, unban X, maxTrans Y, paths A B k, quit."<<endl;
        string tmpStr;
        cin>>tmpStr;
        if(tmpStr=="ban"){
            cin>>tmpStr;
            if(blacklist->locateEle(tmpStr)!=-1) continue;//如果已经在黑名单里面，代表输入的没用
            blacklist->insertLast(tmpStr);
        }
        else if(tmpStr=="unban"){
            cin>>tmpStr;
            if(blacklist->locateEle(tmpStr)==-1) continue;//黑名单里面没找到、
            blacklist->deleteEleAtPos(blacklist->locateEle(tmpStr));
        }
        else if(tmpStr=="paths"){
            string st,en;
            cin>>st>>en;
            if(false) cout<<"Invalid number of paths."<<endl;
            else{
                result.printDijkstra(st);
                result.Dijkstra(st,en,blacklist)->printList();
                cout<<endl;
                cout<<result.getPathLength(result.Dijkstra(st,en,blacklist));
                cout<<endl;
            }
        }
        else if(tmpStr=="quit"){
            isContinue=false;
        }
        else{
            cout<<"No such option."<<endl;
        }
    } 
}

int main(){
    doDemo();
    return 0;
}