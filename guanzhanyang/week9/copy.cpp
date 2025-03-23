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
int arr[11][301];
void initAnswers() {
     for (int i = 0; i < 301; i++) {
        arr[0][i] = 0;
    }//0个蛋，测300次，最高为0层
    for (int i = 0; i < 11; i++) {
        arr[i][0] = 0;
    }//i个蛋，测0次，最高为0层
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 301; j++) {
            arr[i][j] = 1;
        }
    }//其他情况先初始化为1层
     //由于1个蛋测i次最高能测i层
    for (int i = 1; i < 301; i++) {
        arr[1][i] = i;
    }
    //由于i个蛋测一次最高都只能测1层，所以先固定测量的次数，对蛋的个数做归纳
    for (int j = 2; j < 301; j++) {
        for (int i = 2; i < 11; i++) {
            arr[i][j] = arr[i - 1][j - 1] + arr[i][j - 1] + 1;
        }
    }
}

int canHandleFloors(int eggs, int numTries) {
    return arr[eggs][numTries];
}

int nextTestFloor(int hFloor, int eggsLeft, int lastSurvival, int lastBreak) {
    // gives us next floor to test on.
    // return -1 if there's no further need to test.
    if (lastBreak - lastSurvival == 0) { return -1; }//不存在的情况
    if (lastBreak - lastSurvival == 1) { return -1; }//如果这两层连续，则不需要再测下去
    if (lastBreak - lastSurvival == 2) { return lastSurvival +1; }//如果这两层只相差一层，则测两者中间这一层即可
    int maxcount = lastBreak - lastSurvival - 1;
    int minicount = 0;
    for (int i = 1; i <= maxcount; i++) {
        if (arr[eggsLeft][i] >= maxcount) {
            minicount = i;
            break;
        }
    }//获取最少需要测多少次，才能处理lastBreak-lastSurviva -1层建筑。
    int next = -1;//找出下一个测试的层数
    for (int j = lastSurvival + 1; j < lastBreak; j++) {
        if ((arr[eggsLeft - 1][minicount - 1] >= j - lastSurvival - 1) && (arr[eggsLeft][minicount - 1] >= lastBreak - j - 1)) {
            next = j;
            break;
        }
    }
    return next;
}

int minTimesForBuilding(int eggs, int numFloors) {
    int count = 0;
    for (int i = 0; i <= numFloors; i++) {
        
        if (arr[eggs][i] >= numFloors) {
        count = i; 
        break;
        }
    }
    return count;  // 返回所需的最坏测试次数
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
