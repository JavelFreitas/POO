#include <iostream>
using namespace std;

int debug = 0;

int somar(int a, int v){ return a + v;}

int main(){
    int x, y, z;
    cin >> x >> y >> z;

    x = somar(x, y);
    if(debug) cout << z;
    z = x;
    return 0;
}