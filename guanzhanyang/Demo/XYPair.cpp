#include <iostream>
using namespace std;

class XYPair{
public:
    XYPair(){ // constructor
        x = 0;
        y = 0;
    }
    XYPair(int a, int b){
        x = a;
        y = b;
    }
    void shiftPos(int a, int b){
        x += a;
        y += b;
    }
    int getX(){
        return x;
    }
    int getY(){
        return y;
    }
    void printPos(){
        cout << "(" << x << "," << y << ")"; //´òÓ¡
    }
private:
    int x, y;
};

int main(){
    XYPair xy1;
    XYPair xy2(5,10);

    xy1.printPos();
    cout << endl;
    xy2.printPos();

    xy1.shiftPos(-5,-10); // -5,-10
    xy2.shiftPos(5,10); // 10,20

    cout << endl;
    xy1.printPos();
    cout << endl;
    xy2.printPos();

    cout << endl;
    cout << xy2.getX() << " " << xy2.getY() <<endl;

    return 0;
}
