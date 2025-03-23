#include <iostream>
#include <iomanip>
using namespace std;

class EggDropTest{
    private:
        int critFloor;
        int highestFloor;
        
        int numTries;
        int eggsBroken;
        bool exactFloorTested;
        bool oneAboveTested;
        
    public:
        EggDropTest(){ // do not use this.
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
        EggDropTest(int cfloor, int tfloor){
            critFloor = cfloor;
            highestFloor = tfloor;
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
        bool testFloor(int fnum){
            // true if egg survives, false if egg breaks.
            numTries++;
            if(fnum <= critFloor){
                if(fnum==critFloor) exactFloorTested = true;
                return true;
            }
            else{
                if(fnum == critFloor + 1) oneAboveTested = true;
                eggsBroken++;
                return false;
            }
        }
        int getTries(){
            return numTries;
        }
        int getEggsBroken(){
            return eggsBroken;
        }
        bool floorConfirmed(){
            if(critFloor == 0){
                return oneAboveTested;
            }
            else if(critFloor==highestFloor){
                return exactFloorTested;
            }
            else{
                return (oneAboveTested && exactFloorTested);
            }
        }
        
        void setData(int cfloor, int tfloor){
            resetTries();
            critFloor = cfloor;
            highestFloor = tfloor;
        }
        void resetTries(){
            numTries = 0;
            eggsBroken = 0;
            exactFloorTested = false;
            oneAboveTested = false;
        }
};

/* Question 4 UPLOAD START */
// guaranteed at worst 300 floors, and at worst 10 eggs.
int dp[11][301];
//这里reault[i][j]使用 i 个鸡蛋和 j 次尝试，最多可以处理的楼层数。
//使用全局变量，因为下面无法传参

void initAnswers() {
    // 初始化dp数组
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j <= 300; j++) {
            dp[i][j] = 10000000;
        }
    }
    
    // 填充基本情况
    for (int i = 1; i <= 10; i++) {
        dp[i][0] = 0; // 0层楼，不需要测试
        dp[i][1] = 1; // 1层楼，只需要测试1次
    }
    for (int j = 1; j <= 300; j++) {
        dp[1][j] = j; // 1个鸡蛋，需要测试j次
    }

    // 填充所有情况
    for (int j = 2; j < 301; j++) {
        for (int i = 2; i < 11; i++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
        }
    }
}
int nextTestFloor(int hFloor, int eggsLeft, int lastSurvival, int lastBreak) {
    if (eggsLeft == 0) return -1; // 没有鸡蛋剩余，不再测试
    if (lastSurvival == -1) return 1; // 第一次测试，从第一层开始
    if (lastSurvival == hFloor - 1) return -1; // 已经测试到最高层，不再需要测试

    // 查找最优的下一步测试楼层
    int nextFloor = -1;
    int minCost = INT_MAX;
    for (int x = lastSurvival + 1; x < hFloor; x++) {
        int cost = max(dp[eggsLeft - 1][x - lastSurvival - 1], dp[eggsLeft][hFloor - x]);
        if (cost < minCost) {
            minCost = cost;
            nextFloor = x;
        }
    }
    return nextFloor;
}

int canHandleFloors(int eggs, int numTries) {
    return dp[eggs][numTries];
}

int minTimesForBuilding(int eggs, int numFloors) {
    // 查找最小的尝试次数
    for (int i = 1; i <= 300; i++) {
        if (dp[eggs][i] >= numFloors) {
            return i;
        }
    }
    return -1; // 理论上不会执行到这里
}

/* Question 4 UPLOAD END */

void minTimesTest(){
    for(int i=1;i<=10;i++){
        cout << right << setw(5) << i;
    }
    cout << endl;
    for(int j=1;j<=25;j++){
        for(int i=1;i<=10;i++)
            cout << right << setw(5) << minTimesForBuilding(i,j);
        cout << endl;
    }
    int testings[8] = {30,35,40,45,50,100,200,300};
    for(int j=0;j<8;j++){
        for(int i=1;i<=10;i++)
            cout << right << setw(5) << minTimesForBuilding(i,testings[j]);
        cout << endl;
    }
    cout << endl;
}

void handleFloorTest(){
    cout << right << setw(5) << " ";
    for(int i=1;i<=10;i++){
        cout << right << setw(5) << i;
    }
    cout << endl;
    for(int i=1;i<=8;i++){
        cout << right << setw(5) << i;
        for(int j=1;j<=10;j++){
            cout << right << setw(5) << canHandleFloors(j,i);
        }
        cout << endl;
    }
    cout << endl;
}

void setUpCase(int eggCount, int cFloor, int hFloor, int target){
    int lastSurvival = 0;
    int lastBreak = hFloor+1;
    int nextTest = 0;
    int eggsLeft = eggCount;
    EggDropTest edt(cFloor,hFloor);
    while(nextTest!=-1){
        nextTest = nextTestFloor(hFloor,eggsLeft,lastSurvival,lastBreak);
        if(nextTest==-1) break;
        if(edt.testFloor(nextTest)){
            lastSurvival = nextTest;
        }
        else{
            eggsLeft--;
            lastBreak = nextTest;
            if(eggsLeft==0) break;
        }
    }
    if(edt.floorConfirmed() && edt.getTries()<= target){
        cout << "Good" << endl;
    }
    else{
        cout << "Bad" << endl;
    }
}

void specificTests(int i){
    int floors[6] = {0,20,40,60,80,100};
    int counts[11] = {0,0,14,9,8,7,7,7,7,7,7};
    switch(i){
        case 10:
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
        case 3:
        case 2:
            for(int j=0;j<6;j++)
                setUpCase(i,floors[j],100,counts[i]);
            break;
        case 1: // reality check
            setUpCase(1,0,100,1);
            setUpCase(1,100,100,100);
            setUpCase(1,50,300,51);
            setUpCase(1,89,200,90);
        default:
            break;
    }
}

int main(){
    int testNum = 0;
    initAnswers();
    cin >> testNum;
    switch(testNum){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            specificTests(testNum);
            break;
        default:
            minTimesTest();
            handleFloorTest();
    }    
    return 0;
}
