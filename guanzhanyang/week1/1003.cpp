#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class MaxMean {
public:
    MaxMean() : dataCount(0), maxVal(numeric_limits<int>::min()), sum(0) {
    }

    void addNewInt(int x) {
        data.push_back(x);
        sum += x;
        dataCount++;
        if (x > maxVal) {
            maxVal = x;
        }
    }

    int getDataCount() {
        return dataCount;
    }

    double getAverage() {
        if (dataCount == 0) return 0;
        return static_cast<double>(sum) / dataCount;
    }

    int getMax() {
        return maxVal;
    }

private:
    vector<int> data;    // 用于存储数据
    int dataCount;       // 数据项的数量
    int maxVal;          // 当前最大值
    long long sum;       // 数据项的总和，使用 long long 以处理大数据量
};

int main() {
    srand(77747);
    MaxMean mm;
    for (int i = 0; i < 300; i++) { // generate random numbers between -200 to 200
        mm.addNewInt(rand() % 401 - 200);
    }
    cout << "Count: " << mm.getDataCount() << endl;
    cout << "Max: " << mm.getMax() << endl;
    cout << "Average: " << mm.getAverage() << endl << endl;

    MaxMean mm2;
    for (int i = 0; i < 200; i++) {
        mm2.addNewInt(i);
    }
    cout << "Count: " << mm2.getDataCount() << endl;
    cout << "Max: " << mm2.getMax() << endl;
    cout << "Average: " << mm2.getAverage() << endl << endl;

    return 0;
}