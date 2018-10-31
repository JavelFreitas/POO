#include <iostream>
#include <sstream>
using namespace std;

int main(){
    string line;
    getline(cin, line);
    stringstream in(line);
    int number;
    string name, object;
    in >> number >> name >> object;
    cout << number << name << object;
    return 0;
}