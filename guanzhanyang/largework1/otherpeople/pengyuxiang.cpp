#include <iostream>
#include <cstdlib>
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
    void printList() {
        for (int i = 0; i < length; i++)
            cout << arr[i] << " ";
    }
};

struct trip { //定义装一个表达式的结构体
    int a, b, c;
};

int check(bool* boo, int boolength, VecList<trip>* T) { //用循环检测目前boolean数组是否满足题意，若不满足，则返回最先不满足的位置
    for (int i = 0; i < T->getLength(); i++) {
        if ((T->getEleAtPos(i).a * (boo[(T->getEleAtPos(i).a > 0 ? T->getEleAtPos(i).a : -T->getEleAtPos(i).a) - 1] == 1 ? 1 : -1) < 0) && (T->getEleAtPos(i).b * (boo[(T->getEleAtPos(i).b > 0 ? T->getEleAtPos(i).b : -T->getEleAtPos(i).b) - 1] == 1 ? 1 : -1) < 0) && (T->getEleAtPos(i).c * (boo[(T->getEleAtPos(i).c > 0 ? T->getEleAtPos(i).c : -T->getEleAtPos(i).c) - 1] == 1 ? 1 : -1) < 0)) {
            cout << i << endl;
            return i;
        }
    }
    return T->getLength();
}

void change(bool* boo, int boolength, VecList<trip>* T, int x) { //利用check返回的位置，用随机数生成来改变该位置的其中一个bool值使得该位置满足题意
    int x1 = T->getEleAtPos(x).a;
    int x2 = T->getEleAtPos(x).b;
    int x3 = T->getEleAtPos(x).c;
    int r = rand() % 3 + 1;

    if (r == 1) {
        boo[abs(x1) - 1] = boo[abs(x1) - 1] == 0 ? 1 : 0;
    }
    else if (r == 2) {
        boo[abs(x2) - 1] = boo[abs(x2) - 1] == 0 ? 1 : 0;
    }
    else if (r == 3) {
        boo[abs(x3) - 1] = boo[abs(x3) - 1] == 0 ? 1 : 0;
    }
}
int main(){
	int n, m;
	cin >> n >> m;
    bool* boolean = new bool[n]; //构造长度为n的bool动态数组
    VecList<trip>* t = new VecList<trip>; //构造并集表达式的储存空间 链表指针
	for (int i = 0; i < m; i++) { //储存m个并集表达式
		int x, y, z;
		cin >> x >> y >> z;
        trip tmp = { x,y,z };
        t->insertEleAtPos(i,tmp);
	}
    int* count = new int[2 * n]; //构造长度2n的动态数组，用于统计各个数据在m个表达式中出现的频次
    for (int i = 0; i < 2 * n; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < m; i++) { //统计频次
        if (t->getEleAtPos(i).a > 0) {
            count[t->getEleAtPos(i).a - 1]++;
        }
        else {
            count[-t->getEleAtPos(i).a - 1 + n]++;
        }
        if (t->getEleAtPos(i).b > 0) {
            count[t->getEleAtPos(i).b - 1]++;
        }
        else {
            count[-t->getEleAtPos(i).b - 1 + n]++;
        }
        if (t->getEleAtPos(i).c > 0) {
            count[t->getEleAtPos(i).c - 1]++;
        }
        else {
            count[-t->getEleAtPos(i).c - 1 + n]++;
        }
    }

    for (int i = 0; i < n; i++) { //根据统计情况初始化boolean数组：如1的频次为5，-1的频次为3，5>3，故boolean[0] = true
        if (count[i] >= count[i + n]) {
            boolean[i] = true;
        }
        else boolean[i] = false;
    }
    
    while (true) { //不断循环直至得出一个解
        int xx = check(boolean, n, t);
        if (xx == m) {
            for (int i = 0; i < n; i++) {
                cout << boolean[i] << " ";
            }
            break;
        }
        else {
            change(boolean, n, t, xx);
        }
    }
    delete[]boolean;
    delete[]count;
    delete t;
	return 0;
}