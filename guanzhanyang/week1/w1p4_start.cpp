#include <iostream>
#include <vector>
using namespace std;
class MaxMean{
    public:
        MaxMean(){
            sum=0;
            maxVal=-250;
            dataCount=0;
        }//构造函数
        
        void addNewInt(int x){
            data.push_back(x);
            sum+=x;
            ++dataCount;
            if(x>maxVal)
            {
                maxVal=x;
            }
        }
        
        int getDataCount(){
            return dataCount;
        }
        
        double getAverage(){
            double average=0;
            average=1.0*sum/dataCount;
            return average;
        }
        
        int getMax(){
            return maxVal;
        }
    private:
        vector<int> data;
        int dataCount;
        int maxVal;
        int sum;
        
};



int main(){
    srand(7777);
    MaxMean mm;
    for(int i=0;i<300;i++){ //generate random numbers between -200 to 200
        mm.addNewInt(rand() % 401 - 200);
    }
    cout << "Count: " << mm.getDataCount() << endl;
    cout << "Max: " << mm.getMax() << endl;
    cout << "Average: " << mm.getAverage() << endl << endl;
    
    MaxMean mm2;
    for(int i=0;i<200;i++){
        mm2.addNewInt(i);
    }
    cout << "Count: " << mm2.getDataCount() << endl;
    cout << "Max: " << mm2.getMax() << endl;
    cout << "Average: " << mm2.getAverage() << endl << endl;
    
    return 0;
}