#include <iostream>
using namespace std;

int somar(int x, int y){return x + y;}

int main(){
    int x, y;
    while(cin >> x >> y){
        cout << somar(x, y) << endl;
    }
    return 0;
}