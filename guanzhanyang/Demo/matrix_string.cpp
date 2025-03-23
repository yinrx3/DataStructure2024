#include <iostream>
using namespace std;

int main(){
    int A[10][12]; // 10 x 12 ¾ØÕó

    int** B = new int*[10];
    for(int i=0;i<10;i++){
        B[i] = new int[12];
    }

    // A[i][j], B[i][j]

    string s = "ABC";
    string t = s + "BA";

    string w = t + 'j';

    string blank = "";
    w = blank + 'a' + 'b';

    cout << w << endl;

    return 0;
}
